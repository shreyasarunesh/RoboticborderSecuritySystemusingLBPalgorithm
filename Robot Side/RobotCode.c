#include<LPC17xx.h>
#include<stdio.h>
#include "ocf_lpc176x_lib.h"
#define	Ref_Vtg		3.300
#define TRIG1 (1<<10) //P0.10
#define ECHO1 (1<<11) //P0.11
#define TRIG2 (1<<19) //P0.19
#define ECHO2 (1<<20) //P0.20

void delay(unsigned int r1);
void UART0_Init(void);
void UART1_Init(void);
void turn_left(void);
void turn_right(void);
void forward(void);
void reverse(void);
void hold(void);
void release(void);
void arm_forward(void);
void arm_backward(void);
void temp_value(void);
void stop(void);
void stop2(void);

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
        if(rxdata=='f')
		{
			arm_forward();
			rxdata=0;
		}
		if(rxdata=='b')
		{
			arm_backward();
			rxdata=0;
        }

        if(rxdata=='T')
		{
			temp_value();
			tx0_flag = 0;
			LPC_UART0->THR='T';
			while(tx0_flag==0x00);
			tx0_flag=0;
//			delay(250);
			//
			LPC_UART0->THR=vtg[0];
			while(tx0_flag==0x00);
			tx0_flag=0;
//			delay(250);
			//
			LPC_UART0->THR=vtg[1];
			while(tx0_flag==0x00);
			tx0_flag=0;
			rxdata=0;
			
			LPC_UART0->THR=vtg[2];
			while(tx0_flag==0x00);
			tx0_flag=0;
			rxdata=0;
			delay(250);
		}

        if((LPC_GPIO4->FIOPIN&0x10000000)==0x00000000) //metaldetector
 			{
				if(tx_flag == 0xff)
				{
					LPC_UART0->THR='m';
					while(tx0_flag==0x00);
					tx0_flag=0;
					tx_flag=0;
				//	delay(250);
				}
			}
			else
			{
				if(tx_flag == 0x00)
				{
					LPC_UART0->THR='M';
					while(tx0_flag==0x00);
					tx0_flag=0;
					tx_flag = 0xff;
				 //  delay(250);
				}

                if((LPC_GPIO4->FIOPIN&0x10000000)==0x00000000) //metaldetector
 			{
				if(tx_flag == 0xff)
				{
					LPC_UART0->THR='m';
					while(tx0_flag==0x00);
					tx0_flag=0;
					tx_flag=0;
				//	delay(250);
				}
			}
			else
			{
				if(tx_flag == 0x00)
				{
					LPC_UART0->THR='M';
					while(tx0_flag==0x00);
					tx0_flag=0;
					tx_flag = 0xff;
				 //  delay(250);
				}
		}
		}

    }

void UART0_Init(void)
{
	LPC_SC->PCONP |= 0x00000008;			//UART0 peripheral enable
	LPC_PINCON->PINSEL0 |= 0x00000050;
	LPC_UART0->LCR = 0x00000083;			//enable divisor latch, parity disable, 1 stop bit, 8bit word length
	LPC_UART0->DLM = 0X00; 
	LPC_UART0->DLL = 0x1A;      			//select baud rate 9600 bps
	LPC_UART0->LCR = 0X00000003;
	LPC_UART0->FCR = 0x07;
	LPC_UART0->IER = 0X03;	   				//select Transmit and receive interrupt

	NVIC_EnableIRQ(UART0_IRQn);				//Assigning channel
}

void UART0_IRQHandler(void)
{
	unsigned long Int_Stat;
	Int_Stat = LPC_UART0->IIR;				//reading the data from interrupt identification register
	Int_Stat = Int_Stat & 0x06;				//masking other than txmit int & rcve data indicator

	if((Int_Stat & 0x02)== 0x02)			//transmit interrupt
	{
		tx0_flag = 0xff;
	}
	else
	{
		rxdata=LPC_UART0->RBR;
	}		
}
//
void UART1_Init(void)
{
	LPC_SC->PCONP |= 0x00000010;			//UART0 peripheral enable
	LPC_PINCON->PINSEL4 |= 0x0000000A;
	LPC_UART1->LCR = 0x00000083;			//enable divisor latch, parity disable, 1 stop bit, 8bit word length
 	LPC_UART1->DLM = 0X00; 
	LPC_UART1->DLL = 0x1A;      			//select baud rate 9600 bps
	LPC_UART1->LCR = 0X00000003;
	LPC_UART1->FCR = 0x07;
	LPC_UART1->IER = 0X03;	   				//select Transmit and receive interrupt

	NVIC_EnableIRQ(UART1_IRQn);				//Assigning channel
}
//
void UART1_IRQHandler(void)
{
	unsigned long Int_Stat;
	Int_Stat = LPC_UART1->IIR;				//reading the data from interrupt identification register
	Int_Stat = Int_Stat & 0x06;				//masking other than txmit int & rcve data indicator

	if((Int_Stat & 0x02)== 0x02)			//transmit interrupt
	{
		tx1_flag = 0xff;
	}
	else
	{
		uart1rx[z]=LPC_UART1->RBR;
		z++;
	}		
}
//
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

void hold(void)
{
LPC_GPIO2->FIOCLR = 0x00003C00;
LPC_GPIO2->FIOSET = 0x00002000;	
	
}
//
void release(void)
{
LPC_GPIO2->FIOCLR = 0x00003C00;
LPC_GPIO2->FIOSET = 0x00001000;	
	
}
//

void arm_forward(void)
{
LPC_GPIO2->FIOCLR = 0x00003C00;
LPC_GPIO2->FIOSET = 0x00000800;	
	
}
//
void arm_backward(void)
{
LPC_GPIO2->FIOCLR = 0x00003C00;
LPC_GPIO2->FIOSET = 0x00000400;	
	
}

void temp_value(void)
{
	  LPC_ADC->ADCR = (1<<5)|(1<<21)|(1<<24);									//0x01200001;//ADC0.5, start conversion and operational	
		for(i=0;i<2000;i++);																								//delay for conversion
		while((adc_temp = LPC_ADC->ADGDR) == 0x80000000);		//wait till 'done' bit is 1, indicates conversion complete
		adc_temp = LPC_ADC->ADGDR;
		adc_temp >>= 4;
		adc_temp &= 0x00000FFF;																	//12 bit ADC
		in_vtg1 = ((adc_temp * 330)/4096);	
	  sprintf(vtg,"%3.2f",in_vtg1);
	
}
//
//

void automatic(void)
{
		LPC_GPIO0->FIOPIN |= TRIG1;
		delayUS(10);
		LPC_GPIO0->FIOCLR |= TRIG1;

		while(!(LPC_GPIO0->FIOPIN & ECHO1)); //Wait for a HIGH on ECHO pin
		startTimer0(); //Start counting
		while(LPC_GPIO0->FIOPIN & ECHO1); //Wait for a LOW on ECHO pin
		echoTime1 = stopTimer0(); //Stop counting and save value(us) in echoTime

			
		//sprintf(vtg1,"%3.2f",distance2);

//		LPC_TIM0->TC = 0X00;

}