#include <boost/shared_ptr.hpp>

#include "rpc.pb.h"
#include "rpc_session.h"
#include "rpc_object_session.h"

namespace contester {

SessionRpc::SessionRpc(shared_ptr<Session> session, ProtocolMessage* message)
  : session_(session),
    message_(message) {};

SessionRpc::~SessionRpc() {};

void SessionRpc::Return(::google::protobuf::Message* response) {
  SetCancelCallback(NULL);
  session_->ReturnResult(this, response->SerializeAsString());
};

void SessionRpc::ReturnError(const std::string& traceback) {
  SetCancelCallback(NULL);
  session_->ReturnError(this, traceback);
};

const ProtocolMessage* const SessionRpc::GetMessage() const {
  return message_.get();
};

const std::string& SessionRpc::GetRequestMessage() const {
  return message_->request().message();
};

void SessionRpc::SetCancelCallback(RpcCallback cancel_callback) {
  mutex_.lock();
  cancel_callback_ = cancel_callback;
  mutex_.unlock();
};

void SessionRpc::Cancel() {
  mutex_.lock();
  if (cancel_callback_) {
    const RpcCallback cancel_callback_t_ = cancel_callback_;
    cancel_callback_ = NULL;
    cancel_callback_t();
  } 
  mutex_.unlock();
};

boost::asio::io_service * SessionRpc::GetIoService() {
  return session_->GetIoService();
};

};
