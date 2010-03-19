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

class SubprocessWrapper {
 private:
  struct Subprocess * sub_;

 public:
  explicit SubprocessWrapper(::contester::proto::LocalExecutionParameters params);
  virtual ~SubprocessWrapper();
};

static bool Subprocess_SetProtoString(struct Subprocess * const sub, enum SUBPROCESS_PARAM param, const std::string& str) {
  return Subprocess_SetBufferUTF8(sub, param, str.c_str(), str.size());
};


SubprocessWrapper::SubprocessWrapper(::contester::proto::LocalExecutionParameters params) {
  sub_ = Subprocess_Create();
  Subprocess_SetProtoString(sub_, RUNLIB_APPLICATION_NAME, params.application_name());
  Subprocess_SetProtoString(sub_, RUNLIB_COMMAND_LINE, params.command_line());
  Subprocess_SetProtoString(sub_, RUNLIB_CURRENT_DIRECTORY, params.current_directory());
  
  Subprocess_SetInt(sub_, RUNLIB_TIME_LIMIT, params.time_limit() * 1000);
  Subprocess_SetInt(sub_, RUNLIB_TIME_LIMIT_HARD, params.time_limit_hard() * 1000);
  Subprocess_SetInt(sub_, RUNLIB_MEMORY_LIMIT, params.memory_limit());
  Subprocess_SetInt(sub_, RUNLIB_PROCESS_LIMIT, params.process_limit());

  Subprocess_SetBool(sub_, RUNLIB_CHECK_IDLENESS, params.check_idleness());
  Subprocess_SetBool(sub_, RUNLIB_RESTRICT_UI, params.restrict_ui());
  Subprocess_SetBool(sub_, RUNLIB_NO_JOB, params.no_job());
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
    boost::asio::async_read(
        socket_,
        boost::asio::buffer(&request_length_, sizeof(request_length_)),
        boost::bind(&LocalSession::handle_read_length, this,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
  }

  void handle_read_length(const boost::system::error_code& error,
      size_t bytes_transferred)
  {
    if (!error &&
        (bytes_transferred == sizeof(request_length_)) &&
        ((request_length_ = ntohl(request_length_)) < (64 * 1024 * 1024))) {

      std::cout << "Read length:" << request_length_ << ", error" << error << std::endl;

      buffer_.reset(new char[request_length_]);

      boost::asio::async_read(
          socket_,
          boost::asio::buffer(buffer_.get(), request_length_),
          boost::bind(&LocalSession::handle_read_proto, this,
              boost::asio::placeholders::error,
              boost::asio::placeholders::bytes_transferred));
    }
    else
    {
      delete this;
    }
  }

  void handle_read_proto(const boost::system::error_code& error,
      size_t bytes_transferred)
  {
    received_message_.reset(new ProtocolMessage());
    if (!error &&
        (bytes_transferred == request_length_) &&
        received_message_->ParseFromArray(buffer_.get(), request_length_) &&
        handle_message()) {
      start();
    } else delete this;
  }

  bool handle_message() {
    received_message_->PrintDebugString();

    if (received_message_->request().method_name() == "LocalExecute")
      return handle_local_execute();

    return false;
  }

  bool handle_local_execute() {
    contester::proto::LocalExecutionParameters params;
    if (params.ParseFromString(received_message_->request().message())) {
      SubprocessWrapper s(params);
      timer_.expires_from_now(boost::posix_time::seconds(3));
      timer_.async_wait(boost::bind(&LocalSession::handle_exec_done, this, received_message_->sequence_number()));
      return true;
    }
  }

  void handle_exec_done(int sequence_number) {
    contester::proto::LocalExecutionResult result;

    result.set_return_code(100);
    
    reply_message_.reset(new ProtocolMessage());
    reply_message_->set_sequence_number(sequence_number);
    reply_message_->mutable_response()->set_message(result.SerializeAsString());

    reply_buffer_ = reply_message_->SerializeAsString();
    response_length_ = htonl(reply_buffer_.size());

    boost::array<boost::asio::const_buffer, 2> bufs = {
      boost::asio::buffer(&response_length_, sizeof(response_length_)),
      boost::asio::buffer(reply_buffer_)
    };
    
    boost::asio::async_write(
        socket_,
        bufs,
        boost::bind(&LocalSession::handle_write_done, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
  };

  void handle_write_done(const boost::system::error_code& error,
      size_t bytes_transferred) {
  };
    

private:
  tcp::socket socket_;
  uint32_t request_length_;
  boost::scoped_array<char> buffer_;
  boost::scoped_ptr<ProtocolMessage> received_message_;
  uint32_t response_length_;
  boost::scoped_ptr<ProtocolMessage> reply_message_;
  std::string reply_buffer_;
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