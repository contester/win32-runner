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
  cancel_callback_ = NULL;
  session_->ReturnResult(this, response->SerializeAsString());
};

void SessionRpc::ReturnError(const std::string& traceback) {
  cancel_callback_ = NULL;
  session_->ReturnError(this, traceback);
};

const ProtocolMessage* const SessionRpc::GetMessage() const {
  return message_.get();
};

const std::string& SessionRpc::GetRequestMessage() const {
  return message_->request().message();
};

void SessionRpc::SetCancelCallback(RpcMethod cancel_callback) {
  cancel_callback_ = cancel_callback;
};

void SessionRpc::Cancel(shared_ptr<Rpc> rpc) {
  cancel_callback_(rpc);
};

boost::asio::io_service * SessionRpc::GetIoService() {
  return session_->GetIoService();
};

};