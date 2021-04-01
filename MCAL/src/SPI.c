/*
 * SPI.c
 *
 *  Created on: Nov 22, 2020
 *      Author: Options
 */
#include"SPI.h"

void SPI2_init(SPI_Mode mode){
	RCC->AHB1ENR	|=RCC_AHB1ENR_GPIOBEN;
	RCC->AHB1ENR	|=RCC_AHB1ENR_GPIOCEN;
	//rcc for spi2
	RCC->APB1ENR	|=RCC_APB1ENR_SPI2EN;
	//	pB10 clk
	GPIOB->MODER	&= ~(3<<(10*2));
	GPIOB->MODER	|= (2<<(10*2));
	//pc3 MOSI
			//GPIOC->MODER	&= ~(3<<(3*2));
			//GPIOC->MODER	|= (2<<(3*2));

			GPIOC->MODER &= ~(0xF << (2 * 2));
				GPIOC->MODER |= (0xA << (2 * 2));


			//pcS MISO
	//GPIOC->MODER	&= ~(3<<(2*2));
	//GPIOC->MODER	|= (2<<(2*2));


	//aRTINAIVE
	//PB10
	GPIOB->AFR[1]	&= ~(0xF<<(2*4));
	GPIOB->AFR[1]	|= (0x5<<(2*4));
	//PC2
	GPIOC->AFR[0]	&= ~(0xF<<(2*4));
	GPIOC->AFR[0]	|= (0x5<<(2*4));
	//PC3
	GPIOC->AFR[0]	&= ~(0xF<<(3*4));
	GPIOC->AFR[0]	|= (0x5<<(3*4));

switch (mode) {
	case MASTER_MODE:
		// highest psc
		SPI2->CR1 |= SPI_CR1_BR;
		//slave select mannagment
		SPI2->CR1 |= SPI_CR1_SSM;
		//internal slave select
		SPI2->CR1 |= SPI_CR1_SSI;
		//master bit
		SPI2->CR1 |= SPI_CR1_MSTR;
		break;
	case SLAVE_MODE:
		SPI2->CR1 &=~ SPI_CR1_MSTR;
			break;
	default:
		break;
}
//enable spi
SPI2->CR1 |= SPI_CR1_SPE;
delayMs(100);
}

uint8_t SPI2_Tranceive(uint8_t data){
SPI2->DR =data;
while(!(SPI2->SR&SPI_SR_TXE));
while(!(SPI2->SR&SPI_SR_RXNE));
return SPI2->DR;

}
