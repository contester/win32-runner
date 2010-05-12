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
 public:
  struct Subprocess * sub_;
  shared_ptr<Rpc> rpc_;

  explicit SubprocessWrapper(proto::LocalExecutionParameters* params, shared_ptr<Rpc> rpc);
  virtual ~SubprocessWrapper();
  void Execute();
};

static bool Subprocess_SetProtoString(struct Subprocess * const sub, enum SUBPROCESS_PARAM param, const std::string& str) {
  return Subprocess_SetBufferUTF8(sub, param, str.c_str(), str.size());
};

void ExecuteDone(const struct Subprocess* sub__, void* wrapper) {
  scoped_ptr<SubprocessWrapper> sub(reinterpret_cast<SubprocessWrapper*>(wrapper));

  contester::proto::LocalExecutionResult response;

  const struct SubprocessResult * const result = Subprocess_GetResult(sub__);

  response.set_return_code(result->ExitCode);
  response.mutable_time()->set_user_time(result->ttUser);
  response.mutable_time()->set_kernel_time(result->ttKernel);
  response.mutable_time()->set_wall_time(result->ttWall);
  response.set_memory(result->PeakMemory);
  response.set_total_processes(result->TotalProcesses);
  
  const int succ = result->SuccessCode;

  if (succ & EF_KILLED) response.mutable_flags()->set_killed(true);
  if (succ & EF_TIME_LIMIT_HIT) response.mutable_flags()->set_time_limit_hit(true);
  if (succ & EF_MEMORY_LIMIT_HIT) response.mutable_flags()->set_memory_limit_hit(true);
  if (succ & EF_INACTIVE) response.mutable_flags()->set_inactive(true);
  if (succ & EF_TIME_LIMIT_HARD) response.mutable_flags()->set_time_limit_hard(true);
  if (succ & EF_TIME_LIMIT_HIT_POST) response.mutable_flags()->set_time_limit_hit_post(true);
  if (succ & EF_MEMORY_LIMIT_HIT_POST) response.mutable_flags()->set_memory_limit_hit_post(true);
  if (succ & EF_PROCESS_LIMIT_HIT) response.mutable_flags()->set_process_limit_hit(true);

  sub->rpc_->Return(&response);
}

SubprocessWrapper::SubprocessWrapper(proto::LocalExecutionParameters* params, shared_ptr<Rpc> rpc)
  : rpc_(rpc) {
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

  Subprocess_SetCallback(sub_, ExecuteDone, this);
};

SubprocessWrapper::~SubprocessWrapper() {
  if (sub_)
    Subprocess_Destroy(sub_);
  sub_ = NULL;
};

void SubprocessWrapper::Execute() {
  Subprocess_Start(sub_);
}


void Test(shared_ptr<Rpc> rpc) {
  contester::proto::LocalExecutionParameters request;
  request.ParseFromString(rpc->GetRequestMessage());

  SubprocessWrapper* sub = new SubprocessWrapper(&request, rpc);
  sub->Execute();
};


};

using boost::asio::ip::tcp;


int main(int argc, char **argv) {
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: async_tcp_echo_server <port>\n";
      return 1;
    }

    boost::asio::io_service io_service;
    shared_ptr<contester::Server> s(contester::CreateTCPServer(io_service));
    s->AddMethod("LocalExecute", contester::Test);
    s->Listen(tcp::endpoint(boost::asio::ip::address_v4::loopback(), std::atoi(argv[1])));
    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
};
