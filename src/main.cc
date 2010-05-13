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

static bool Subprocess_SetProtoString(struct Subprocess * const sub, enum SUBPROCESS_PARAM param, const std::string& str) {
  return Subprocess_SetBufferUTF8(sub, param, str.c_str(), str.size());
};

class SubprocessWrapper {
 public:
  shared_ptr<Rpc> rpc_;

  SubprocessWrapper(shared_ptr<Rpc> rpc) : rpc_(rpc) {};
};

void ExecuteDone(struct Subprocess* const sub, void* wrapper) {
  scoped_ptr<SubprocessWrapper> sw(reinterpret_cast<SubprocessWrapper*>(wrapper));

  contester::proto::LocalExecutionResult response;

  const struct SubprocessResult * const result = Subprocess_GetResult(sub);

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

  Subprocess_Destroy(sub);

  sw->rpc_->Return(&response);
}

void Subprocess_FillProto(struct Subprocess * const sub, proto::LocalExecutionParameters* params) {
  Subprocess_SetProtoString(sub, RUNLIB_APPLICATION_NAME, params->application_name());
  Subprocess_SetProtoString(sub, RUNLIB_COMMAND_LINE, params->command_line());
  Subprocess_SetProtoString(sub, RUNLIB_CURRENT_DIRECTORY, params->current_directory());
  
  Subprocess_SetInt(sub, RUNLIB_TIME_LIMIT, params->time_limit() * 1000);
  Subprocess_SetInt(sub, RUNLIB_TIME_LIMIT_HARD, params->time_limit_hard() * 1000);
  Subprocess_SetInt(sub, RUNLIB_MEMORY_LIMIT, params->memory_limit());
  Subprocess_SetInt(sub, RUNLIB_PROCESS_LIMIT, params->process_limit());

  Subprocess_SetBool(sub, RUNLIB_CHECK_IDLENESS, params->check_idleness());
  Subprocess_SetBool(sub, RUNLIB_RESTRICT_UI, params->restrict_ui());
  Subprocess_SetBool(sub, RUNLIB_NO_JOB, params->no_job());
};

struct Subprocess * Subprocess_CreateAndFill(proto::LocalExecutionParameters* params) {
  struct Subprocess * const result = Subprocess_Create();

  Subprocess_FillProto(result, params);
  return result;
};


void LocalExecute(shared_ptr<Rpc> rpc) {
  contester::proto::LocalExecutionParameters request;
  request.ParseFromString(rpc->GetRequestMessage());

  struct Subprocess * const sub = Subprocess_CreateAndFill(&request);
  SubprocessWrapper* sw = new SubprocessWrapper(rpc);

  Subprocess_SetCallback(sub, ExecuteDone, sw);

  if (!Subprocess_Start(sub)) {
    delete sw;
    Subprocess_Destroy(sub);
    contester::proto::LocalExecutionResult response;
    rpc->Return(&response);
    return;
  }
};

void GetLocalEnvironment(shared_ptr<Rpc> rpc) {
  contester::proto::LocalEnvironment response;
  WCHAR* const env = GetEnvironmentStringsW();
  WCHAR* envp = env;

  while (*envp) {
    int bufsize = WideCharToMultiByte(CP_UTF8, 0, envp, -1, NULL, 0, NULL, NULL);
    char* buf = new char[bufsize];
    WideCharToMultiByte(CP_UTF8, 0, envp, -1, buf, bufsize, NULL, NULL);
    std::string str_var(buf);
    delete buf;
    size_t split_pos = str_var.find_first_of("=");
    if (split_pos != str_var.npos) {
      proto::LocalEnvironment::Variable* const var = response.add_variable();
      var->set_name(str_var.substr(0, split_pos));
      var->set_value(str_var.substr(split_pos + 1));
    }
    while (*envp) envp++;
    envp++;
  }
  FreeEnvironmentStringsW(env);

  rpc->Return(&response);
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
    s->AddMethod("LocalExecute", contester::LocalExecute);
    s->AddMethod("GetLocalEnvironment", contester::GetLocalEnvironment);
    s->Listen(tcp::endpoint(boost::asio::ip::address_v4::loopback(), std::atoi(argv[1])));
    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
};
