#pragma once

#include <vector>
#include <iostream>
#include <ctype.h>
#include <string>
#define NOTLOADED (-1)
using namespace std;

class Packet
{
public:
	Packet();
	~Packet();
	bool myTurn(int myComputer);
	bool mustAskUser();
	void setSequence(int * arr);
	void setAnimation(char a);
	int nextComputer();
	bool runNextComputer();				
	string getPacketToTransfer();		
	void setRecievedPacket(string a);
	void updateCount();

private:
	bool countIncremented;
	char animation;
	int count;
	int countVerification;
	vector<int> sequence;
};

