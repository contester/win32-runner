#include "LocalProto.pb.h"

#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/make_shared.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include "rpc_server.h"
#include "w32invoke.h"

using boost::make_shared;
using boost::scoped_ptr;
using boost::shared_ptr;
using std::string;

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
};

using boost::asio::ip::tcp;
using contester::Server;


int main(int argc, char **argv) {
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: async_tcp_echo_server <port>\n";
      return 1;
    }

    boost::asio::io_service io_service;
    Server s(io_service);
	s.Listen(tcp::endpoint(boost::asio::ip::address_v4::loopback(), std::atoi(argv[1])));
    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
};
