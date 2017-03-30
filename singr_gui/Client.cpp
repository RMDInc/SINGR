#include <StdAfx.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <string>
#include <fstream>
#include "Form1.h"
// link with Ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")
 
#define DEFAULT_PORT "7" 
#define DEFAULT_BUFFER_LENGTH	65536
using namespace std;  
class Client {
public:
	Client(char* servername)
	{
		szServerName = servername;
		ConnectSocket = INVALID_SOCKET;
	}
 
	bool Start() {
		WSADATA wsaData;
 
		// Initialize Winsock
		int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
		if(iResult != 0)
		{
			printf("WSAStartup failed: %d\n", iResult);
			return false;
		}
 
		struct addrinfo	*result = NULL,
						*ptr = NULL,
						hints;
 
		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_UNSPEC;		
		hints.ai_socktype = SOCK_STREAM;	
		hints.ai_protocol = IPPROTO_TCP;
 
		// Resolve the server address and port
		iResult = getaddrinfo(szServerName, DEFAULT_PORT, &hints, &result);
		if (iResult != 0)
		{
			printf("getaddrinfo failed: %d\n", iResult);
			WSACleanup();
			return false;
		}
 
		ptr = result;
 
		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
 
		if (ConnectSocket == INVALID_SOCKET)
		{
			printf("Error at socket(): %d\n", WSAGetLastError());
			freeaddrinfo(result);
			WSACleanup();
			return false;
		}
 
		// Connect to server
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
 
		if (iResult == SOCKET_ERROR)
		{
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
		}
 
		freeaddrinfo(result);
 
		if (ConnectSocket == INVALID_SOCKET)
		{
			printf("Unable to connect to server!\n");
			WSACleanup();
			return false;
		}
 
		return true;
	};
 
	// Free the resouces
	void Stop() {
		int iResult = shutdown(ConnectSocket, SD_SEND);
 
		if (iResult == SOCKET_ERROR)
		{
			printf("shutdown failed: %d\n", WSAGetLastError());
		}
 
		closesocket(ConnectSocket);
		WSACleanup();
	};
 
	// Send message to server
	bool Send(char* szMsg)
	{
		
		int iResult = send(ConnectSocket, szMsg, strlen(szMsg), 0);
 
		if (iResult == SOCKET_ERROR)
		{
			printf("send failed: %d\n", WSAGetLastError());
			Stop();
			return false;
		}
 
		return true;
	};
 
	// Receive message from server
	bool Recv()
	{   
			ofstream myfile;
	        myfile.open ("datafile.txt",ios::app);
		char recvbuf[DEFAULT_BUFFER_LENGTH];
		int iResult = recv(ConnectSocket, recvbuf, DEFAULT_BUFFER_LENGTH, 0);
 
		if (iResult > 0)
		{
			char msg[DEFAULT_BUFFER_LENGTH];
			memset(&msg, 0, sizeof(msg));
			strncpy(msg, recvbuf, iResult);
			myfile << msg;
			//printf("Received: %s\n", msg);
 
			return true;
		}
 
 
		return false;
	}
 
private:
	char* szServerName;
	SOCKET ConnectSocket;
};