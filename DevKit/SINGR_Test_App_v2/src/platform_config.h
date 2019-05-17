#ifndef __PLATFORM_CONFIG_H_
#define __PLATFORM_CONFIG_H_

#define STDOUT_IS_PS7_UART
#define UART_DEVICE_ID 0

//This was missing from the platform_config.h file generated for the project gjs 4/17
#define PLATFORM_EMAC_BASEADDR XPAR_XEMACPS_0_BASEADDR

//this was missing, add it as well gjs 4/17
#define PLATFORM_ZYNQ

#endif
