/******************************************************************************
 *
 * Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * Use of the Software is limited solely to applications:
 * (a) running on a Xilinx device, or
 * (b) that interact with a Xilinx device through a bus or interconnect.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Except as contained in this notice, the name of the Xilinx shall not be used
 * in advertising or otherwise to promote the sale, use or other dealings in
 * this Software without prior written authorization from Xilinx.
 *
 ******************************************************************************/
#include "LApp.h"

XGpioPs Gpio;
int Status;
XGpioPs_Config *GPIOConfigPtr;
XScuGic InterruptController;
static XScuGic_Config *GicConfig;

//static u32 testdata[LENGTH_DATA_ARRAY] = {};
static int testdata[LENGTH_DATA_ARRAY] = {};
int g_iTestCounter;	//global test counter variable

int main()
{
	// Local Variables for main()
	int i = 0;				// index
	int mode = 99;			// Mode of Operation
	int	menusel = 99999;	// Menu Select
	int enable_state = 0; 	// 0: disabled, 1: enabled
	int thres = 0;			// Trigger Threshold
	int ipollReturn = 0;
	//char updateint = 'N';	// switch to change integral values

	// Readout Variables
	int index = 0;
	int dram_addr = 0;
	int dram_base = 0xa000000;		// 167772160
	int dram_ceiling = 0xa00c000;	// 167821312 - 167772160 = 49152

	g_iTestCounter = 0;		// initialize global test counter
	XTime tStart = 0; XTime tEnd = 0;

	// SD Card Variables
	int doMount = 0;
	uint numBytesWritten = 0;
	FIL datafile;
	FRESULT i_SDReturn = FR_OK;
	FATFS fatfs;

	//test variables
//	u8 * pc_ReportBuff2;
//	pc_ReportBuff2 = (u8 *)calloc(101, sizeof(u8));
//	u8 * pu_testdatapieces;
//	pu_testdatapieces = (u8 *)calloc(49152, sizeof(u8));
//	int iSprintfReturn = 0;
	int bytesSent = 0;
	int testxilin = 0;
//	int myreturn = 0;

	memset(RecvBuffer, '\0',32);
	memset(SendBuffer, '\0',32);

	//*******************Setup the UART **********************//
	XUartPs_Config *Config = XUartPs_LookupConfig(UART_DEVICEID);
	if (NULL == Config) { return 1;}
	Status = XUartPs_CfgInitialize(&Uart_PS, Config, Config->BaseAddress);
	if (Status != 0){ return 1;	}

	/* Conduct a Selftest for the UART */
	Status = XUartPs_SelfTest(&Uart_PS);
	if (Status != 0) { return 1; }

	/* Get format of uart */
	XUartPsFormat Uart_Format;			// Specifies the format we have
	XUartPs_GetDataFormat(&Uart_PS, &Uart_Format);
	/* Set to normal mode. */
	XUartPs_SetOperMode(&Uart_PS, XUARTPS_OPER_MODE_NORMAL);
	//*******************Setup the UART **********************//

	//*******************Receive and Process Packets **********************//
	Xil_Out32 (XPAR_AXI_GPIO_0_BASEADDR, 11);
	Xil_Out32 (XPAR_AXI_GPIO_1_BASEADDR, 71);
	Xil_Out32 (XPAR_AXI_GPIO_2_BASEADDR, 167);
	Xil_Out32 (XPAR_AXI_GPIO_3_BASEADDR, 2015);
//	Xil_Out32 (XPAR_AXI_GPIO_4_BASEADDR, 12);
//	Xil_Out32 (XPAR_AXI_GPIO_5_BASEADDR, 75);
//	Xil_Out32 (XPAR_AXI_GPIO_6_BASEADDR, 75);
//	Xil_Out32 (XPAR_AXI_GPIO_7_BASEADDR, 50);
//	Xil_Out32 (XPAR_AXI_GPIO_8_BASEADDR, 25);
	Xil_Out32 (XPAR_AXI_GPIO_18_BASEADDR, 1);	//enable the system
	//*******************Receive and Process Packets **********************//

	init_platform();
	ps7_post_config();
	Xil_DCacheDisable();	//
	InitializeAXIDma();		// Initialize the AXI DMA Transfer Interface
	Xil_Out32 (XPAR_AXI_GPIO_16_BASEADDR, 16384);
	Xil_Out32 (XPAR_AXI_GPIO_17_BASEADDR , 1);
	InitializeInterruptSystem(XPAR_PS7_SCUGIC_0_DEVICE_ID);

	//****************** Mount SD Card *****************//
	if( doMount == 0 )	//make sure we only mount once
	{
		i_SDReturn = f_mount(&fatfs, "", 0);	// Mount the SD card in the default logical drive // This will mount upon first access to the volume
		doMount = 1;
	}
	//****************** Mount SD Card *****************//

	// *********** Setup the Hardware Reset GPIO ****************//
	GPIOConfigPtr = XGpioPs_LookupConfig(XPAR_PS7_GPIO_0_DEVICE_ID);
	Status = XGpioPs_CfgInitialize(&Gpio, GPIOConfigPtr, GPIOConfigPtr ->BaseAddr);
	if (Status != XST_SUCCESS) { return XST_FAILURE; }
	XGpioPs_SetDirectionPin(&Gpio, SW_BREAK_GPIO, 1);
	// *********** Setup the Hardware Reset MIO ****************//

	//test code
	xil_printf("I'm working\r\n");

	// ******************* POLLING LOOP *******************//
	while(1){
		sw = 0;   //  stop switch reset to 0
		XUartPs_SetOptions(&Uart_PS,XUARTPS_OPTION_RESET_RX);	// Clear UART Read Buffer
		memset(RecvBuffer, '\0', 32);
		menusel = 999;

//		sleep(0.5);  // Built in Latency ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 0.5 s
//		xil_printf("\n\r v2.1 \n\r");
//		xil_printf("\n\r MAIN MENU \n\r");
//		xil_printf("******************************\n\r");
//		xil_printf(" 0) Set Mode of Operation\n\r");
//		xil_printf(" 1) Enable or disable the system\n\r");
//		xil_printf(" 2) Continuously Read of Processed Data\n\r");
//		xil_printf("\n\r **Setup Parameters ** \n\r");
//		xil_printf(" 3) Set Trigger Threshold\n\r");
//		xil_printf(" 4) Set Integration Times (number of clock cycles * 4ns) \n\r");
//		xil_printf("\n\r ** Additional Commands ** \n\r");
//		xil_printf(" 5) Perform a DMA transfer of Waveform Data\n\r");
//		xil_printf(" 6) Send WFs to the GUI
//		xil_printf(" 7) Check the Size of the Data Buffered (Max = 4095) \n\r");
//		xil_printf(" 8) Clear the Processed Data Buffers\n\r");
//		xil_printf(" 9) Execute Print of Data on DRAM \n\r");
//		xil_printf("******************************\n\n\r");
		while (XUartPs_IsSending(&Uart_PS)) {i++;}  // Wait until Write Buffer is Sent

//		//test loop
//		while(1)
//		{
//			ipollReturn = PollUart(RecvBuffer, &Uart_PS);	//return value of 97, 113, or 0
//			if(ipollReturn == 97)	//user sent an "a" and wants to transfer a file	//32 bytes?
//			{
//				xil_printf("found an 'a'\r\n");
//				break;
//			}
//		}

		ReadCommandPoll();
		sscanf(RecvBuffer,"%02u",&menusel);

		switch (menusel) { // Switch-Case Menu Select

		case 0:
			ReadCommandPoll();
			sscanf(RecvBuffer,"%01u",&mode);

			if (mode < 0 || mode > 4 ) { break; }	// mode = 0, AA waveform // mode = 1, LPF waveform	// mode = 2, DFF waveform	// mode = 3, TRG waveform	// mode = 4, Processed Data
			Xil_Out32 (XPAR_AXI_GPIO_14_BASEADDR, ((u32)mode));
			break;

		case 1: //Enable or disable the system
			enable_state = 1;
			if (enable_state != 0 && enable_state != 1) { break; }
			Xil_Out32(XPAR_AXI_GPIO_18_BASEADDR, ((u32)enable_state));
			break;

		case 2: //Continuously Read of Processed Data
			// the user needs to set the mode before coming here; see case 0
			enable_state = 1;
			Xil_Out32 (XPAR_AXI_GPIO_18_BASEADDR, ((u32)enable_state));	//set enable device

			ipollReturn = 0;
			bytesSent = 0;
			index = 0;

			while(ipollReturn != 113)	//loop until getting a 'q' in the RecvBuffer
			{
				if(Xil_In32(XPAR_AXI_GPIO_11_BASEADDR) > 0)	//if the buffer is full, read it to SD
					DAQ();

				ipollReturn = PollUart(RecvBuffer, &Uart_PS);	//return value of 97(a), 113(q), or 0(else)

				if(ipollReturn == 97)	//user sent an "a" and wants to transfer a file	//32 bytes?
				{
					while(index < LENGTH_DATA_ARRAY)
					{
						xil_printf("%d\n",testdata[index]);
						index++;
					}
					index = 0;
					//bytesSent = 0;
					ipollReturn = 0;
				}

				memset(testdata, '\0', 12288);
			}

//			i_SDReturn = f_close(&datafile);
			sw = 0;   // broke out of the read loop, stop switch reset to 0
			break;

		case 3: //Set Threshold
			ReadCommandPoll();
			sscanf(RecvBuffer,"%04u",&thres);
			Xil_Out32(XPAR_AXI_GPIO_10_BASEADDR, ((u32)thres));
			break;

		case 4:
			SetIntegrationTimes(0);	// 0 means we want to change the AA waveforms, 1 for LPF, 2 for DFF
			break;

		case 5:
			Xil_Out32 (XPAR_AXI_DMA_0_BASEADDR + 0x48, 0xa000000);
			Xil_Out32 (XPAR_AXI_DMA_0_BASEADDR + 0x58 , 65536);
			sleep(1); 			// Built in Latency ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 1 s
			PrintData();		// Display data to console.
			sw = 0;   // broke out of the read loop, stop swith reset to 0
			break;

		case 6:
			//print waveforms to the GUI
			//set the mode with case 0:
			//make this just like case 2, except we have a different mode

//			mode = 0;
//			Xil_Out32 (XPAR_AXI_GPIO_14_BASEADDR, ((u32)mode));	//set mode to processed data
			enable_state = 1;
			Xil_Out32 (XPAR_AXI_GPIO_18_BASEADDR, ((u32)enable_state));	//set enable device

			ipollReturn = 0;
			bytesSent = 0;
			index = 0;

			while(ipollReturn != 113)	//loop until gettting a 'q' in the RecvBuffer
			{
//				if(Xil_In32(XPAR_AXI_GPIO_11_BASEADDR) > 0)	//if the buffer is full, read it to SD
					WFDAQ();	//eventually, need to put the buffer check back in (above) so that this doesn't just read garbage continuously

				ipollReturn = PollUart(RecvBuffer, &Uart_PS);	//return value of 97(a), 113(q), or 0(else)

				memset(testdata, '\0', 12288);
			}
			break;

		case 7:
			break;

		case 8: //Testing
			while(1)
			{
				ipollReturn = PollUart(RecvBuffer, &Uart_PS);	//return value of 97, 113, or 0
				if(ipollReturn == 97)	//user sent an "a" and wants to transfer a file	//32 bytes?
				{
					xil_printf("found an 'a'\r\n");
					break;
				}
				Xil_Out32 (XPAR_AXI_GPIO_15_BASEADDR, 1);				//enable read out
				Xil_Out32 (XPAR_AXI_DMA_0_BASEADDR + 0x48, 0xa000000);	//tell the fpga what address to start at
				Xil_Out32 (XPAR_AXI_DMA_0_BASEADDR + 0x58 , 49152);		//and how much to transfer	//can likely change 65536 -> 49152
				usleep(54); 											// Built in Latency - 54 us
				Xil_Out32 (XPAR_AXI_GPIO_15_BASEADDR, 0);				//disable read out
				//testxilin = Xil_In32(XPAR_AXI_GPIO_13_BASEADDR);
				testxilin = Xil_In32(XPAR_AXI_GPIO_11_BASEADDR);//0x41230000 //peripheral definition
				//xil_printf("%d\r\n",testxilin);
				testxilin = Xil_In32(0x412B0000);//canonical definition of gpio_2 listed as gpio_11
				//xil_printf("%d\r\n",testxilin);
				testxilin = Xil_In32(0x41230000);//0x41230000
				//xil_printf("%d\r\n",testxilin);

			}
//			bytesSent = 0;
//			iSprintfReturn = snprintf(pc_ReportBuff2, 100, "0123456789abcdefghijklmnopqrstuvwxyz9876543210zwxyvutsrqponmlkjihgfedcba");
//			XTime_GetTime(&tStart);
//			while(1)
//			{
//				XTime_GetTime(&tStart);
//				while(XUartPs_IsSending(&Uart_PS)){ i++;}	//wait
//				XTime_GetTime(&tEnd);
//
//				bytesSent += XUartPs_Send(&Uart_PS, pc_ReportBuff2 + bytesSent, iSprintfReturn - bytesSent);
//				if(bytesSent == iSprintfReturn)
//					break;
//			}
//			printf("\r\nOne wait took: %.2f us with i=%d\r\n", 1.0 * (tEnd - tStart) / (COUNTS_PER_SECOND/1000000),i);
			break;
		case 9: //Print DMA Data
			xil_printf("\n\r Test DAQ\n\r");
			XTime_GetTime(&tStart);
			DAQ();
			XTime_GetTime(&tEnd);
			printf("One DAQ() took: %.2f us\r\n", 1.0 * (tEnd - tStart) / (COUNTS_PER_SECOND/1000000));
			break;
		default :
			break;
		} // End Switch-Case Menu Select
	}

	/* never reached */
	cleanup_platform();

	return 0;
}

