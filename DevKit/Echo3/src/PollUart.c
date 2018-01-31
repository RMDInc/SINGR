/*
 * PollUart.c
 *
 *  Created on: Aug 24, 2017
 *      Author: GStoddard
 */
//////////////////////////// ReadCommandType////////////////////////////////
// This function takes in the RecvBuffer read in by readcommandpoll() and
// determines what the input was and returns an int to main which indicates
// that value. It also places the 'leftover' part of the buffer into a separate
// buffer with just that number(s)/filename/other for ease of use.

#include "PollUart.h"

//Variable definitions
u32 rbuff;			// read buffer size returned
int ret;
int commandNum;	//this value tells the main menu what command we read from the rs422 buffer
int firstVal;
int secondVal;
int thirdVal;
int fourthVal;
float ffirstVal;
float fsecondVal;
float fthirdVal;
float ffourthVal;
unsigned long long int realTime;
char commandBuffer[10] = "";
char commandBuffer2[50] = "";
//unsigned int ui_TotalNeutronsPSD = 294967295;
//unsigned int ui_LocalTime = 1234567890;
int i_AnalogTemp = 12;
int i_DigitalTemp = 34;
char c_ReportBuff[100] = "";
int i_SprintfReturn = 0;
int ibytesSent = 0;

int ReadCommandType(char * RecvBuffer, XUartPs *Uart_PS) {
	//Variable definitions
	rbuff = 0;			// read buffer size returned
	ret = 0;
	commandNum = 999;	//this value tells the main menu what command we read from the rs422 buffer
	firstVal = 0;
	secondVal = 0;
	thirdVal = 0;
	fourthVal = 0;
	ffirstVal = 0.0;
	fsecondVal = 0.0;
	fthirdVal = 0.0;
	ffourthVal = 0.0;
	realTime = 0;

/*	while (!(RecvBuffer[rbuff-1] == '\n' || RecvBuffer[rbuff-1] == '\r'))
	{
		if(rbuff>32) { rbuff = 0;}
		rbuff += XUartPs_Recv(Uart_PS, RecvBuffer + rbuff, 32 - rbuff);
	} */

	iPollBufferIndex += XUartPs_Recv(Uart_PS, RecvBuffer + iPollBufferIndex, 32 - iPollBufferIndex);// Since iPollBufferIndex is global, we keep track of how many bytes we have read in to the receive buffer
	if(RecvBuffer[iPollBufferIndex - 1] == '\n' || RecvBuffer[iPollBufferIndex - 1] == '\r')		// if we find a return character
		ret = sscanf(RecvBuffer, " %[^_]", commandBuffer);											// copy the command (everything before the underscore)
	else
		return 99;	// If we don't find a return character, don't try and check the commandBuffer for one

	if(!strcmp(commandBuffer, "DAQ"))
	{
		ret = sscanf(RecvBuffer + strlen(commandBuffer) + 1, " %d", &firstVal);	//check that there is one int after the underscore // may need a larger value here to take a 64-bit time

		if(ret != 1)	//invalid input
		{
			//xil_printf("Invalid input; real time not recognized.\n\r");
			commandNum = -1;
		}
		else			//proper input
			commandNum = 0;

	}
	else if(!strcmp(commandBuffer, "WF"))
	{
		ret = sscanf(RecvBuffer + strlen(commandBuffer) + 1, " %d", &firstVal);	//check for the _number of the waveform

		if(ret != 1)	//invalid input
		{
			//xil_printf("Invalid input; wf_number not recognized.\n\r");
			commandNum = -1;
		}
		else
			commandNum = 1;
	}
	else if(!strcmp(commandBuffer, "TMP"))
	{
		ret = sscanf(RecvBuffer + strlen(commandBuffer) + 1, " %d_%d", &firstVal, &secondVal);	//check for the _number of the waveform

		if(ret != 2)	//invalid input
		{
			//xil_printf("Invalid input; _temperature_timeout not recognized.\n\r");
			commandNum = -1;
		}
		else
			commandNum = 2;
	}
	else if(!strcmp(commandBuffer, "GETSTAT"))
		commandNum = 3;
	else if(!strcmp(commandBuffer, "DISABLE"))
	{
		ret = sscanf(RecvBuffer + strlen(commandBuffer) + 1, " %s", commandBuffer2);	//check for the _number of the waveform

		if(ret != 1)	//invalid input
		{
			//xil_printf("\n\rInvalid input; wf_number not recognized.\n\r");
			commandNum = -1;
		}
		else
		{
			if(!strcmp(commandBuffer2, "ACT"))
				commandNum = 4;
			else if(!strcmp(commandBuffer2, "TEC"))
				commandNum = 5;
			else
				commandNum = -1;
		}
	}
	else if(!strcmp(commandBuffer, "TX"))
	{
		ret = sscanf(RecvBuffer + strlen(commandBuffer) + 1, " %s", commandBuffer2);

		if(ret != 1)
			commandNum = -1;
		else
			commandNum = 6;
	}
	else if(!strcmp(commandBuffer, "DEL"))
	{
		ret = sscanf(RecvBuffer + strlen(commandBuffer) + 1, " %s", commandBuffer2);

		if(ret != 1)
			commandNum = -1;
		else
			commandNum = 7;
	}
	else if(!strcmp(commandBuffer, "LS"))
	{
		ret = sscanf(RecvBuffer + strlen(commandBuffer) + 1, " %s", commandBuffer2);
		if(ret != 1)
			commandNum = -1;
		else
			commandNum = 8;
	}
	else if(!strcmp(commandBuffer, "TRG"))
	{
		ret = sscanf(RecvBuffer + strlen(commandBuffer) + 1, " %d", &firstVal);	//check that there is one int after the underscore

		if(ret != 1)	//invalid input
		{
			//xil_printf("Invalid input; wrong number of thresholds.\n\r");
			commandNum = -1;
		}
		else
			commandNum = 9;
	}
	else if(!strcmp(commandBuffer, "NGATES"))
	{
		ret = sscanf(RecvBuffer + strlen(commandBuffer) + 1, " %f_%f_%f_%f", &ffirstVal, &fsecondVal, &fthirdVal, &ffourthVal);	//check for the _number of the waveform

		if(ret != 4)	//invalid input
		{
			//xil_printf("Invalid input; wf_number not recognized.\n\r");
			commandNum = -1;
		}
		else
			commandNum = 10;
	}
	else if(!strcmp(commandBuffer, "HV"))
	{
		ret = sscanf(RecvBuffer + strlen(commandBuffer) + 1, " %d_%d", &firstVal, &secondVal);	//check for the _number of the waveform

		if(ret != 2)	//invalid input
		{
			//xil_printf("Invalid input; _temperature_timeout not recognized.\n\r");
			commandNum = -1;
		}
		else
			commandNum = 11;
	}
	else if(!strcmp(commandBuffer, "INT"))
	{
		//copy over the integrals
		ret = sscanf(RecvBuffer + strlen(commandBuffer) + 1, " %d_%d_%d_%d", &firstVal, &secondVal, &thirdVal, &fourthVal);

		//check the result and see if input from the user was correct
		if(ret < 4 && ret > -1)
		{
			//not enough numbers given
			//xil_printf("Invalid input, too few integration times given.\n\r");
			commandNum = -1;
		}
		else if((ret <= -1) || (ret > 4))
		{
			//invalid input, return a message indicating failure and return to main menu
			//too many ints or fail to read
			//xil_printf("Invalid input, too many or no integration times given.\n\r");
			commandNum = -1;
		}
		else
			commandNum = 12;
	}
	else if(!strcmp(commandBuffer, "ECAL"))
	{
		ret = sscanf(RecvBuffer + strlen(commandBuffer) + 1, " %f_%f", &ffirstVal, &fsecondVal);	//check for the _number of the waveform

		if(ret != 2)	//invalid input
		{
			//xil_printf("Invalid input; wf_number not recognized.\n\r");
			commandNum = -1;
		}
		else
			commandNum = 13;
	}
	else if(!strcmp(commandBuffer, "BREAK"))
		commandNum = 14;
	else if(!strcmp(commandBuffer, "START"))
	{
		ret = sscanf(RecvBuffer + strlen(commandBuffer) + 1, " %llud", &realTime);	//check for the _number of the waveform

		if(ret != 1)	//invalid input
		{
			//xil_printf("Invalid input; RealTime not recognized.\n\r");
			commandNum = -1;
		}
		else
			commandNum = 15;
	}
	else if(!strcmp(commandBuffer, "END"))
	{
		ret = sscanf(RecvBuffer + strlen(commandBuffer) + 1, " %llud", &realTime);	//check for the _number of the waveform

		if(ret != 1)	//invalid input
		{
			//xil_printf("Invalid input; RealTime not recognized.\n\r");
			commandNum = -1;
		}
		else
			commandNum = 16;
	}
	else if(!strcmp(commandBuffer, "ENDTMP"))
		commandNum = 17;
	else
		commandNum = -1;

	// a negative return value indicates failure, a positive value indicates success

	return commandNum;
}

int PollUart(char * RecvBuffer, XUartPs *Uart_PS)
{
	//Variable definitions
	int returnVal = 0;
	memset(commandBuffer, '\0', 10);

	iPollBufferIndex += XUartPs_Recv(Uart_PS, RecvBuffer + iPollBufferIndex, 32 - iPollBufferIndex);
	if(RecvBuffer[iPollBufferIndex-1] == '\n' || RecvBuffer[iPollBufferIndex-1] == '\r')	//if we find an 'enter'
	{
		ret = sscanf(RecvBuffer, " %[^\r]", commandBuffer);	//copy the command (everything before the underscore)
		memset(RecvBuffer, 0, 32);							//if there was input, blank it out after reading, regardless; should get rid of bad stuff hanging around
		iPollBufferIndex = 0;								//reset where we are reading from, as well
	}
	if(!strcmp(commandBuffer, "a"))
		returnVal = 97;
	else if(!strcmp(commandBuffer, "q"))
		returnVal = 113;

	return returnVal;
}

