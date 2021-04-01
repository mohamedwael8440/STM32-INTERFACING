/*
 * seqment.h
 *
 *  Created on: Nov 9, 2020
 *      Author: Options
 */

#ifndef INC_SEQMENT_H_
#define INC_SEQMENT_H_
#include "stm32f4xx.h"
#include <delay.h>
//#define DATA_MASK 0x1fe0 		// to out one for 8 leds of 7-seq from 5to 12
#define SEG_DATA_ODR_MASK (0xff<<5)	// to out one for 8 leds of 7-seq from 5to 12
#define SEG_DATA_SHIFT    5
#define SEG_POS_SHIFT    12

#define SEG_DATA_GPIO	GPIOC
#define SEG_POS_GPIO	GPIOB
#define SEG_DATA_RCC	RCC_AHB1ENR_GPIOCEN
#define SEG_POS_RCC     RCC_AHB1ENR_GPIOBEN  //
#define SEG_DATA_MODER_OUT_MASK 	(0X5555<<(SEG_DATA_SHIFT*2)) ///01 01 01 01 01 01 FOR  OUT DIRECTION
#define SEG_DATA_MODER_MASK 	(0XFFFF<<(SEG_DATA_SHIFT*2))//TO SET 0 FOR ALL
#define SEG_POS_ODR_MASK  0xf<<SEG_POS_SHIFT	//to start from pin 12
#define SEG_POS_MODER_MASK	(0XFF<<(SEG_POS_SHIFT*2))//TO SET 0 FOR ALL
#define SEG_POS_MODER_OUT_MASK	(0X55<<(SEG_POS_SHIFT*2))

#define NUM_0	0x3f
#define NUM_1	0x06
#define NUM_2	0x5b
#define NUM_3	0x4f
#define NUM_4	0x66
#define NUM_5	0x6d
#define NUM_6	0x7d
#define NUM_7	0x07
#define NUM_8	0x7f
#define NUM_9	0x6f
#define DOT		0x80

void Segment_Init(void);
void Segment_Display(uint8_t value, uint8_t position);
// data active high     pc 5:12
// pos active low       PB12:15

#endif /* INC_SEQMENT_H_ */