//////////////////////////// InitializeAXIDma////////////////////////////////
// Sets up the AXI DMA
int InitializeAXIDma(void) {
	u32 tmpVal_0 = 0;
	u32 tmpVal_1 = 0;

	tmpVal_0 = Xil_In32(XPAR_AXI_DMA_0_BASEADDR +  0x30);

	tmpVal_0 = tmpVal_0 | 0x1001; //<allow DMA to produce interrupts> 0 0 <run/stop>

	Xil_Out32 (XPAR_AXI_DMA_0_BASEADDR + 0x30, tmpVal_0);
	tmpVal_1 = Xil_In32(XPAR_AXI_DMA_0_BASEADDR + 0x30);

	return 0;
}
//////////////////////////// InitializeAXIDma////////////////////////////////

//////////////////////////// InitializeInterruptSystem////////////////////////////////
int InitializeInterruptSystem(u16 deviceID) {
	int Status;

	GicConfig = XScuGic_LookupConfig (deviceID);

	if(NULL == GicConfig) {

		return XST_FAILURE;
	}

	Status = XScuGic_CfgInitialize(&InterruptController, GicConfig, GicConfig->CpuBaseAddress);
	if(Status != XST_SUCCESS) {
		return XST_FAILURE;

	}

	Status = SetUpInterruptSystem(&InterruptController);
	if(Status != XST_SUCCESS) {
		return XST_FAILURE;

	}

	Status = XScuGic_Connect (&InterruptController,
			XPAR_FABRIC_AXI_DMA_0_S2MM_INTROUT_INTR,
			(Xil_ExceptionHandler) InterruptHandler, NULL);
	if(Status != XST_SUCCESS) {
		return XST_FAILURE;

	}

	XScuGic_Enable(&InterruptController, XPAR_FABRIC_AXI_DMA_0_S2MM_INTROUT_INTR );

	return XST_SUCCESS;

}
//////////////////////////// InitializeInterruptSystem////////////////////////////////


