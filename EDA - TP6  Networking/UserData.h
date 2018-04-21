#pragma once
#include <string>
#include <fstream>
using namespace std;

typedef struct UserData
{
	string ip;
	bool imServer;
	int ipPosition;
	vector<string> ipList;
	int ammountOfIPs;

	void init(const char * ipFile)
	{
		char buff[200];
		bool matchNotFound = true;
		ifstream source;
		source.open(ipFile, ifstream::in);

		for (int i = 0; source.good(); i++) {
			source.getline(buff, 200, '\n');
			ipList.push_back(buff);
		}
		source.close();


		ammountOfIPs = ipList.size();

		for (string ip_ : ipList) {
			int i = 1;
			if (!ip.compare(ip_.c_str()))
				ipPosition = i;
		}
	}


};