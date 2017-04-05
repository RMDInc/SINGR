/* Source file for client class functions */
#include "stdafx.h"
#include "clientExample.h"

// Declare structs
struct corEvt {				// This struct can hold all of the data for a correlated event
	int aatime;				// aa stands for adjacent average
	int aatotCount;
	int aaEventNum;
	int aaInt1;
	int aaInt2;
	int aaInt3;
	int aaInt4;
	int lpfEventNum;		// lpf stands for Low Pass Filter
	int lpfInt1;
	int lpfInt2;
	int lpfInt3;
	int lpfSix;
	int lpfSeven;
	int lpfEight;
	int dffEventNum;		// dff stands for Differential filter
	int dffInt1;
	int dffInt2;
	int dffFive;
	int dffSix;
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
int Client::Recv(int intArray[12291], int placeInArray)		//bool Recv() need to pass in pointer to msgInt array
{   
	int transferNum(0);
	int iResult(0);
	int arrayIndex = placeInArray;
	std::string mystring = "";
	char * precvBuff(nullptr);
	precvBuff = new char[DEFAULT_BUFFER_LENGTH];
		
	iResult = recv(ConnectSocket, precvBuff, DEFAULT_BUFFER_LENGTH, 0);

	if (iResult > 0)
	{
		char * pmsg(nullptr);
		pmsg = new char[DEFAULT_BUFFER_LENGTH];		// msg[65536]
		strncpy(pmsg, precvBuff, iResult);			// Copy the contents of recvbuf -> msg

		//Print the value of iResult to a file?? that way we see how much is coming in // Don't need this for now
/*		ofstream output_file_3;
		output_file_3.open("iResultsizes.txt",ios::app);
		if(!output_file_3.is_open())
		{
			return 1;
		}
		output_file_3 << "Transfer" << transferNum++ << endl;
		output_file_3 << iResult << endl;  */

		delete [] precvBuff;
		precvBuff = nullptr;

		for (int i = 0; i < DEFAULT_BUFFER_LENGTH; ++i)		// Loop to convert a char array to an int array
		{
			char var = *(pmsg + i);
			if (var == 13 && *(pmsg+i+1) == 10)	// If the char and the next one are both empty
			{
				*(intArray + arrayIndex) = atoi(mystring.c_str());	// Convert the string to an int and save it to the array
				mystring = "";
				++arrayIndex;					// Increment the index of the int arrray
			}
			else if ( var == 10 )				// If on the second of the two empty chars, skip it
			{
				continue;
			}
			else 
			{
				mystring += var;				// Otherwise save the char onto the end of a string
			}
			if ( arrayIndex == 12291 )
			{
				output_file_3 << "-----" << endl;
				output_file_3.close();
				delete [] pmsg;
				pmsg = nullptr;
				return arrayIndex;
			}
		}
		output_file_3.close();
		delete [] pmsg;
		pmsg = nullptr;
		return arrayIndex;
	} 
 
	return 1;
}

/* Sort and print to file the data from the experiment */	
int Client::SortPrint(int msgInt[12291])
{
	// Need to sort the data that is now in msgInt	
	bool loop(true);
	corEvt * pevtArray(nullptr);
	pevtArray = new corEvt[512];
	int j(0);		// loops over ints in msgInt
	int jj(0);
	int val;		// holds the int value
	int i(0);		// loops through events
	int ii(0);
	int iii(0);
	int check(0);	// check where we exit sorting loop
	int skips(0);

/*		ofstream output_file_2;
	output_file_2.open("nosortfiletest.txt",ios::app);
	if(!output_file_2.is_open())
	{
		return 1;
	}
		
	output_file_2 << "----------" << endl;

	while(j<12291)
	{
		output_file_2 << msgInt[j] << endl;
		j++;
	}
	output_file_2.close();
	j = 0; */

	ofstream output_file;
	output_file.open("datafiletest.txt",ios::app);
	if ( !output_file.is_open() )
	{
		return 1;
	}

	while (j < 12291)
	{	
		if(i == 509 && ii == 510 && iii == 510)
		{
			j = 12291;
			continue;
		}
		val = msgInt[j];
		switch (val) 
		{
		case 111111:
			// loop over the values in this event type
			for(i = 0; i < 510; i++)
			{
				if(j >=12291){break;}
				pevtArray[i].aatime = msgInt[j+1];
				pevtArray[i].aatotCount = msgInt[j+2];
				pevtArray[i].aaEventNum = msgInt[j+3];
				pevtArray[i].aaInt1 = msgInt[j+4];
				pevtArray[i].aaInt2 = msgInt[j+5];
				pevtArray[i].aaInt3 = msgInt[j+6];
				pevtArray[i].aaInt4 = msgInt[j+7];
				j+=8;
			}
			j++;	//Push the j value above the last 111111 ID so it won't come back here
			break;
		case 121212:
			for(ii = 0; ii < 511; ii++, j+=8)
			{
				if(j >=12291){break;}
				pevtArray[ii].lpfEventNum = msgInt[j+1];
				pevtArray[ii].lpfInt1 = msgInt[j+2];
				pevtArray[ii].lpfInt2 = msgInt[j+3];
				pevtArray[ii].lpfInt3 = msgInt[j+4];
				pevtArray[ii].lpfSix = msgInt[j+5];
				pevtArray[ii].lpfSeven = msgInt[j+6];
				pevtArray[ii].lpfEight = msgInt[j+7];
			}
			j++;	//Again, instead of setting j to another ID value, put it just above that
			break;
		case 131313:
			for(iii = 0; iii < 511; iii++, j+=8)
			{
				if(j >=12291){break;}
				pevtArray[iii].dffEventNum = msgInt[j+1];
				pevtArray[iii].dffInt1 = msgInt[j+2];
				pevtArray[iii].dffInt2 = msgInt[j+3];
				pevtArray[iii].dffFive = msgInt[j+4];
				pevtArray[iii].dffSix = msgInt[j+5];
				pevtArray[iii].dffSeven = msgInt[j+6];
				pevtArray[iii].dffEight = msgInt[j+7];
			}
			j++;
			break;
		default:
			j++;
			skips++;
			break;
		} //End of switch statement
	} //End of while loop
		
	if( j > 12292){check = 1;};
	// Sorting the values of the int array is finished, print out the struct here
	if( check == 0 ){
		for ( jj = 0; jj < 510; ++jj)
		{
			output_file << setw(3) << ii
				<< setw(10) << pevtArray[jj].aatime
				<< setw(10) << pevtArray[jj].aatotCount
				<< setw(10) << pevtArray[jj].aaEventNum 
				<< setw(10) << pevtArray[jj].aaInt1
				<< setw(10) << pevtArray[jj].aaInt2 
				<< setw(10) << pevtArray[jj].aaInt3
				<< setw(10) << pevtArray[jj].aaInt4
				<< setw(10) << pevtArray[jj].lpfEventNum 
				<< setw(10) << pevtArray[jj].lpfInt1
				<< setw(10) << pevtArray[jj].lpfInt2 
				<< setw(10) << pevtArray[jj].lpfInt3
				<< setw(10) << pevtArray[jj].lpfSix
				<< setw(10) << pevtArray[jj].lpfSeven
				<< setw(10) << pevtArray[jj].lpfEight
				<< setw(10) << pevtArray[jj].dffEventNum 
				<< setw(10) << pevtArray[jj].dffInt1
				<< setw(10) << pevtArray[jj].dffInt2 
				<< setw(10) << pevtArray[jj].dffFive
				<< setw(10) << pevtArray[jj].dffSix
				<< setw(10) << pevtArray[jj].dffSeven
				<< setw(10) << pevtArray[jj].dffEight << endl;
		}
	}

	output_file.close(); 

	delete [] pevtArray;
	pevtArray = nullptr;
	return 0;
}//end of SortPrint	