//////////////////////////// Interrupt Handler////////////////////////////////
void InterruptHandler (void ) {

	u32 tmpValue;
	tmpValue = Xil_In32(XPAR_AXI_DMA_0_BASEADDR + 0x34);
	tmpValue = tmpValue | 0x1000;
	Xil_Out32 (XPAR_AXI_DMA_0_BASEADDR + 0x34, tmpValue);

	global_frame_counter++;
}
//////////////////////////// Interrupt Handler////////////////////////////////

//////////////////////////// SetUp Interrupt System////////////////////////////////
int SetUpInterruptSystem(XScuGic *XScuGicInstancePtr) {
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler)XScuGic_InterruptHandler, XScuGicInstancePtr);
	Xil_ExceptionEnable();
	return XST_SUCCESS;

}
//////////////////////////// SetUp Interrupt System////////////////////////////////

//////////////////////////// ReadCommandPoll////////////////////////////////
// Function used to clear the read buffer
// Read In new command, expecting a <return>
// Returns buffer size read
int ReadCommandPoll() {
	u32 rbuff = 0;			// read buffer size returned
	int i = 0; 				// index
	XUartPs_SetOptions(&Uart_PS,XUARTPS_OPTION_RESET_RX);	// Clear UART Read Buffer
	for (i=0; i<32; i++ ) { RecvBuffer[i] = '_'; }			// Clear RecvBuffer Variable
	while (!(RecvBuffer[rbuff-1] == '\n' || RecvBuffer[rbuff-1] == '\r')) {
		rbuff += XUartPs_Recv(&Uart_PS, &RecvBuffer[rbuff],(32 - rbuff));
		sleep(0.1);			// Built in Latency ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 0.1 s
	}
	return rbuff;

}
//////////////////////////// ReadCommandPoll////////////////////////////////


