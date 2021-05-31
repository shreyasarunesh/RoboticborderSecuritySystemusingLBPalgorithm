#include<LPC17xx.h>
#include<stdio.h>
#include "ocf_lpc176x_lib.h"
#define	Ref_Vtg		3.300


void delay(unsigned int r1);
void UART0_Init(void);
void UART1_Init(void);
void turn_left(void);
void turn_right(void);
void forward(void);
void reverse(void);
void hold(void);
void release(void);

unsigned long int r=0, i = 0,z=0,j;
unsigned char tx0_flag=0;
unsigned char rxdata;
unsigned char tx_flag;


int main(void)
{


while(1)
	
	{
         if(rxdata=='L')
		{
				turn_left();
				rxdata=0;
        }
        if(rxdata=='R')
		{
			turn_right();
			rxdata=0;
		}
        if(rxdata=='H')
		{
			hold();
			rxdata=0;
		}
		if(rxdata=='r')
		{
			release();
			rxdata=0;
		}
		if(rxdata=='F')
		{
			forward();
			rxdata=0;
			tx_flag=0xff;
		}
		if(rxdata=='B')
		{
			reverse();
			rxdata=0;
		}

    }

//
void turn_left(void)
{
LPC_GPIO1->FIOCLR =0x0F000000;
LPC_GPIO1->FIOSET =0x08000000;	

}
//
void turn_right(void)
{
LPC_GPIO1->FIOCLR =0x0F000000;
LPC_GPIO1->FIOSET =0x02000000;	
}

//
void forward(void)
{
LPC_GPIO1->FIOCLR =0x0A000000;
LPC_GPIO1->FIOSET =0x0F000000;	

}
//
void reverse(void)
{
LPC_GPIO1->FIOCLR =0x0F000000;
LPC_GPIO1->FIOSET =0x08000000;	
	
}

	
}