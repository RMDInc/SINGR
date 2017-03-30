/*
 * readEtherPoll.c
 *
 *  Created on: Feb 24, 2017
 *      Author: GStoddard
 */

#include "readEtherPoll.h"

extern int g_menuSel;

int readEtherPoll()
{
	//reset global variable
	g_menuSel = 99999;

	/* receive and process packets */
	while (1) {
		if (TcpFastTmrFlag) {
			tcp_fasttmr();
			TcpFastTmrFlag = 0;
		}
		if (TcpSlowTmrFlag) {
			tcp_slowtmr();
			TcpSlowTmrFlag = 0;
		}
		xemacif_input(echo_netif);
		transfer_data();

		if(g_menuSel < 10000 && g_menuSel >= -200)	//if we don't have the correct size menu select variable, keep waiting for input? //increased range on both sides of 0
		{											//essentially, if the global is set, we have received something
			break;
		}
	}

	return 0;
}
