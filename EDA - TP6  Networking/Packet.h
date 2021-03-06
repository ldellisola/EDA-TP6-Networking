#pragma once

#include <vector>
#include <iostream>
#include <ctype.h>
#include <algorithm>
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
	void setSequence(vector<int> vect);
	void setAnimation(char a);
	int nextComputer();
	bool runNextComputer();				
	string getPacketToTransfer();		
	void setRecievedPacket(string a);
	void updateCount();
	char getAnimation();
	bool amILast(int pos);
	void clear();
	bool validateSequence();
private:
	bool countIncremented;
	char animation;
	int count;
	int countVerification;
	vector<int> sequence;
};


