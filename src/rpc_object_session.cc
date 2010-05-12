#include <boost/shared_ptr.hpp>

#include "rpc.pb.h"
#include "rpc_session.h"
#include "rpc_object_session.h"

namespace contester {

SessionRpc::SessionRpc(shared_ptr<Session> session, ProtocolMessage* message)
  : message_(message),
    session_(session) {};

SessionRpc::~SessionRpc() {};

void SessionRpc::Return(::google::protobuf::Message* response) {
  session_->ReturnResult(this, response->SerializeAsString());
};

const ProtocolMessage* const SessionRpc::GetMessage() const {
  return message_.get();
};

};