#pragma once

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <cstdlib>
#include <iomanip>

// link with Ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")
 
#define DEFAULT_PORT				"7"		//Decreased default buffer length to 5000(4096) because we are just reading in 512 ints * 8 bytes/int = 4096 bytes max
#define DEFAULT_BUFFER_LENGTH		65536	// Increased from 65536 to try and bring in 3 full data sets (11,12,13) // reduce to 49152, data sets are smaller
//#define INTEGRATOR_DATA_BUFFSIZE	49152

// Client class that Sam wrote
class Client {
public:
	Client(char* servername);
 
	bool Start();
	void Stop();	// Free the resouces
	bool Send(const char* szMsg);	// Send message to server
	int miniRecv();
	int Recv(int * intArray);	// Receive message from server
	int SortPrint(const char * fileName, int * msgInt, int msgIntLen);
 
private:
	char* szServerName;
	SOCKET ConnectSocket;
};