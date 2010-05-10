#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/make_shared.hpp>
#include <boost/scoped_array.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/unordered_map.hpp>
#include <boost/uuid/uuid.hpp>

#include "rpc.pb.h"
#include "rpc_session.h"
#include "rpc_session_impl.h"
#include "rpc_object_session.h"
#include "rpc_server.h"

namespace contester {

using boost::uuids::uuid;
using boost::asio::ip::tcp;
using boost::shared_ptr;
using boost::scoped_ptr;
using boost::scoped_array;
using boost::make_shared;
using std::auto_ptr;


SessionImpl::SessionImpl(Server* server, uuid& id, shared_ptr<tcp::socket> socket)
  : server_(server),
    id_(id),
    socket_(socket) {};

void SessionImpl::StartRead() {
  uint32_t* request_size_buffer = new uint32_t;
  
  boost::asio::async_read(
      *socket_,
      boost::asio::buffer(request_size_buffer, sizeof(*request_size_buffer)),
      boost::bind(
          &SessionImpl::HandleReadSize, this,
          request_size_buffer,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
};

void SessionImpl::SelfDestruct() {
  socket_->close();
  // server_->sessions_.erase(id_);
  
  requests_.clear();
};

void SessionImpl::HandleReadSize(
    uint32_t* request_size_buffer,
    const boost::system::error_code& error,
    size_t bytes_transferred) {

  scoped_ptr<uint32_t> request_size_buffer_deleter(request_size_buffer);
  const uint32_t request_size = ntohl(*request_size_buffer);

  if (!error &&
      (bytes_transferred == sizeof(*request_size_buffer)) &&
      (request_size < kMaxRequestSize)) {
	  
    char* request_buffer = new char[request_size];

    boost::asio::async_read(
        *socket_,
        boost::asio::buffer(request_buffer, request_size),
        boost::bind(
            &SessionImpl::HandleReadProto, this,
            request_buffer,
            request_size,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
  } else SelfDestruct();
};

void SessionImpl::HandleReadProto(
    char* request_buffer,
    uint32_t request_size,
    const boost::system::error_code& error,
    size_t bytes_transferred) {
  scoped_array<char> request_buffer_deleter(request_buffer);

  if (!error && (bytes_transferred == request_size)) {
    auto_ptr<ProtocolMessage> message(new ProtocolMessage());
	
    if (message->ParseFromArray(request_buffer, request_size)) {
      shared_ptr<SessionRpc> sess(
          make_shared< SessionRpc, shared_ptr<Session>, ProtocolMessage* >(
              server_->GetSessionById(id_), message.release()));

      StartRead();
      server_->CallMethod(sess->GetMessage()->request().method_name(), sess);
    }
  } else SelfDestruct();
};

void SessionImpl::ReturnResult(SessionRpc* rpc, const std::string& result) {
  ProtocolMessage message;

  message.set_sequence_number(rpc->GetMessage()->sequence_number());
  message.mutable_response()->set_message(result);

  auto_ptr<std::string> response_string(new std::string(message.SerializeAsString()));
  auto_ptr<uint32_t> response_size(new uint32_t(htonl(response_string->size())));

  boost::array<boost::asio::const_buffer, 2> buffers = {
    boost::asio::buffer(response_size.get(), sizeof(*response_size)),
    boost::asio::buffer(*response_string)
  };

  boost::asio::async_write(
    *socket_,
    buffers,
    boost::bind(
        &SessionImpl::HandleWriteResponse, this,
        response_string.release(),
        response_size.release(),
        rpc->GetMessage()->sequence_number(),
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
};

void SessionImpl::HandleWriteResponse(
    std::string* response_string,
    uint32_t* response_size,
    uint32_t sequence_number,
    const boost::system::error_code& error,
    size_t bytes_transferred) {
  scoped_ptr<std::string> response_string_deleter(response_string);
  scoped_ptr<uint32_t> response_size_deleter(response_size);

  if (!error) {
    requests_.erase(sequence_number);
  } else SelfDestruct();
};

};