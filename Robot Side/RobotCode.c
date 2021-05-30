#include<LPC17xx.h>
#include<stdio.h>

void delay(unsigned int r1);
void UART0_Init(void);
void UART1_Init(void);
void turn_left(void);
void turn_right(void);
void forward(void);
void reverse(void);

unsigned long int r=0, i = 0,z=0,j;
unsigned char tx0_flag=0;
unsigned char rxdata;
unsigned char tx_flag;
unsigned char tx1_flag;
unsigned char uart1rx[255];
unsigned char lat[40];
unsigned char vtg1;
unsigned char vtg[3];
unsigned char vtg2;
float in_vtg1;
unsigned int adc_temp;
int echoTime1=0,echoTime2=0;
float distance1=0,distance2=0;

int main(void)
{
initTimer0(); //Init Timer for delay functions - defined in ocf_lpc176x_lib.c
initTimer1(); //Init Timer for delay functions - defined in ocf_lpc176x_lib.c
//LPC_GPIO1->FIODIR = 0x07F80000;
UART0_Init();
UART1_Init();	
tx_flag = 0xff;	
LPC_GPIO1->FIODIR = 0x0F000000;
LPC_GPIO2->FIODIR = 0x00003C00;
LPC_PINCON->PINSEL3 |= 0xC0000000;		//P1.31 as AD0.5
LPC_SC->PCONP |= (1<<12);				//enable the peripheral ADC

LPC_GPIO0->FIODIR |= TRIG1;    //Set P0.2(TRIG) as output
LPC_GPIO0->FIODIR &= ~(ECHO1); //Set P0.3(ECHO) as input (explicitly)
LPC_GPIO0->FIOCLR |= TRIG1;    //Set P0.2 LOW initially

LPC_GPIO0->FIODIR |= TRIG2;    //Set P0.2(TRIG) as output
LPC_GPIO0->FIODIR &= ~(ECHO2); //Set P0.3(ECHO) as input (explicitly)
LPC_GPIO0->FIOCLR |= TRIG2;    //Set P0.2 LOW initially

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
LPC_GPIO1->FIOCLR =0x0F000000;
LPC_GPIO1->FIOSET =0x0A000000;	

}
//
void reverse(void)
{
LPC_GPIO1->FIOCLR =0x0F000000;
LPC_GPIO1->FIOSET =0x05000000;	
	
}
