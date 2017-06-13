/* Source file for client class functions */
#include "stdafx.h"
#include "clientExample.h"

// Declare structs
struct corEvt {				// This struct can hold all of the data for a correlated event
	int aaTotalCounts;				// aa stands for adjacent average
	int aaEventNumber;
	int aaInt1;
	int aaInt2;
	int aaInt3;
	int aaInt4;
	int aaEight;
	int lpfEventNumber;		// lpf stands for Low Pass Filter
	int lpfTTLSignal;
	int lpfInt1;
	int lpfInt2;
	int lpfInt3;
	int lpfSeven;
	int lpfEight;
	int dffTimeSmall;		// dff stands for Differential filter
	int dffTimeBig;
	int dffEventNumber;
	int dffInt1;
	int dffInt2;
	int dffSeven;
	int dffEight;
};

using namespace std;

/* Client constructor */	
Client::Client(char* servername)
{
	szServerName = servername;
	ConnectSocket = INVALID_SOCKET;
}

/* Client member function */
bool Client::Start() {
	WSADATA wsaData;
 
	/* Initialize Winsock */
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
 
	/* Resolve the server address and port */
	iResult = getaddrinfo(szServerName, DEFAULT_PORT, &hints, &result);
	if (iResult != 0)
	{
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		return false;
	}
 
	ptr = result;
 
	/* Create a SOCKET for connecting to server */
	ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
 
	if (ConnectSocket == INVALID_SOCKET)
	{
		printf("Error at socket(): %d\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return false;
	}
 
	/* Connect to server */
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
 
/* Client member function 
 * Free the resouces */
void Client::Stop() {
	int iResult = shutdown(ConnectSocket, SD_SEND);
 
	if (iResult == SOCKET_ERROR)
	{
		printf("shutdown failed: %d\n", WSAGetLastError());
	}
 
	closesocket(ConnectSocket);
	WSACleanup();
};
 
/* Client member function
 * Send message to server */
bool Client::Send(const char* szMsg)
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

/* Receive message from server */
int Client::Recv(int * intArray)		//bool Recv() need to pass in pointer to msgInt array
{   
	int i(0);
	int iResult(0);
	int iPreviousResult(1);
	int iRecvd(0);
	int iLastError(0);
	int variable_buffsize = 65536;	
	char cTransferBuff[1000] = "";
	char cTestBuff[1000] = "";
	char * precvBuff(nullptr);
	precvBuff = new char[DEFAULT_BUFFER_LENGTH]();

	//just get this working...
	Sleep(2000);	//want to reduce this, should be a check loop or something that only waits as long as we need to
					//loop until we receive a certain packet from the uZ?

	while(1)
	{
		iResult = recv(ConnectSocket, cTransferBuff, 1000, 0);	// receive data from the socket
		if(iResult < 0)											// error checking
			break;
		if(iResult + iRecvd > 65535)							// ensure we don't write past the end of the buffer
			break;
		memcpy((precvBuff + iRecvd), cTransferBuff, iResult);	// copy the data from transferbuff to receive buffer
		iRecvd += iResult;
		if(iResult < 1000)										// if we got less than 1k bytes, break out
			break;
		memset(cTransferBuff, 0, 1000);							// reset the transfer buffer
		
	}

	if (iRecvd > 0)
	{
		std::istringstream iss (precvBuff);		// load buff into stream for reading
		while(iss.rdbuf()->in_avail() != 0)		// loop over the values in the string stream until there are no more available; ie. when in_avail returns 0
		{
			iss >> intArray[i];					// each time we loop we read out an int to the array
			i++;
		}
		delete [] precvBuff; precvBuff = nullptr;
		return i;								// return the number of ints read into intArray
	} 
 
	delete [] precvBuff;
	precvBuff = nullptr;
	return 1;
}

/* Sort and print to file the data from the experiment */	
int Client::SortPrint(const char * fileName, int * msgInt, int msgIntLen)
{
	// Need to sort the data that is now in msgInt	
	bool loop(true);
	corEvt * pevtArray(nullptr);
	pevtArray = new corEvt[512]();
	int j(0);		// loops over ints in msgInt
	int jj(0);
	int val;		// holds the int value
	int i(0);		// loops through events
	int ii(0);
	int iii(0);
	int check(0);	// check where we exit sorting loop
	int skips(0);

	ofstream output_file;
	output_file.open(fileName,ios::app);
	if ( !output_file.is_open() )
	{
		delete [] pevtArray;
		pevtArray = nullptr;
		return 2;
	}

	output_file << "ffffff" << endl;

	//write all our data to the file above
	for(i = 0; i < msgIntLen; i++)
	{
		output_file << msgInt[i] << endl;
	}
	i = 0;			//reset i
	return 414141;	// don't sort atm

	while (j < 12300)
	{	
		if(i == 512 && ii == 512 && iii == 512)
		{
			j = 12300;
			continue;
		}
		val = msgInt[j];
		switch (val) 
		{
		case 111111:
			// loop over the values in this event type
			for(i = 0; i < 512; i++)
			{
				if(j >=12300){break;}
				pevtArray[i].aaTotalCounts = msgInt[j+1];
				pevtArray[i].aaEventNumber = msgInt[j+2];
				pevtArray[i].aaInt1 = msgInt[j+3];
				pevtArray[i].aaInt2 = msgInt[j+4];
				pevtArray[i].aaInt3 = msgInt[j+5];
				pevtArray[i].aaInt4 = msgInt[j+6];
				pevtArray[i].aaEight = msgInt[j+7];
				j+=8;
			}
			//j++;	//Push the j value above the last 111111 ID so it won't come back here
			break;
		case 121212:
			for(ii = 0; ii < 512; ii++, j+=8)
			{
				if(j >=12300){break;}
				pevtArray[ii].lpfEventNumber = msgInt[j+1];
				pevtArray[ii].lpfTTLSignal = msgInt[j+2];
				pevtArray[ii].lpfInt1 = msgInt[j+3];
				pevtArray[ii].lpfInt2 = msgInt[j+4];
				pevtArray[ii].lpfInt3 = msgInt[j+5];
				pevtArray[ii].lpfSeven = msgInt[j+6];
				pevtArray[ii].lpfEight = msgInt[j+7];
			}
			//j++;	//Again, instead of setting j to another ID value, put it just above that
			break;
		case 131313:
			for(iii = 0; iii < 512; iii++, j+=8)
			{
				if(j >=12300){break;}
				pevtArray[iii].dffTimeSmall = msgInt[j+1];
				pevtArray[iii].dffTimeBig = msgInt[j+2];
				pevtArray[iii].dffEventNumber = msgInt[j+3];
				pevtArray[iii].dffInt1 = msgInt[j+4];
				pevtArray[iii].dffInt2 = msgInt[j+5];
				pevtArray[iii].dffSeven = msgInt[j+6];
				pevtArray[iii].dffEight = msgInt[j+7];
			}
			//j++;
			break;
		default:
			j++;
			skips++;
			break;
		} //End of switch statement
	} //End of while loop
		
	if( j > 12300)	//if the index ran away, exit
	{
		delete[] pevtArray;
		pevtArray = nullptr;
		output_file.close();
		return 1;
	}

	// Sorting the values of the int array is finished, print out the struct here
	if( check == 0 ){
		for ( jj = 0; jj < 512; ++jj)
		{
			output_file << setw(3) << jj
				<< setw(11) << pevtArray[jj].aaTotalCounts
				<< setw(10) << pevtArray[jj].aaEventNumber
				<< setw(10) << pevtArray[jj].aaInt1
				<< setw(10) << pevtArray[jj].aaInt2
				<< setw(10) << pevtArray[jj].aaInt3 
				<< setw(10) << pevtArray[jj].aaInt4
				<< setw(10) << pevtArray[jj].aaEight
				<< setw(10) << pevtArray[jj].lpfEventNumber 
				<< setw(10) << pevtArray[jj].lpfTTLSignal
				<< setw(10) << pevtArray[jj].lpfInt1 
				<< setw(10) << pevtArray[jj].lpfInt2
				<< setw(10) << pevtArray[jj].lpfInt3
				<< setw(10) << pevtArray[jj].lpfSeven
				<< setw(10) << pevtArray[jj].lpfEight
				<< setw(10) << pevtArray[jj].dffTimeSmall 
				<< setw(10) << pevtArray[jj].dffTimeBig
				<< setw(10) << pevtArray[jj].dffEventNumber
				<< setw(10) << pevtArray[jj].dffInt1
				<< setw(10) << pevtArray[jj].dffInt2
				<< setw(10) << pevtArray[jj].dffSeven
				<< setw(10) << pevtArray[jj].dffEight << endl;
		}
	}

	output_file.close(); 

	delete [] pevtArray;
	pevtArray = nullptr;
	return 414141;
}//end of SortPrint	
