#pragma once

#include <boost/asio.hpp>
#include <string>
#include <cstdio>

class Server {
public:
	Server(std::string port);
	~Server();
	void connect();
	std::string getInfo();

private:
	boost::asio::io_service* IO_handler;
	boost::asio::ip::tcp::socket* serverSocket;
	boost::asio::ip::tcp::acceptor* serverAcceptor;
};