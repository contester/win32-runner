#pragma once

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/unordered_map.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include "rpc_method.h"
#include "rpc_server.h"

namespace contester {

class Session;
class Rpc;

class ServerImpl : public Server {
 public:
  ServerImpl(boost::asio::io_service& io_service);
  virtual ~ServerImpl();
  virtual void Listen(const boost::asio::ip::tcp::endpoint& endpoint);
  virtual bool CallMethod(const std::string& method_name, boost::shared_ptr<Rpc> rpc);
  virtual boost::shared_ptr<Session> GetSessionById(boost::uuids::uuid& id);
  virtual void AddMethod(const std::string& method_name, RpcMethod method);
  
 private:
  boost::asio::io_service& io_service_;
  boost::unordered_map< boost::uuids::uuid, boost::shared_ptr<Session> > sessions_;
  boost::unordered_map< boost::uuids::uuid, boost::shared_ptr<boost::asio::ip::tcp::acceptor> > acceptors_;
  boost::unordered_map< boost::uuids::uuid, boost::shared_ptr<boost::asio::ip::tcp::socket> > listeners_;

  boost::unordered_map< std::string, RpcMethod > methods_;

  boost::uuids::random_generator uuid_generator_;

  void RestartAccept(const boost::uuids::uuid& id);
  void HandleAccept(
    const boost::uuids::uuid& id,
    const boost::system::error_code& error);
};

};