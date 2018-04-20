#include "Client.h"


using namespace boost::asio;
Client::Client()
{
	this->IOHandler = new io_service();
	this->clientSocket = new ip::tcp::socket(*IOHandler);
	this->clientResolver = new ip::tcp::resolver(*IOHandler);
}

//using namespace boost::asio;
void Client::link(const char * host, const char * port)
{
	auto q = ip::tcp::resolver::query(host, port);
	this->endpoint = clientResolver->resolve(q);
	connect(*clientSocket, endpoint);
	clientSocket->non_blocking(true);

	cout << "Client trying to conecct " << host << endl;
}

/*
using namespace boost;
string Client::recieveMessage()
{
	system::error_code error;
	char buff[1 + 1 + 255 + 1];		// 1 de la animacion, uno del count 255 de la cantidad de computadoras posibles y 1 del terminador
	size_t lenght = 0;
	timer::cpu_timer ticks;
	ticks.start();
	timer::cpu_times pastTicks = ticks.elapsed();
	double elapsedSeconds = 0.0;

	do {
		lenght = this->clientSocket->read_some(asio::buffer(buff), error);

		timer::cpu_times currentTicks = ticks.elapsed();

		if ((currentTicks.wall - pastTicks.wall) > 1e9) 
		{
			elapsedSeconds += (currentTicks.wall - pastTicks.wall) / 1e9;
			pastTicks = currentTicks;
		}

		if (!error)
			buff[lenght] = 0;
	} while (error.value() == WSAEWOULDBLOCK);

	string retValue = NULL;

	if (!error)
		retValue = buff;

	return retValue;
}
*/

void Client::sendMessage(string msg)
{
	size_t lenght = 0;
	boost::system::error_code error;

	do {
		lenght = this->clientSocket->write_some(boost::asio::buffer(msg, msg.length), error);
	} while (error);


}

bool Client::sendMessageTimed(string msg, int ms)
{
	Timer timer;
	timer.start();
	bool timeout = false;

	size_t lenght = 0;
	boost::system::error_code error;

	do {
		lenght = this->clientSocket->write_some(boost::asio::buffer(msg, msg.length), error);
		timer.stop();
		if (timer.getTime() > ms && lenght == 0)
			timeout = true;
	} while (error && !timeout);

	return !timeout;

}

Client::~Client()
{
	this->clientSocket->close();
	delete this->clientResolver;
	delete this->clientSocket;
	delete this->IOHandler;
}
