/*
 * readEtherPoll.h
 *
 *  Created on: Feb 24, 2017
 *      Author: GStoddard
 */

#ifndef READETHERPOLL_H_
#define READETHERPOLL_H_

#include <stdio.h>
#include "xparameters.h"
#include "netif/xadapter.h"
#include "platform.h"
#include "platform_config.h"

#include "lwip/tcp.h"
#include "xil_cache.h"

/* Function declarations */
int readEtherPoll();
int transfer_data();
void tcp_fasttmr(void);
void tcp_slowtmr(void);

/* Variable Declarations */
extern volatile int TcpFastTmrFlag;
extern volatile int TcpSlowTmrFlag;
static struct netif server_netif;
struct netif *echo_netif;

#endif /* READETHERPOLL_H_ */
