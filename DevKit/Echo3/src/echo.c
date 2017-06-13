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

#include <stdio.h>
#include <string.h>
#include "globals.h"
#include "lwip/err.h"
#include "lwip/tcp.h"
#include "sleep.h"
#include <xil_io.h>
#include <xil_cache.h>

#if defined (__arm__) || defined (__aarch64__)
#include "xil_printf.h"
#endif

struct tcp_pcb *globalTCP_pcb;	//global struct
extern int g_menuSel;			//global menu variable
int g_buffer_addr;

int transfer_data() {
	return 0;
}

void print_app_header()
{
	xil_printf("\n\r\n\r-----lwIP TCP echo server ------\n\r");
	xil_printf("TCP packets sent to port 6001 will be echoed back\n\r");
}

err_t recv_callback(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
	/* set variables */
	char * buffer = NULL;
	char * pEnd = NULL;
	int dat;
	int dram_addr = 0;
	int dram_base = 0xa000000;		//167772160
	int dram_ceiling = 0xa00c008;	//167821320 - 167772160 = 49160
	int writePtrAA = 0;
	int readPtrAA = 0;
	char cDone[8] = "141414\n";
	char data[20] = "";

	if (!p)
	{
		tcp_close(tpcb);
		tcp_recv(tpcb, NULL);
		return ERR_OK;
	}

	/* indicate that the packet has been received */
	tcp_recved(tpcb, p->len);

	/* allocate memory for the buffer and initialize it */
	buffer = (char *) malloc(p->len);
	memcpy(buffer, "0", 8);

	/* receive the data */
	memcpy(buffer, p->payload, p->len);

	if(g_menuSel == 9)	//if we want to transfer data, come here
	{
		if(buffer[0] == 'q')	//if the value sent was a 'q', then the user wants to break out of the
		{						//capturing loop and go back to the main menu
			g_txcomplete = 0;
			g_menuSel = 0;
			free(buffer);
			free(pEnd);
			return ERR_OK;
		}
		else if(buffer[0] == 'b')
		{
			while(tcp_sndbuf(tpcb) < 65535)
			{
				//wait until the buffer is clear
			}
			dram_base = g_buffer_addr;	//set the base value to be the top of the range that was already sent
			g_buffer_addr = 0;			//reset the variable holding the buffer address
		}
		else
		{
			Xil_Out32(XPAR_AXI_GPIO_9_BASEADDR,1);//reset BRAM buffers
			Xil_Out32(XPAR_AXI_GPIO_9_BASEADDR,0);//reset BRAM buffers

			Xil_Out32 (XPAR_AXI_GPIO_15_BASEADDR, 1);				//dma transfer
			Xil_Out32 (XPAR_AXI_DMA_0_BASEADDR + 0x48, 0xa000000);
			Xil_Out32 (XPAR_AXI_DMA_0_BASEADDR + 0x58 , 65536);
			sleep(1);												//want to reduce this statement as much as possible
			Xil_Out32 (XPAR_AXI_GPIO_15_BASEADDR, 0);				//ideally, we would have a check loop (like below) which monitors a gpio for a certain value

			switch(g_mode){
			case 0: case 1: case 2:	case 3:	//Any WF choice comes here
				while(1)	//test for data; when > 4095, we have a full buffer
				{
					dram_ceiling = Xil_In32(XPAR_AXI_GPIO_20_BASEADDR) * 4 + dram_base;		//Read the value of the write pointer * 4; it gives the number of ints written
					if(dram_ceiling - dram_base > 4095)
						break;
				}
				Xil_Out32(XPAR_AXI_GPIO_9_BASEADDR,1);//reset BRAM buffers
				Xil_Out32(XPAR_AXI_GPIO_9_BASEADDR,0);//reset BRAM buffers
				dram_ceiling = Xil_In32(XPAR_AXI_GPIO_20_BASEADDR) * 4 + dram_base; // 0xa004000;	//167788544	//set the dram_ceiling lower, there is less data to send
				//g_txcomplete = 0;
				break;
			case 4:
				while(1)
					{
						writePtrAA = Xil_In32 (XPAR_AXI_GPIO_11_BASEADDR);	//checks how many ints were written into the bram buffer
						readPtrAA = Xil_In32 (XPAR_AXI_GPIO_19_BASEADDR);		//checks how far we have read into the buffer (0)
						if((writePtrAA - readPtrAA) >= 4095)	//tells when the AA integrator has written a full buffer (can be out of sync with other integrators)
						{
							break;
						}
					}
				//sleep(2);
				Xil_Out32(XPAR_AXI_GPIO_9_BASEADDR,1);	//reset BRAM buffers
				Xil_Out32(XPAR_AXI_GPIO_9_BASEADDR,0);	//reset BRAM buffers
				break;
			default:
				g_txcomplete = 0;
				g_menuSel = 102;	//indicates mode is incorrect
				return ERR_OK;
				break;
			}
		}

		for(dram_addr = dram_base; dram_addr <= dram_ceiling; dram_addr+=4)
		{
			dat = Xil_In32(dram_addr);
			sprintf(data, "%d\n", dat);

			err = tcp_write(tpcb, (void*)data, strlen(data), 0x01);
			if(err != ERR_OK)
			{
				g_buffer_addr = dram_addr;	//no space in the tcp send buffer, track the address we stopped at
				break;
			}
		}
		err = tcp_write(tpcb, (void *)cDone, strlen(cDone), 0x01);	//put in a "finished" set of bits/bytes at the end to indicate transmission is complete
	}
	else	//Otherwise come here for the polling loop
	{
		if((p->len) < 9)	//check that the packet is int size or less
			g_menuSel = strtol(buffer, &pEnd, 10);	//gjs
		else
			g_menuSel = 99999;	//indicate that we didn't read a value from the buffer

		/* echo back the payload */
		/* in this case, we assume that the payload is < TCP_SND_BUF */
		if (tcp_sndbuf(tpcb) > p->len) {
			//err = tcp_write(tpcb, p->payload, p->len, 1);	//don't echo anything back
			//err = tcp_write(tpcb, 0x1, p->len, 1);
		} else
			xil_printf("no space in tcp_sndbuf\n\r");
	}

	/* free the received pbuf */
	pbuf_free(p);
	free (buffer);
	return ERR_OK;
}

err_t accept_callback(void *arg, struct tcp_pcb *newpcb, err_t err)
{
	static int connection = 1;

	/* set the receive callback for this connection */
	tcp_recv(newpcb, recv_callback);

	/* just use an integer number indicating the connection id as the
	   callback argument */
	tcp_arg(newpcb, (void*)connection);

	/* increment for subsequent accepted connections */
	connection++;

	return ERR_OK;
}


int start_application()
{
	struct tcp_pcb *pcb;
	err_t err;
	unsigned port = 7;

	/* create new TCP PCB structure */
	pcb = tcp_new();
	if (!pcb) {
		xil_printf("Error creating PCB. Out of Memory\n\r");
		return -1;
	}

	/* bind to specified @port */
	err = tcp_bind(pcb, IP_ADDR_ANY, port);
	if (err != ERR_OK) {
		xil_printf("Unable to bind to port %d: err = %d\n\r", port, err);
		return -2;
	}

	/* we do not need any arguments to callback functions */
	tcp_arg(pcb, NULL);

	/* listen for connections */
	pcb = tcp_listen(pcb);
	if (!pcb) {
		xil_printf("Out of memory while tcp_listen\n\r");
		return -3;
	}

	/* specify callback to use for incoming connections */
	tcp_accept(pcb, accept_callback);

	xil_printf("TCP echo server started @ port %d\n\r", port);

	return 0;
}
