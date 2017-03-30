#pragma once

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <cstdlib>
#include <iomanip>

// link with Ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")
 
#define DEFAULT_PORT "7" 
#define DEFAULT_BUFFER_LENGTH	65536	// Increased from 65536 to try and bring in 3 full data sets (11,12,13) // reduce to 49152, data sets are smaller

// Client class that Sam wrote
class Client {
public:
	Client(char* servername);
 
	bool Start();
	void Stop();	// Free the resouces
	bool Send(const char* szMsg);	// Send message to server
	int Recv(int intArray[12291], int placeInArray);	// Receive message from server
														//bool Recv() need to pass in pointer to msgInt array
	int SortPrint(int msgInt[12291]);
 
private:
	char* szServerName;
	SOCKET ConnectSocket;
};