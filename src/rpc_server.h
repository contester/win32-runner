#pragma once

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/function.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/unordered_map.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

namespace contester {

using boost::scoped_ptr;
using boost::shared_ptr;
using boost::function;
using boost::asio::io_service;
using boost::asio::ip::tcp;
using boost::enable_shared_from_this;
using boost::unordered_map;
using boost::uuids::uuid;
using std::auto_ptr;
using std::string;
using std::map;

class Rpc {
};

typedef boost::function<void (shared_ptr<Rpc>)> RpcMethod;

class Session;

class Server {
 public:
  boost::asio::io_service& io_service_;
  unordered_map< uuid, shared_ptr<Session> > sessions_;
  unordered_map< uuid, shared_ptr<tcp::acceptor> > acceptors_;
  unordered_map< uuid, shared_ptr<tcp::socket> > listeners_;

  Server(boost::asio::io_service& io_service);
  RpcMethod GetMethodHandler(const string& method_name);
  
  void Listen(const tcp::endpoint& endpoint);

 private:
  
  boost::uuids::random_generator uuid_generator_;

  void RestartAccept(const uuid& id);  
  void HandleAccept(
    const uuid id,
    const boost::system::error_code& error);
};

};