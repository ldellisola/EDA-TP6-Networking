
#include "Packet.h"
#include "UserData.h"
#include "Client.h"
#include "UserHandler.h"
#include <memory>

#define IPFILE "hola"
#define PORT ("12345")


class Server{};

int main(int ardc, char * argv[])
{
	UserData data;		// Tiene que devolver la posicion de la ip.
	Packet packet;
	UserHandler user;

	parseCmdLine(argc, argv, &callback, &data);

	data.init(IPFILE);
	// Hay que verificar que hay mas de 2 maquinas y menos de 255.
	// Tengo que cambiar la numeracion de las ip ya que deben empezar con 1
	do {
		if (data.imServer && packet.mustAskUser())
		{
			packet.setSequence(user.getSequence());		
			packet.setAnimation(user.getAnimation());
		}
		if (packet.myTurn(data.ipPosition))
		{
			user.draw();					// No se si deberia ser de Packet
			packet.updateCount();
		}
		if (packet.runNextComputer())		// No se si deberia ser de Packet
		{
			unique_ptr<Client> client(new Client());
			client->link(user.getNextIP(packet.nextComputer(), IPFILE), PORT);
			client->sendMessage(packet.getPacketToTransfer());
		}
			Server s(PORT);

			s.connect();
			packet.setRecievedPacket(s.getInfo());

		
	} while (getch() != QUIT);


		
}

// IMPORTANTE

//El Server es el que escucha, mientras que el cliente es el que manda. 