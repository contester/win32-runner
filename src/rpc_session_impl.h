#pragma once

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/unordered_map.hpp>

namespace contester {

class Server;
class SessionRpc;

class SessionImpl : public Session {
 public:
  SessionImpl(Server* server, boost::uuids::uuid& id, boost::shared_ptr<boost::asio::ip::tcp::socket> socket);
  virtual ~SessionImpl();

  virtual void Start();
  virtual void ReturnResult(SessionRpc* rpc, const std::string& result);

 private:
  Server* server_;
  boost::uuids::uuid id_;
  boost::shared_ptr<boost::asio::ip::tcp::socket> socket_;

  boost::unordered_map< int, boost::shared_ptr<SessionRpc> > requests_;

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


  void HandleWriteResponse(
      std::string* response_string,
      uint32_t* response_size,
      uint32_t sequence_number,
      const boost::system::error_code& error,
      size_t bytes_transferred);
};

};