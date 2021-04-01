/*
 * WIFI.c
 *
 *  Created on: Nov 24, 2020
 *      Author: MahmoudH
 */

#include "WIFI.h"
/* timeout in ms */
uint8_t WIFI_SendCmd(uint8_t* cmd, uint8_t* expResp, uint32_t timeout){
	uint8_t	status 		= 0;
	uint8_t	data 		= 0;
	uint32_t compInd 	= 0;
	uint32_t len        = strlen(expResp);
	Uart_SendString(USART2,cmd);
	SysTick_Restart();
	/*\r\nOK\r\n*/
	while(SysTick_GetTicks() < timeout && status == 0){
		if(compInd < len){
			if(Uart_ReceiveByte_Unblock(USART2,&data))
			{
				if(data == expResp[compInd]){
					compInd++;
				}
				else{
					compInd = 0;
				}
			}
		}
		else if(compInd == len){
			status = 1;
		}
	}
	return status;
}
