#include "Server.h"
#include "Packet.h"
#include "UserData.h"
#include "Client.h"
#include "UserHandler.h"
#include "AllegroClass.h"
#include "Parser.h"
#include <memory>

#define IPFILE "direcciones.txt"
#define PORT ("12345")




int main(int argc, char * argv[])
{
	UserData data;		
	Packet packet;
	UserHandler user;
	AllegroClass allegro;
	Parser parser;

	parser.Read(argc, argv);

	data.imServer = parser.initialMachine;
	data.ip = parser.myIP;

	data.init(IPFILE);


	bool stop = false;
	bool amILast = false;
	if (data.ammountOfIPs >=2  && data.ammountOfIPs <= 255) {
		do {
			amILast = packet.amILast(data.ipPosition);

			if (data.imServer && packet.mustAskUser())
			{
				user.initGetter();
				stop = !user.askToStart();
				if (!stop) {
					packet.setAnimation(user.getAnimation());
					bool validSequence = false;
					while (!validSequence) {
						packet.setSequence(user.getSequence(data.ammountOfIPs));
						validSequence = packet.validateSequence();
					}
				}
				user.killGetter();
			}
			if (!stop && packet.myTurn(data.ipPosition))
			{
				ALLEGRO_DISPLAY * disp = allegro.createDisplay(2000, 1000);
				Animation * an =new Animation(packet.getAnimation());
				user.draw(an);					
				packet.updateCount();
				allegro.destroyDisplay(disp);
				delete an;
			}
			if (!stop && data.imServer && !amILast)		
 {
				unique_ptr<Client> client(new Client());
				client->link(user.getNextIP(packet.nextComputer(), data.ipList), PORT);
				client->sendMessage(packet.getPacketToTransfer());
				data.imServer = false;
			}

			if (!stop ) {
				if (!amILast) {
					Server s(PORT);
					s.connect();
					string a = s.getInfo();
					packet.clear();
					packet.setRecievedPacket(a);
					data.imServer = true;
				}
				else {
					data.imServer = true;
					packet.clear();
				}
			}


		} while (!stop);
	}		
}

