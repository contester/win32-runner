#pragma once

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
};

};