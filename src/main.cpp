#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

#include "rpc.pb.h"

using boost::asio::ip::tcp;

int main(int argc, char **argv) {
  try
  {
    boost::asio::io_service io_service;
    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 9900));
    for (;;)
    {
      tcp::socket socket(io_service);
      acceptor.accept(socket);

      boost::system::error_code ignored_error;
      uint32_t proto_length = 0;

      std::size_t read_b = boost::asio::read(socket, boost::asio::buffer(&proto_length, sizeof(proto_length)));
      if (read_b < sizeof(proto_length))
        continue;

      proto_length = ntohl(proto_length);
      std::cout << proto_length << std::endl;

      char * msgbuf = (char*) malloc(proto_length);
      read_b = boost::asio::read(socket, boost::asio::buffer(msgbuf, proto_length));

      if (read_b == proto_length) {
        ProtocolMessage msg;

        msg.ParseFromArray(msgbuf, proto_length);
        msg.PrintDebugString();
      }

      free(msgbuf);
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}