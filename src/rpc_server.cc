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
#include "rpc_server_impl.h"
#include "rpc_method.h"
#include "rpc_session.h"

namespace contester {

using boost::asio::ip::tcp;
using boost::enable_shared_from_this;
using boost::make_shared;
using boost::scoped_array;
using boost::scoped_ptr;
using boost::shared_ptr;
using boost::unordered_map;
using boost::uuids::uuid;

Server::~Server() {};

ServerImpl::ServerImpl(boost::asio::io_service& io_service)
    : io_service_(io_service) {};

void ServerImpl::Listen(const tcp::endpoint& endpoint) {
  const uuid id(uuid_generator_());
  shared_ptr<tcp::acceptor> acc(new tcp::acceptor(io_service_, endpoint));
  acceptors_.insert(std::pair< uuid, shared_ptr<tcp::acceptor> >(id, acc));
  RestartAccept(id);
};

void ServerImpl::RestartAccept(const uuid& id) {
  listeners_.erase(id);
  
  shared_ptr<tcp::socket> sock_ptr(new tcp::socket(acceptors_[id]->get_io_service()));
  listeners_.insert(std::pair< uuid, shared_ptr<tcp::socket> >(id, sock_ptr));
  
  acceptors_[id]->async_accept(
      *(listeners_[id]),
	  boost::bind(
	      &ServerImpl::HandleAccept, this,
		  id,
		  boost::asio::placeholders::error));
};
	
void ServerImpl::HandleAccept(
    const uuid& id,
    const boost::system::error_code& error) {
	
  if (!error) {
    uuid session_id(uuid_generator_());
    sessions_.insert(std::pair< uuid, shared_ptr<Session> >(session_id, CreateTCPSession(this, session_id, listeners_[id])));
    sessions_[session_id]->Start();
    RestartAccept(id);
  } else
    listeners_.erase(id);
};

bool ServerImpl::CallMethod(const std::string& method_name, shared_ptr<Rpc> rpc) {
  if (methods_.count(method_name)) {
    methods_[method_name](rpc);
    return true;
  }
  return false;
};

shared_ptr<Session> ServerImpl::GetSessionById(uuid& id) {
  return sessions_[id];
}

};