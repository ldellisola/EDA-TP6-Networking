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
	if (count != NOTLOADED)
		return (sequence[count-1] == myComputer);
	else return false;
}

bool Packet::mustAskUser()
{
	return (animation == NOTLOADED || count == NOTLOADED || sequence.size() == 0);
}

void Packet::setSequence(vector<int> vect)		
{
	sequence = vect;
	
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
	char arr[2];
	arr[0] = animation;
	arr[1] = 0;
	string retValue = arr;
	retValue += count;

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