#include "UserHandler.h"



UserHandler::UserHandler()
{
}


UserHandler::~UserHandler()
{
}

const char * UserHandler::getNextIP(int pos, const char * file)
{
	char arr[200];
	int i = 1;

	ifstream source;

	source.open(file, ifstream::in);

	while (i != pos && source.good())
	{
		source.getline(arr, 200, '\n');
		i++;
	}
	return arr;		// Hay que chequear aca. No se si se va a destriur el arreglo o, como 
					//devuelvo un puntero constante, se mantiene lindo
}

int * UserHandler::getSequence()
{
	return nullptr;
}

char UserHandler::getAnimation()
{
	return 0;
}
