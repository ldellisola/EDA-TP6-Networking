#pragma once
#include <string>
#include <fstream>
using namespace std;

typedef struct UserData
{
	string ip;
	bool imServer;
	int ipPosition;

	void init(const char * ipFile)
	{
		char buff[100];
		bool matchNotFound = true;
		ifstream source;
		source.open(ipFile, ifstream::in);

		for (int i = 0; source.good() && matchNotFound; i++)
		{
			source.getline(buff, 200, '\n');
			if (!ip.compare(buff))
			{
				ipPosition = i;
				matchNotFound = false;
			}
		}
		source.close();
	}

};