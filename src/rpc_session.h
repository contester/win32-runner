#pragma once

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/unordered_map.hpp>

namespace contester {

class SessionRpc;

class Session {
 public:
  virtual ~Session();
  
  static const uint32_t kMaxRequestSize = 64 * 1024 * 1024;

  virtual void Start() = 0;
  virtual void ReturnResult(SessionRpc* rpc, const std::string& result) = 0;
  virtual void ReturnError(SessionRpc* rpc, const std::string& traceback) = 0;
};

class Server;

boost::shared_ptr<Session> CreateTCPSession(
    Server* server,
    boost::uuids::uuid& id,
    boost::shared_ptr<boost::asio::ip::tcp::socket> socket);

};