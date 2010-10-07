#pragma once

#include <boost/asio.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread/recursive_mutex.hpp>
#include "rpc_object.h"

using boost::scoped_ptr;
using boost::shared_ptr;

namespace contester {

class Session;

class SessionRpc : public Rpc {
 public:
  explicit SessionRpc(shared_ptr<Session> session, ProtocolMessage* message);
  virtual ~SessionRpc();

  virtual void Return(::google::protobuf::Message* response);
  virtual const ProtocolMessage* const GetMessage() const;
  virtual const std::string& GetRequestMessage() const;
  virtual void SetCancelCallback(RpcCallback cancel_callback);
  virtual void Cancel();
  virtual void ReturnError(const std::string& traceback);
  virtual boost::asio::io_service * GetIoService();

 private:
  shared_ptr<Session> session_;
  scoped_ptr<ProtocolMessage> message_;
  RpcCallback cancel_callback_;
  boost::recursive_mutex mutex_;
};

};