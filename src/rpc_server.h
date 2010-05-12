#pragma once
#include <boost/shared_ptr.hpp>

namespace contester {

class Rpc;
class Session;

class Server {
 public:
  virtual ~Server();

  virtual void Listen(const boost::asio::ip::tcp::endpoint& endpoint) = 0;
  virtual bool CallMethod(const std::string& method_name, boost::shared_ptr<Rpc> rpc) const = 0;
  virtual boost::shared_ptr<Session> GetSessionById(boost::uuids::uuid& id) = 0;
};

boost::shared_ptr<Server> CreateTCPServer(boost::asio::io_service& io_service);

};
