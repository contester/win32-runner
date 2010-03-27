#include "rpc.pb.h"
#include "LocalProto.pb.h"

#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/scoped_array.hpp>

#include "w32invoke.h"

using boost::scoped_ptr;
using boost::scoped_array;
using std::auto_ptr;
using std::string;

const uint32_t kMaxRequestSize = 64 * 1024 * 1024;

namespace contester {

class SubprocessWrapper {
 private:
  struct Subprocess * sub_;

 public:
  explicit SubprocessWrapper(proto::LocalExecutionParameters* params);
  virtual ~SubprocessWrapper();
};

static bool Subprocess_SetProtoString(struct Subprocess * const sub, enum SUBPROCESS_PARAM param, const std::string& str) {
  return Subprocess_SetBufferUTF8(sub, param, str.c_str(), str.size());
};


SubprocessWrapper::SubprocessWrapper(proto::LocalExecutionParameters* params) {
  sub_ = Subprocess_Create();
  Subprocess_SetProtoString(sub_, RUNLIB_APPLICATION_NAME, params->application_name());
  Subprocess_SetProtoString(sub_, RUNLIB_COMMAND_LINE, params->command_line());
  Subprocess_SetProtoString(sub_, RUNLIB_CURRENT_DIRECTORY, params->current_directory());
  
  Subprocess_SetInt(sub_, RUNLIB_TIME_LIMIT, params->time_limit() * 1000);
  Subprocess_SetInt(sub_, RUNLIB_TIME_LIMIT_HARD, params->time_limit_hard() * 1000);
  Subprocess_SetInt(sub_, RUNLIB_MEMORY_LIMIT, params->memory_limit());
  Subprocess_SetInt(sub_, RUNLIB_PROCESS_LIMIT, params->process_limit());

  Subprocess_SetBool(sub_, RUNLIB_CHECK_IDLENESS, params->check_idleness());
  Subprocess_SetBool(sub_, RUNLIB_RESTRICT_UI, params->restrict_ui());
  Subprocess_SetBool(sub_, RUNLIB_NO_JOB, params->no_job());
};

SubprocessWrapper::~SubprocessWrapper() {
  if (sub_)
    Subprocess_Destroy(sub_);
  sub_ = NULL;
};

using boost::asio::ip::tcp;

class LocalSession {
public:
  LocalSession(boost::asio::io_service& io_service)
    : socket_(io_service), timer_(io_service)
  {
  }

  tcp::socket& socket()
  {
    return socket_;
  }

  void start()
  {
    uint32_t* request_size_buffer = new uint32_t;

    boost::asio::async_read(
        socket_,
        boost::asio::buffer(request_size_buffer, sizeof(*request_size_buffer)),
        boost::bind(&LocalSession::handle_read_size, this,
          request_size_buffer,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
  }

  void handle_read_size(uint32_t* request_size_buffer,
      const boost::system::error_code& error,
      size_t bytes_transferred)
  {
    scoped_ptr<uint32_t> request_size_buffer_deleter(request_size_buffer);
    const uint32_t request_size = htonl(*request_size_buffer);

    if (!error &&
        (bytes_transferred == sizeof(*request_size_buffer)) &&
        (request_size < kMaxRequestSize)) {

      std::cout << "Read length:" << request_size << ", error" << error << std::endl;

      char* request_buffer = new char[request_size];

      boost::asio::async_read(
          socket_,
          boost::asio::buffer(request_buffer, request_size),
          boost::bind(&LocalSession::handle_read_proto, this,
              request_buffer,
              request_size,
              boost::asio::placeholders::error,
              boost::asio::placeholders::bytes_transferred));
    }
    else
    {
      delete this;
    }
  }

  void handle_read_proto(char* request_buffer,
      uint32_t request_size,
      const boost::system::error_code& error,
      size_t bytes_transferred)
  {
    scoped_array<char> request_buffer_deleter(request_buffer);
    std::auto_ptr<ProtocolMessage> message(new ProtocolMessage());

    if (!error &&
        (bytes_transferred == request_size) &&
        message->ParseFromArray(request_buffer, request_size) &&
        handle_message(message.release())) {
      start();
    } else delete this;
  }

  bool handle_message(ProtocolMessage* message) {
    std::auto_ptr<ProtocolMessage> message_deleter(message);
    message->PrintDebugString();

    if (message->request().method_name() == "LocalExecute") {
      auto_ptr<proto::LocalExecutionParameters> params(new proto::LocalExecutionParameters());
      if (params->ParseFromString(message->request().message()))
        return handle_local_execute(params.release(), message->sequence_number());
    }

    return false;
  }

  bool handle_local_execute(proto::LocalExecutionParameters* params_p, int sequence_number) {
    scoped_ptr<proto::LocalExecutionParameters> params(params_p);

    SubprocessWrapper s(params_p);
    timer_.expires_from_now(boost::posix_time::seconds(3));
    timer_.async_wait(boost::bind(&LocalSession::handle_exec_done, this, sequence_number));

    return true;
  }

  void send_rpc_reply(int sequence_number, google::protobuf::Message* message) {
    ProtocolMessage reply;

    reply.set_sequence_number(sequence_number);
    reply.mutable_response()->set_message(message->SerializeAsString());
    
    string* reply_str = new string(reply.SerializeAsString());
    uint32_t* reply_size = new uint32_t;
    *reply_size = htonl(reply_str->size());

    boost::array<boost::asio::const_buffer, 2> bufs = {
      boost::asio::buffer(reply_size, sizeof(*reply_size)),
      boost::asio::buffer(*reply_str)
    };
    
    boost::asio::async_write(
        socket_,
        bufs,
        boost::bind(&LocalSession::handle_write_done, this,
            reply_size,
            reply_str,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
  };

  void handle_exec_done(int sequence_number) {
    proto::LocalExecutionResult result;
    result.set_return_code(100);

    send_rpc_reply(sequence_number, &result);
  };

  void handle_write_done(
      uint32_t* reply_size,
      string* reply_str,
      const boost::system::error_code& error,
      size_t bytes_transferred) {
    scoped_ptr<uint32_t> reply_size_deleter(reply_size);
    scoped_ptr<string> reply_str_deleter(reply_str);

    //if (error || (bytes_transferred < (sizeof(*reply_size) + reply_str.size())))
    //  delete this;
  };
    

private:
  tcp::socket socket_;
  boost::asio::deadline_timer timer_;
};


class LocalServer
{
public:
  LocalServer(boost::asio::io_service& io_service, short port)
    : io_service_(io_service),
      acceptor_(io_service, tcp::endpoint(boost::asio::ip::address_v4::loopback(), port))
  {
    restart_accept();
  }

  void handle_accept(LocalSession* new_session,
      const boost::system::error_code& error)
  {
    if (!error)
    {
      std::cout << "accept" << std::endl;
      new_session->start();
      restart_accept();
    }
    else
    {
      delete new_session;
    }
  }

  void restart_accept() {
    LocalSession * const new_session = new LocalSession(io_service_);

    acceptor_.async_accept(new_session->socket(),
        boost::bind(&LocalServer::handle_accept, this, new_session,
            boost::asio::placeholders::error));
  }

private:
  boost::asio::io_service& io_service_;
  tcp::acceptor acceptor_;
};
};

using contester::LocalServer;

int main(int argc, char **argv) {
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: async_tcp_echo_server <port>\n";
      return 1;
    }

    boost::asio::io_service io_service;

    LocalServer s(io_service, std::atoi(argv[1]));

    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
};
