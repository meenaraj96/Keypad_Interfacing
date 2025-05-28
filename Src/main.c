/*
 * set 1 in Rows(PC0-PC3) - 	*portcODR|=0x0f;
 * Set 0 for row(PC0-PC3) - each row at a time
 * Send 1 to column(PC4-PC7)
 *
 * 			 1
 * 			 |		|	 |		|
 * 			 |		|	 |		|
 * PC0-------1------2----3------A-------0
 * 			 |		|	 |		|
 * PC1-------4------5----6------B-------1
 * 			 |		|	 |		|
 * PC2-------7------8----9------C-------1
 * 			 |		|	 |		|
 * PC3-----Start----0---Stop----D-------1
 *			 |		|	 |		|
 * PC4-------|		|	 |		|
 * PC5--------------|	 |		|
 * PC6-------------------|		|
 * PC7--------------------------|
 *
 */

#include <stdint.h>
#include <stdio.h>

void delay(void)
{
	for (volatile uint32_t i=0;i<300000;i++);
}

int main(void)
{
	//RCC - 0x4002 3800 , Address offset: 0x30
	uint32_t *portcAHB1ENR =(uint32_t*)0x40023830;

	//GPIOC - 0x4002 0800
	uint32_t *portcMODER=(uint32_t*)0x40020800; //Port C - 0x0000 0000
	uint32_t *portPUPDR=(uint32_t*)0x4002080C; //Address offset: 0x0C

	uint32_t *portcODR=(uint32_t*)0x40020814; //Address offset: 0x14
	uint32_t *portcIDR=(uint32_t*)0x40020810; //Address offset: 0x10


	// Enable the peripheral clock of GPIOC Register
	//*portcAHB1ENR|=0X04;
	*portcAHB1ENR  |= (1<<2); //GPIOCEN - pin 2

	//configure COLUMN GPIO IN INPUT MODE(00) PC4-PC7 (Pin 8 to Pin 15) - 0000 0000
	//configure ROW  GPIO IN OUTPUT MODE(01)  PC0-PC3 (Pin 0 to Pin 7) - 0101 0101
	//pin 16 to 31 free
	*portcMODER &= 0XFFFF0000; //clear
	*portcMODER |= 0X00000055; //Set respective values

	//pullup(01) for input PC4-PC7 (0101 0101), no pullup(00) for output PC0-PC3(0000 0000)
	*portPUPDR &= 0XFFFF0000; //clear
	*portPUPDR |= 0X00005500; //Set respective values

	while(1)
	{
		//MAKE R1 LOW
		*portcODR|=0x0f; //set 1 in Rows(PC0-PC3) - 0000 1111
		*portcODR &= ~(1<<0); //Set 0 for row PC0 - 0000 1110

		//IDR = 0 (Button Pressed) , IDR = 1 (Button not Pressed)
		if(!(*portcIDR & (1 <<4 ))) //0001 0000 - Send 1 to column PC4
		{
			//key 1 is pressed
			delay();
			printf("1 \n");
		}
		if(!(*portcIDR & (1 <<5 ))) //0010 0000 - Send 1 to column PC5
		{
			//key 2 is pressed
			delay();
			printf("2 \n");
		}
		if(!(*portcIDR & (1 <<6 ))) //0100 0000 - Send 1 to column PC6
		{
			//key 3 is pressed
			delay();
			printf("3 \n");
		}
		if(!(*portcIDR & (1 <<7 ))) //1000 0000 - Send 1 to column PC7
		{
			//key A is pressed
			delay();
			printf("A \n");
		}


		//MAKE R2 LOW
		*portcODR|=0x0f; //set 1 in Rows(PC0-PC3) - 0000 1111
		*portcODR &= ~(1<<1); //Set 0 for row PC1 - 0000 1101

		if(!(*portcIDR & (1 <<4 ))) //0001 0000 - Send 1 to column PC4
		{
			//key 4 is pressed
			delay();
			printf("4 \n");
		}
		if(!(*portcIDR & (1 <<5 ))) //0010 0000 - Send 1 to column PC5
		{
			//key 5 is pressed
			delay();
			printf("5 \n");
		}
		if(!(*portcIDR & (1 <<6 ))) //0100 0000 - Send 1 to column PC6
		{
			//key 6 is pressed
			delay();
			printf("6 \n");
		}
		if(!(*portcIDR & (1 <<7 ))) //1000 0000 - Send 1 to column PC7
		{
			//key B is pressed
			delay();
			printf("B \n");
		}


		//MAKE R3 LOW
		*portcODR|=0x0f; //set 1 in Rows(PC0-PC3) - 0000 1111
		*portcODR &= ~(1<<2); //Set 0 for row PC2 - 0000 1011

		if(!(*portcIDR & (1 <<4 ))) //0001 0000 - Send 1 to column PC4
		{
			//key 7 is pressed
			delay();
			printf("7 \n");
		}
		if(!(*portcIDR & (1 <<5 ))) //0010 0000 - Send 1 to column PC5
		{
			//key 8 is pressed
			delay();
			printf("8 \n");
		}
		if(!(*portcIDR & (1 <<6 ))) //0100 0000 - Send 1 to column PC6
		{
			//key 9 is pressed
			delay();
			printf("9 \n");
		}
		if(!(*portcIDR & (1 <<7 ))) //1000 0000 - Send 1 to column PC7
		{
			//key C is pressed
			delay();
			printf("C \n");
		}


		//MAKE R4 LOW
		*portcODR|=0x0f; //set 1 in Rows(PC0-PC3) - 0000 1111
		*portcODR &= ~(1<<3); //Set 0 for row PC3 - 0000 0111

		if(!(*portcIDR & (1 <<4 ))) //0001 0000 - Send 1 to column PC4
		{
			//key start is pressed
			delay();
			printf("start \n");
		}
		if(!(*portcIDR & (1 <<5 ))) //0010 0000 - Send 1 to column PC5
		{
			//key 0 is pressed
			delay();
			printf("0 \n");
		}
		if(!(*portcIDR & (1 <<6 ))) //0100 0000 - Send 1 to column PC6
		{
			//key stop is pressed
			delay();
			printf("stop \n");
		}
		if(!(*portcIDR & (1 <<7 ))) //1000 0000 - Send 1 to column PC7
		{
			//key D is pressed
			delay();
			printf("D \n");
		}

	}
}
