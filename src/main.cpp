#include "rpc.pb.h"
#include "LocalProto.pb.h"

#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

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

int main(int argc, char **argv) {
  try
  {
    boost::asio::io_service io_service;
    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 9900));
    for (;;)
    {
      tcp::socket socket(io_service);
      acceptor.accept(socket);

      boost::system::error_code ignored_error;
      uint32_t proto_length = 0;

      std::size_t read_b = boost::asio::read(socket, boost::asio::buffer(&proto_length, sizeof(proto_length)));
      if (read_b < sizeof(proto_length))
        continue;

      proto_length = ntohl(proto_length);
      std::cout << proto_length << std::endl;

      char * msgbuf = (char*) malloc(proto_length);
      read_b = boost::asio::read(socket, boost::asio::buffer(msgbuf, proto_length));

      if (read_b == proto_length) {
        ProtocolMessage msg;

        msg.ParseFromArray(msgbuf, proto_length);

        ::contester::proto::LocalExecutionParameters params;

        params.ParseFromString(msg.request().message());

        params.PrintDebugString();

        SubprocessWrapper sub(params);

        ::contester::proto::LocalExecutionResult result;

        result.set_return_code(100);

        ProtocolMessage reply;
        reply.set_sequence_number(msg.sequence_number());
        reply.mutable_response()->set_message(result.SerializeAsString());

        std::string reply_str = reply.SerializeAsString();

        proto_length = htonl(reply_str.size());

        read_b = boost::asio::write(socket, boost::asio::buffer(&proto_length, sizeof(proto_length)));
        read_b = boost::asio::write(socket, boost::asio::buffer(reply_str));
      }

      free(msgbuf);
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
};