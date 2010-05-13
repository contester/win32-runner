#pragma once

#include <boost/shared_ptr.hpp>
#include "rpc_method.h"

namespace google {
namespace protobuf {
class Message;
};
};

class ProtocolMessage;

namespace contester {

class Rpc {
 public:
  virtual ~Rpc();

  virtual void Return(::google::protobuf::Message* response) = 0;
  virtual const ProtocolMessage* const GetMessage() const = 0;
  virtual const std::string& GetRequestMessage() const = 0;
  virtual void SetCancelCallback(RpcMethod cancel_callback) = 0;
  virtual void Cancel(boost::shared_ptr<Rpc> rpc) = 0;
  virtual void ReturnError(const std::string& traceback) = 0;
};

};