/*
 * PollUart.h
 *
 *  Created on: Aug 24, 2017
 *      Author: GStoddard
 */

#ifndef POLLUART_H_
#define POLLUART_H_

#include <stdio.h>		//needed for unsigned types
#include "xuartps.h"	//needed for uart functions

int iPollBufferIndex;

int ReadCommandType(char * RecvBuffer, XUartPs *Uart_PS);
int PollUart(char * RecvBuffer, XUartPs *Uart_PS);

#endif /* POLLUART_H_ */
