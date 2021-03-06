/*
 ******************************************************************************
File:     main.c
Info:     Generated by Atollic TrueSTUDIO(R) 9.3.0   2020-11-04

The MIT License (MIT)
Copyright (c) 2019 STMicroelectronics

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

 ******************************************************************************
 */
/* os includes*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
/* Includes */
#include "stm32f4xx.h"
#include "delay.h"
#include "board.h"
#include "segment.h"
#include "keypad.h"
#include "LCD.h"
#include "ADC.h"
#include "timer.h"
#include "ultrasonic.h"
#include "Servo.h"
#include "uart.h"
#include "SPI.h"
#include "i2c.h"

/* Private macro */
/* Private variables */
/* Private function prototypes */
void T_SMS(void* pvData);
void T_Server(void* pvData);
//void T_buz(void* pvData);
//void T_led2(void* pvData);
//void T_5(void* pvData);
//void T_rel(void* pvData);

/*OS Objects Decl. like the semaphore AND MUTEX */
xSemaphoreHandle		bsResource=NULL;

/* Private functions */

/**
 **===========================================================================
 **
 **  Abstract: main program
 **
 **===========================================================================
 */
void BTN_Center_Handler(void){
	Leds_Toggle(0xFF);
}
void BTN_Up_Handler(void){
	Buz_Toggle();
}
void BTN_Down_Handler(void){
	Relay_Toggle();
}
void BTN_Left_Handler(void){
	Leds_Toggle(0xF0);
}
void BTN_Right_Handler(void){
	Leds_Toggle(0x0F);
}
void myNotif(void){
	Leds_Toggle(0x0F);
}
/*interrupt handler for systick */
//uint16_t volatile tickCount=0;
//void SysTick_Handler(void){
//	tickCount++;
//}

int main(void)
{
//	uint8_t key = 0;
//	uint16_t adc_val , temp= 0;
//
//	uint8_t dety6=0, dety7=0 ;
	/* Clock -> Internal 16 MHz */
	RCC_DeInit();				/* Adapt PLL to the internal 16 MHz RC oscillator */
	SystemCoreClockUpdate();	/* Update SystemCoreClock */
Leds_Init(0xff);
Buz_Init();
Btn_Init(BTN_RIGHT);
Btn_Init(BTN_LEFT);
Btn_Init(BTN_UP);
Btn_Init(BTN_DOWN);
Relay_Init();
Uart_Init(USART2,9600);

Uart_SendString(USART2,"rtos stared\n");

/* os objects init and creation*/
//vSemaphoreCreateBinary() make sem init by 1 or z for 1 for resource and zero for events
vSemaphoreCreateBinary(bsResource,1);

//xSemaphoreCreateBinary() make sem init by 0 for events
//bsBtnPreesedEvent = xSemaphoreCreateBinary();
/*Create Tasks*/
xTaskCreate(T_SMS,"T_1",100,NULL,1,NULL);//100word stack size , 1 prority,
xTaskCreate(T_Server,"T_2",100,NULL,2,NULL);//100word stack size , 1 prority,
//xTaskCreate(T_buz,"T_3",100,NULL,3,NULL);//100word stack size , 1 prority,
//xTaskCreate(T_led2,"T_4",100,NULL,4,NULL);//100word stack size , 1 prority,
////xTaskCreate(T_5,"T_5",100,NULL,5,NULL);//100word stack size , 1 prority,
//xTaskCreate(T_rel,"T_6",100,NULL,6,NULL);//100word stack size , 1 prority,
//x for return data type defined in rtos
/* start os or scheduler*/
vTaskStartScheduler();// v for return void
while(1){

}


}
void T_SMS(void* pvData){

	while(1){
		if(xSemaphoreTake(bsResource,portMAX_DELAY)){//portMAX_DELAY give me the max delay out time
		Uart_SendString(USART2," AT+SMS1...\n");
		Uart_SendString(USART2," AT+SMS2...\n");
		xSemaphoreGive(bsResource);
		}
}
}



//event task , always in wating untill event is occure
void T_Server(void* pvData){

	while(1){
		if(xSemaphoreTake(bsResource,portMAX_DELAY)){
		Uart_SendString(USART2," AT+server1...\n");
		Uart_SendString(USART2," AT+server2...\n");
		//vTaskDelay(5);//os delay 250 tick
		xSemaphoreGive(bsResource);
		}
		vTaskDelay(5);
		}
}

//void vApplicationIdleHook(void){
//	Uart_SendString(USART2,"ideal task ...\n");
////no vtask delay here
//}
