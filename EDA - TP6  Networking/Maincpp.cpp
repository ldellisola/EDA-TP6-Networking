#include "Server.h"
#include "Packet.h"
#include "UserData.h"
#include "Client.h"
#include "UserHandler.h"
#include <memory>

#define IPFILE "hola"
#define PORT ("12345")

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