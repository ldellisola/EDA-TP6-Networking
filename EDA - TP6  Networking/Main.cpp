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
#define STOP "stop"
#define IMSERVER "yes"
#define NOTSERVER "not"

bool checkAllConnections(vector<string>& ips, const char * ip);
void tellAllComputersToStop(vector<string>& ips, const char * ip);
bool isIPinList(vector<string>& ips, const char * ip);
bool verifyConnection(vector<string>& ips, bool isServer);


int main(int argc, char * argv[])
{
	UserData data;		// Tiene que devolver la posicion de la ip.
	Packet packet;
	UserHandler user;
	AllegroClass allegro();
	Parser parser;

	parser.Read(argc, argv);

	data.imServer = parser.initialMachine;
	data.ip = parser.myIP;

	data.init(IPFILE);

	// Hay que verificar que hay mas de 2 maquinas y menos de 255.

	bool stop = false;
	bool start = true;
	// Esta parte es para verificar que solo hay un server
	/*if (data.imServer) {
		start = checkAllConnections(data.ipList, data.ip.c_str());
	}
	else{
		start = verifyConnection(data.ipList, data.imServer);
	}*/
	if (start) {
		do {
			if (data.imServer && packet.mustAskUser())
			{
				user.initGetter();
				packet.setAnimation(user.getAnimation());
				packet.setSequence(user.getSequence(data.ammountOfIPs));
				user.killGetter();
			}
			if (packet.myTurn(data.ipPosition))
			{
				user.draw();					
				packet.updateCount();
			}
			if (packet.runNextComputer())		// No se si deberia ser de Packet
			{
				unique_ptr<Client> client(new Client());
				client->link(user.getNextIP(packet.nextComputer(), data.ipList), PORT);
				client->sendMessage(packet.getPacketToTransfer());
			}

			Server s(PORT);
			s.connect();
			string a = s.getInfo();
			if (a.compare(STOP))
				packet.setRecievedPacket(a);
			else
				stop = true;

		} while (!stop);
	}

	// Esta parte hace que se apaguen las demas computadoras

	if (data.imServer)
		tellAllComputersToStop(data.ipList, data.ip.c_str());

	


		
}

// IMPORTANTE

//El Server es el que escucha, mientras que el cliente es el que manda. 


// Veamos esta idea. Al iniciarse el programa, el Servidor (computadora principal) le tiene que preguntar a todas las 
// computadoras si son server, para esto se tiene que conectar a cada computadora y preguntarle. Estas computadoras tiene
// poder responderle a la computadora principal, por eso deberiamos hacer que la computadora principal el mande su IP a 
// todas las demas computadoras, y si estas responden dentro de un tiempo determinado, verificamos si son Servers o no.
// De no responder, o responder que son servidores, se debe cerrar el programa en todas las computadoras.



bool checkAllConnections(vector<string>& ips, const char * ip) {
	bool retValue = true;

	for (string ip_ : ips) {
		if (ip_.compare(ip)) {
			Client * client = new Client();
			client->link(ip_.c_str(), PORT);
			client->sendMessage(ip);
			delete client;

			Server server(PORT);
			server.connect();
			string response = server.getInfoTimed(10);

			if (response.compare(NOTSERVER) || !response.compare(SERVER_TIMEOUT))
				retValue = false;
		}
	}

	return retValue;
}


void tellAllComputersToStop(vector<string>& ips, const char * ip) {
	bool retValue = true;
	
	for (string ip_ : ips) {
		if (ip_.compare(ip)) {
			unique_ptr<Client>client(new Client());
			client->link(ip_.c_str(), PORT);
			client->sendMessage(STOP);
		}
	}

}




bool isIPinList(vector<string>& ips, const char * ip) {
	bool match = false;

	for (int i = 0; i < ips.size() && !match; ++i) {
		if (!ips[i].compare(ip))
			match = true;
	}


	return match;
}

