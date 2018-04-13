#include "Packet.h"

bool validInput(char * arr);


Packet::Packet()
{
	animation = NOTLOADED;
	count = NOTLOADED;
}


Packet::~Packet()
{
}

bool Packet::myTurn(int myComputer)
{
	return (sequence[count] == myComputer);
}

bool Packet::mustAskUser()
{
	return (animation == NOTLOADED || count == NOTLOADED || sequence.size() == 0);
}

void Packet::setSequence(int * arr)		// No me gusta, hay que rehacerlo
{
	for (int i = 0; i < 255 && arr[i] != 0 ; ++i)
		sequence.push_back(arr[i]);	// Seguro hayb una funcion que ahce esto

	count = 1;

	countIncremented = false;

}

void Packet::setAnimation(char a)
{
	animation = toupper(a);

	if (animation < 'A' || animation > 'F')
		animation = NOTLOADED;
}

int Packet::nextComputer()
{
	return sequence[count-1];
}

bool Packet::runNextComputer()
{
	return countIncremented;
}

string Packet::getPacketToTransfer()
{
	string retValue = &animation + count;

	for (int num : sequence)
	{
		retValue += num;
	}
	
	return retValue;
}

void Packet::setRecievedPacket(string a)
{
	animation = a[0];
	a.erase(a.begin());

	count = a[0];
	a.erase(a.begin());
	countIncremented = false;

	for (char ch : a)
		sequence.push_back(ch);


}

void Packet::updateCount()
{
	count++;
	countIncremented = true;
}



bool validInput(char * arr)
{
	bool retValue = true;
	for (int i = 0; i < 255 && arr[i] != 0 && retValue; i++)
	{
		if (arr[i] == '\n')
			arr[i] = 0;
		else if (arr[i] < '0' && arr[i] > '9')		// Hay una funcion que hace esto
			retValue = false;
	}
	return retValue;
}