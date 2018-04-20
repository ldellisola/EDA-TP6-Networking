#include "Server.h"

Server::Server(std::string port) {

	this->IO_handler = new boost::asio::io_service();
	this->serverSocket = new boost::asio::ip::tcp::socket(*(this->IO_handler));
	this->serverAcceptor = new boost::asio::ip::tcp::acceptor(*(this->IO_handler), 
		boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), std::stoi(port)));

}

Server::~Server() {

	this->serverAcceptor->close();
	this->serverSocket->close();
	delete this->serverAcceptor;
	delete this->serverSocket;
	delete this->IO_handler;

}

void Server::connect() {

	this->serverAcceptor->accept(*(this->serverSocket));

}

std::string Server::getInfo() {

	char buffer[1 + 255 + 1];
	size_t lenght = 0;
	boost::system::error_code error;

	do {
		lenght = this->serverSocket->read_some(boost::asio::buffer(buffer), error);
	} while (error);

	buffer[lenght] = 0;
	std::string retValue = buffer;

	return retValue;
}
