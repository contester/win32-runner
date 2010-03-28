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
#include "rpc_server.h"

namespace contester {

using boost::asio::ip::tcp;
using boost::enable_shared_from_this;
using boost::make_shared;
using boost::scoped_array;
using boost::scoped_ptr;
using boost::shared_ptr;
using boost::unordered_map;
using boost::uuids::uuid;

class SessionRpc : public Rpc {
 public:
  explicit SessionRpc(shared_ptr<Session> session, ProtocolMessage* message);
 private:
  shared_ptr<Session> session_;
  scoped_ptr<ProtocolMessage> message_;
};

SessionRpc::SessionRpc(shared_ptr<Session> session, ProtocolMessage* message)
  : session_(session),
    message_(message) {};


class Session {
 public:
  shared_ptr<tcp::socket> socket_;
  uuid id_;

  Session(Server* server, uuid& id, shared_ptr<tcp::socket> socket);
  
  static const uint32_t kMaxRequestSize = 64 * 1024 * 1024;

  void StartRead();
 private:
  Server* server_;
  unordered_map< int, shared_ptr<SessionRpc> > requests_;

  void SelfDestruct();
  
  void HandleReadSize(
      uint32_t* request_size_buffer,
      const boost::system::error_code& error,
      size_t bytes_transferred);

  void HandleReadProto(
      char* request_buffer,
      uint32_t request_size,
      const boost::system::error_code& error,
      size_t bytes_transferred);
};


Session::Session(Server* server, uuid& id, shared_ptr<tcp::socket> socket)
  : server_(server),
    id_(id),
    socket_(socket) {};

void Session::StartRead() {
  uint32_t* request_size_buffer = new uint32_t;

  boost::asio::async_read(
      *socket_,
      boost::asio::buffer(request_size_buffer, sizeof(*request_size_buffer)),
      boost::bind(
          &Session::HandleReadSize, this,
          request_size_buffer,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
};

void Session::SelfDestruct() {
  socket_->close();
  server_->sessions_.erase(id_);
  
  requests_.clear();
};

void Session::HandleReadSize(
    uint32_t* request_size_buffer,
    const boost::system::error_code& error,
    size_t bytes_transferred) {

  scoped_ptr<uint32_t> request_size_buffer_deleter(request_size_buffer);
  const uint32_t request_size = htonl(*request_size_buffer);

  if (!error &&
      (bytes_transferred == sizeof(*request_size_buffer)) &&
      (request_size < kMaxRequestSize)) {
    char* request_buffer = new char[request_size];

    boost::asio::async_read(
        *socket_,
        boost::asio::buffer(request_buffer, request_size),
        boost::bind(
            &Session::HandleReadProto, this,
            request_buffer,
            request_size,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
  } else SelfDestruct();
};

void Session::HandleReadProto(
    char* request_buffer,
    uint32_t request_size,
    const boost::system::error_code& error,
    size_t bytes_transferred) {
  scoped_array<char> request_buffer_deleter(request_buffer);

  if (!error && (bytes_transferred == request_size)) {
    auto_ptr<ProtocolMessage> message(new ProtocolMessage());
    if (message->ParseFromArray(request_buffer, request_size)) {
      requests_[message->sequence_number()] =
	      make_shared< SessionRpc, shared_ptr<Session>, ProtocolMessage* >(server_->sessions_[id_], message.release());
      RpcMethod method = server_->GetMethodHandler(message->request().method_name());

      if (method)
        method(requests_[message->sequence_number()]);
    }
  } else SelfDestruct();
};

Server::Server(boost::asio::io_service& io_service)
    : io_service_(io_service) {};

void Server::Listen(const tcp::endpoint& endpoint) {
  const uuid id(uuid_generator_());
  // acceptors_.insert(id, new tcp::acceptor(io_service_, endpoint));
  RestartAccept(id);
};

void Server::RestartAccept(const uuid& id) {
  listeners_.erase(id);
  
  shared_ptr<tcp::socket> sock_ptr(new tcp::socket(acceptors_[id]->get_io_service()));
  listeners_.insert(std::pair< uuid, shared_ptr<tcp::socket> >(id, sock_ptr));
  
  acceptors_[id]->async_accept(
      *(listeners_[id]),
	  boost::bind(
	      &Server::HandleAccept, this,
		  id,
		  boost::asio::placeholders::error));
};
	
void Server::HandleAccept(
    const uuid id,
    const boost::system::error_code& error) {

  if (!error) {
	uuid session_id(uuid_generator_());
	
	shared_ptr<Session> sess(new Session(this, session_id, listeners_[id]));
	
    sessions_.insert(std::pair< uuid, shared_ptr<Session> >(session_id, sess));
    RestartAccept(id);
  } else
    listeners_.erase(id);
};

RpcMethod Server::GetMethodHandler(const string& method_name) {
  return 0;
};

};