#pragma once

#include <boost/asio.hpp>
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

  // Get the message
  virtual const ProtocolMessage* const GetMessage() const = 0;
  virtual const std::string& GetRequestMessage() const = 0;

  // Various returns. Can be called from any thread
  virtual void Return(::google::protobuf::Message* response) = 0;
  virtual void ReturnError(const std::string& traceback) = 0;

  // Called when session is destroyed, in io_service thread
  virtual void SetCancelCallback(RpcCallback cancel_callback) = 0;

  // Called by session, in io_service thread
  virtual void Cancel() = 0;

  virtual boost::asio::io_service * GetIoService() = 0;
};

};