//////////////////////////// Set Integration Times ////////////////////////////////
// wfid = 	0 for AA
//			1 for DFF
//			2 for LPF
// At the moment, the software is expecting a 5 char buffer.  This needs to be fixed.
void SetIntegrationTimes(u8 wfid){
	int integrals[8];
	u32 setsamples[8];
	int i = 0;

	for (i = 0; i<8; i++) {integrals[i] = 0; setsamples[i] = 0;}

	switch (wfid) { // Switch-Case for performing set integrals

			case 0: //AA Integrals
				ReadCommandPoll();
				sscanf(RecvBuffer,"%d",&integrals[0]);

				ReadCommandPoll();
				sscanf(RecvBuffer,"%d",&integrals[1]);

				ReadCommandPoll();
				sscanf(RecvBuffer,"%d",&integrals[2]);

				ReadCommandPoll();
				sscanf(RecvBuffer,"%d",&integrals[3]);

				setsamples[0] = ((u32)((integrals[0]+52)/4));
				setsamples[1] = ((u32)((integrals[1]+52)/4));
				setsamples[2] = ((u32)((integrals[2]+52)/4));
				setsamples[3] = ((u32)((integrals[3]+52)/4));

				Xil_Out32 (XPAR_AXI_GPIO_0_BASEADDR, setsamples[0]);
				Xil_Out32 (XPAR_AXI_GPIO_1_BASEADDR, setsamples[1]);
				Xil_Out32 (XPAR_AXI_GPIO_2_BASEADDR, setsamples[2]);
				Xil_Out32 (XPAR_AXI_GPIO_3_BASEADDR, setsamples[3]);
				break;
			case 1://DFF Integrals
				xil_printf("Enter Baseline Stop Time in ns: -32 to 0 <return> \t");
				ReadCommandPoll();
				sscanf(RecvBuffer,"%d",&integrals[0]);
				xil_printf("\n\r");

				xil_printf("Enter Integral Stop Time in ns: 0 to 500 <return> \t");
				ReadCommandPoll();
				sscanf(RecvBuffer,"%d",&integrals[1]);
				xil_printf("\n\r");

				setsamples[0] = ((u32)((integrals[0]+32)/4));
				setsamples[1] = ((u32)((integrals[1])/4));

				Xil_Out32 (XPAR_AXI_GPIO_7_BASEADDR, setsamples[0]);
				Xil_Out32 (XPAR_AXI_GPIO_8_BASEADDR, setsamples[1]);

				xil_printf("Inputs Rounded to the Nearest 4 ns : Number of Samples");
				xil_printf("Baseline Integral Window  [-32ns,%dns]: %d \n\r",-32 + ((int)Xil_In32(XPAR_AXI_GPIO_7_BASEADDR))*4, 9+Xil_In32(XPAR_AXI_GPIO_7_BASEADDR) );
				xil_printf("Integral Window 	      [0ns,%dns]: %d \n\r",((int)Xil_In32(XPAR_AXI_GPIO_8_BASEADDR))*4, 1+Xil_In32(XPAR_AXI_GPIO_8_BASEADDR));

				break;
			case 2://LPF Integrals
				xil_printf("Enter Baseline Stop Time in ns: -60 to 0 <return> \t");
				ReadCommandPoll();
				sscanf(RecvBuffer,"%d",&integrals[0]);
				xil_printf("\n\r");

				xil_printf("Enter Tail Integral Stop Time in ns: 200 to 8000 <return> \t");
				ReadCommandPoll();
				sscanf(RecvBuffer,"%d",&integrals[1]);
				xil_printf("\n\r");

				xil_printf("Enter Full Integral Stop Time in ns: 0 to 8000 <return> \t");
				ReadCommandPoll();
				sscanf(RecvBuffer,"%d",&integrals[2]);
				xil_printf("\n\r");

				setsamples[0] = ((u32)((integrals[0]+60)/4));
				setsamples[1] = ((u32)((integrals[1])/4));
				setsamples[2] = ((u32)((integrals[2])/4));

				Xil_Out32 (XPAR_AXI_GPIO_4_BASEADDR, setsamples[0]);
				Xil_Out32 (XPAR_AXI_GPIO_5_BASEADDR, setsamples[1]);
				Xil_Out32 (XPAR_AXI_GPIO_6_BASEADDR, setsamples[2]);

				xil_printf("Inputs Rounded to the Nearest 4 ns : Number of Samples");
				xil_printf("Baseline Integral Window  [-32ns,%dns]: %d \n\r",-32 + ((int)Xil_In32(XPAR_AXI_GPIO_4_BASEADDR))*4, 16+Xil_In32(XPAR_AXI_GPIO_4_BASEADDR) );
				xil_printf("Tail Integral Window 	  [200ns,%dns]: %d \n\r",((int)Xil_In32(XPAR_AXI_GPIO_5_BASEADDR))*4, 1+Xil_In32(XPAR_AXI_GPIO_5_BASEADDR));
				xil_printf("Full Integral Window 	  [0ns,%dns]: %d \n\r",((int)Xil_In32(XPAR_AXI_GPIO_6_BASEADDR))*4, 1+Xil_In32(XPAR_AXI_GPIO_6_BASEADDR));

				break;
			default:
				break;
	}

	return;
}
//////////////////////////// Set Integration Times ////////////////////////////////