// Esta funcion toma como argumentos al archivo que contiene a las ip y tambien a un bool que le dice si es servidor o no
// (computadora principal). La computadora trata de conectarse al servidor por su puerto y espera a que este le mande un 
// mensaje. Cuando le llega este mensaje, va a contener a la IP de la computadora que lo envio, y verifico si esa IP esta
// en mi archivo de IPs. Si la IP no figura, simplemente lo dejo hacer timeout. Si la IP figura, le mando un mensaje que
// depende de si soy server o no. Si soy server le mando 'no' , mientras que si no soy server le mando 'si'. Aunque creo 
// que si soy server es imposible que entre a esta funcion, asi que la otra computadora va a hacer timeout.



bool verifyConnection(vector<string>& ips, bool isServer) {

	bool retValue = false;
	Server server(PORT);

	server.connect();

	string verification = server.getInfo(); // la computadora principal manda su IP

	if (isIPinList(ips, verification.c_str())) {
		retValue = true;
		unique_ptr<Client> client(new Client());
		client->link(verification.c_str(), PORT);
		if (isServer)
			client->sendMessage(IMSERVER);
		else
			client->sendMessage(NOTSERVER);
	}

	return retValue;
}





























































/*

Se utiliza la misma FSM del otro TP pero ahora hay que implementarla con un contenido.

Model View Controller (MVC) //Mirar

Como empezariamos este TP?

Event Generator, Clase evento? (ya la tengo hecha)

class Scenario
{
public:
createNewWorm(ulong id = 0, point pos = {?, ?}, direction dir = left);
destroyWorm(ulong id);
addObserver(Observer* obs);
moveLeft(eventtype ev);
moveRight(eventtype ev);
Jump(eventtype ev);
Toggle(eventtype ev);
Refresh(eventtype ev);
Inactive(eventtype ev);

private:
list<worm> w;
list<observer*> obs;
void update(void);
ImgFondo;
}

Void Sceneraio::update(void){
List<Observer*>::Iterator it;

For(it = obs.begin(); it != obs.end(); it++)  //++ sobrecargado para pasar al proximo item de lista
(*it) -> update(this);

}

class Observer {
virtual void update(void* data) = 0;
};

class drawScenario : public Observer {
public:
drawScenario(ALLEGRO_BITMAP wallpaper, ALLEGRO_DISPLAY disp, etc);
void update(void* data);

private:
drawWorm();
ALLEGRO_BITMAP wallpaper;
etc;
};

void drawScenario::update(void* data) {
Scenario* S = (Scenario*) data;
al_draw_bitmap(wallpaper);
List<worm>* wl = S -> getWormList();
List<worm>::iterator it;
for(it = wl->begin(); it = wl->end(); it++)
drawWorm(it->getPos());
al_flip_display();
};

void Scenario::refresh(eventtype* ev){
List<Worm>::iterator it;
for(it = w.begin(); it != w.end(); it++)
W -> refresh();
lastAction = REFRESH;
update(); //llama a todos los observers que van a ver que hubo un refresh como lastaction.
};

void Scenario::moveLeft(eventtype* ev){
List<worm>::iterator it;
for(it = w.begin(); it != w.end(); it++)
if(w->getId() == ev->getId())
w->StartWaking(); //Busca que gusano tiene que empezar a moverse
lastAction = LEFT;
update();
};

class SendMovement : public Observer {
public:
void update(void* data);
sendMovement(?);
private:
(...)
};

int main (int argc, char* argv[]){
Scenario S;
drawScenario d;
sendMovement sm;
S.addObserver(&a);
S.addObserver(&sm);
quit = false;

while(!quit) {
if(evg.hayEvento()) {
dispatch(evg.getEvento(), &S);
quit = evg.isQuit();
}
}
destroyAllegro();
return 0;

}

bool eventGen::hayEvento() {  //List<eventtype*> ev que esta adentro de evg.
if(hayEventosAllegro()) //agarra y mira la eventqueue de allegro
ev.push_back(getAllegroEvent())
if(hayEventosNetworking()) //lee readsum de boost a ver si llego un paquete
ev.push_back(getNetworkingEvent())//traduce paquete y manda un moveleft, jump, etc
if(ev.size() > 0)
return true;
else
return false;
};



*/