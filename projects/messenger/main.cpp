// Simple TCP server-client console messenger

#include <chrono>
#include <exception>
#include <iostream>
#include <string>
#include <thread>

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

using namespace std::chrono_literals;

void run_as_server (unsigned port)
{
  boost::asio::io_context context;
  tcp::acceptor acceptor(context, tcp::endpoint(tcp::v4(), port));

  tcp::endpoint endpoint = acceptor.local_endpoint();
  std::cout << "Server listening on " << endpoint.address().to_string()
            << ":" << endpoint.port() << std::endl;

  while (acceptor.is_open() && std::cin)
  {
    tcp::iostream stream;
    boost::system::error_code ec;
    acceptor.accept(*stream.rdbuf(), ec);
    if (ec)
    {
      std::cerr << ec << std::endl;
      std::this_thread::sleep_for(500ms);
      continue;
    }
    auto ip = stream.rdbuf()->remote_endpoint().address().to_string();
    std::cout << "Has connection from " << ip << "\n"
              << "*** Chat starts ***" << std::endl;

    while (stream && std::cin)
    {
      // receive message from client
      std::string msg;
      if (!std::getline(stream, msg))
        break;

      std::cout << "client: " << msg << std::endl;

      // send responce to the client
      std::cout << ">> " << std::flush;
      if (!std::getline(std::cin, msg))
        break;

      stream << msg << std::endl;
    }
    std::cout << "*** Chat ends ***\n"
              << "Waiting for a new connection..." << std::endl;
  }
  std::cout << "Bye, bye!" << std::endl;
}

void run_as_client (const std::string& server, unsigned port)
{
  tcp::iostream stream;
  stream.connect(server, std::to_string(port));

  if (!stream)
  {
    std::cerr << "Failed to connect to the server" << std::endl;
    return;
  }
  std::cout << "*** Has connection. Chat starts ***" << std::endl;

  while (stream && std::cin)
  {
    // send a message to the server
    std::cout << ">> " << std::flush;
    std::string msg;
    if (!std::getline(std::cin, msg))
      break;

    stream << msg << std::endl;

    // receive the server's response
    if (!std::getline(stream, msg))
      break;

    std::cout << "server: " << msg << std::endl;
  }
  std::cout << "*** Chat ends ***\n"
            << "Bye, bye!" << std::endl;
}

int main (int argc, char* argv[])
try
{
  if (argc < 2 || 3 < argc)
  {
    std::cerr << "Usage: " << argv[0]
              << " {\"server\"|\"localhost\"|ip} [port]" << std::endl;
    return 2;
  }
  std::string host{argv[1]};
  int port = (argc == 3) ? std::stoi(argv[2]) : 443;

  if (host == "server")  // keyword to start as server
    run_as_server(port);
  else
    run_as_client(host, port);
}
catch (std::exception& e)
{
  std::cerr << e.what() << std::endl;
  return 1;
}