//////////////////////////// PrintData ////////////////////////////////
int PrintData( ){
	int index = 0;
	int dram_addr = 0;
	int dram_base = 0xa000000;		// 167772160
	int dram_ceiling = 0xa00c000;	// 167821312 - 167772160 = 49152

	FRESULT ffres;
	//FRESULT ffres1;
	uint numBytesWritten = 0;
	FIL datafile;

	Xil_DCacheInvalidateRange(0x00000000, 65536);	//make sure the PS doesn't corrupt the memory  by accessing while doing DMA transfer

	//Save to SD card here
	ffres = f_open(&datafile, "t003.bin", FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
	ffres = f_lseek(&datafile, file_size(&datafile));
	dram_addr = dram_base;
	while(dram_addr <= dram_ceiling)	//will loop over 49152/4 addresses = 12288
	{
		testdata[index] = Xil_In32(dram_addr);	//grab the int from DRAM
		index++;
		dram_addr += 4;
		if((index % 4096) == 0)	//will stop at 4096, 8192, 12288
			ffres = f_write(&datafile, testdata + (index - 4096), SIZEOF_DATA_ARRAY/3, &numBytesWritten);	//write the data
	}
	ffres = f_close(&datafile);	//close the file
	return sw;
}
//////////////////////////// PrintData ////////////////////////////////

//////////////////////////// DAQ ////////////////////////////////
int DAQ(){
	Xil_Out32 (XPAR_AXI_GPIO_15_BASEADDR, 1);				//enable read out
	Xil_Out32 (XPAR_AXI_DMA_0_BASEADDR + 0x48, 0xa000000);	//tell the fpga what address to start at
	Xil_Out32 (XPAR_AXI_DMA_0_BASEADDR + 0x58 , 65536);		//and how much to transfer
	usleep(54); 			// Built in Latency - 54 us
	Xil_Out32 (XPAR_AXI_GPIO_15_BASEADDR, 0);				//disable read out

	Xil_Out32(XPAR_AXI_GPIO_9_BASEADDR,1);	//Clear the buffers //Reset the read address
	usleep(1);								// Built in Latency - 1 us // 1 clock cycle-ish
	Xil_Out32(XPAR_AXI_GPIO_9_BASEADDR,0);

	PrintData();

	return sw;
}
//////////////////////////// DAQ ////////////////////////////////

//////////////////////////// WF DAQ ////////////////////////////////
int WFDAQ(){
	Xil_Out32 (XPAR_AXI_GPIO_15_BASEADDR, 1);				//enable read out
	Xil_Out32 (XPAR_AXI_DMA_0_BASEADDR + 0x48, 0xa000000);	//tell the fpga what address to start at
	Xil_Out32 (XPAR_AXI_DMA_0_BASEADDR + 0x58 , 65536);		//and how much to transfer
	usleep(54); 			// Built in Latency - 54 us
	Xil_Out32 (XPAR_AXI_GPIO_15_BASEADDR, 0);				//disable read out

	Xil_Out32(XPAR_AXI_GPIO_9_BASEADDR,1);	//Clear the buffers //Reset the read address
	usleep(1);								// Built in Latency - 1 us // 1 clock cycle-ish
	Xil_Out32(XPAR_AXI_GPIO_9_BASEADDR,0);

	PrintWFData();

	return sw;
}
//////////////////////////// WF DAQ ////////////////////////////////

//////////////////////////// PrintWFData ////////////////////////////////
int PrintWFData( ){
	int data = 0;
	int dram_addr = 0;
	int dram_base = 0xa000000;		// 167772160 + 4096 = 167776256
	int dram_ceiling = 0xa001000;	// this reads out 4096/4 ints from the buffer

	Xil_DCacheInvalidateRange(0x00000000, 65536);	//make sure the PS doesn't corrupt the memory by accessing while doing DMA transfer

	dram_addr = dram_base;
	while(dram_addr <= dram_ceiling)	//will loop over 49152/4 addresses = 12288
	{
		data = Xil_In32(dram_addr);	//grab the int from DRAM
		dram_addr += 4;
		xil_printf("%d\r\n", data);
	}

	return sw;
}
//////////////////////////// PrintWFData ////////////////////////////////
