/*
 * LApp.h
 *
 *  Created on: Jul 6, 2016
 *      Author: EJohnson
 */

#ifndef LAPP_H_
#define LAPP_H_

#include <stdio.h>
#include <stdbool.h>
#include <xil_io.h>
#include <xil_exception.h>
#include "stdlib.h"
#include "ps7_init.h"
#include "xscugic.h"
#include "xaxidma.h"
#include "xgpiops.h"
#include "xuartps.h"
#include "xil_printf.h"
#include "sleep.h"
#include "LDetector.h"
#include "LModule.h"
#include "xtime_l.h"

#include "xparameters.h"
#include "xsdps.h"
#include "ff.h"
#include "xil_cache.h"
#include "platform.h"
#include "xplatform_info.h"
#include "platform_config.h"

//ethernet includes
#include "lwip/init.h"
#include "lwip/tcp.h"
#include "lwipopts.h"
#include "lwip/ip_addr.h"
#include "lwip/inet.h"
#include "netif/xadapter.h"

#include "PollUart.h"

//SPI Includes
#include "xspips.h"

/* Globals */
#define UART_DEVICEID      XPAR_XUARTPS_0_DEVICE_ID
#define SW_BREAK_GPIO		51
#define LENGTH_DATA_ARRAY	12288
#define SIZEOF_DATA_ARRAY	49152
//size of data array is the number of integers read in from the FPGA // this number is divisible by 256, 12288 / 256 = 48
//#define EVENT_SIZE 32
#define INTS_PER_PACKET	361
#define INTS_LEFTOVER	14
#define SIZEOF_SND_BUFF	1444
#define PACKETS_TOTAL	34
#define SIZEOF_LEFTOVER_BYTES	INTS_LEFTOVER * sizeof(unsigned int)

// Hardware Interface
XUartPs Uart_PS;					// Instance of the UART Device
XGpioPs Gpio;						// Instance of the GPIO Driver Interface
XGpioPs_Config *GPIOConfigPtr;		// GPIO configuration pointer
static XScuGic_Config *GicConfig; 	// GicConfig
XScuGic InterruptController;		// Interrupt controller

// UART Variables
static char RecvBuffer[32];		// Buffer for Receiving Data

// General Purpose Variables
int Status; 					// General purpose Status indicator
u32 global_frame_counter = 0;	// Counts ... for ...

// Methods
int InitializeAXIDma(void); 		// Initialize AXI DMA Transfer
int InitializeInterruptSystem(u16 deviceID);
void InterruptHandler (void );
int SetUpInterruptSystem(XScuGic *XScuGicInstancePtr);
int ReadCommandPoll();				// Read Command Poll Function
void SetIntegrationTimes(u8 wfid);	// Set the Registers forIntegral Times
int PrintData();					// Print Data to the Terminal Window
void ClearBuffers();				// Clear Processeed Data Buffers
int DAQ();				// Clear Processeed Data Buffers
int WFDAQ();
int PrintWFData();

#endif /* LAPP_H_ */
