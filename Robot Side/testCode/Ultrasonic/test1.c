#include<LPC17xx.h>
#include "AN_lcd.h"
#include<stdio.h>
#include "ocf_lpc176x_lib.h"
#define	Ref_Vtg		3.300
#define TRIG (1<<10) //P0.10
#define ECHO (1<<11) //P0.11



int main(void)


{
	int echoTime=0;
	float distance=0;
	unsigned int i;
	float in_vtg,in_vtg1,in_vtg2;
	unsigned char vtg[7],dval[7], blank[]="   ";
	unsigned char Msg3[11] = {"distance:"};
	initTimer0(); //Init Timer for delay functions - defined in ocf_lpc176x_lib.c
	
    lcd_init();
	temp1 = 0x80;
	lcd_com();
	delay_lcd(800);
	lcd_puts(&Msg3[0]);

LPC_GPIO0->FIODIR |= TRIG;    //Set P1.19(TRIG) as output
LPC_GPIO0->FIODIR &= ~(ECHO); //Set P1.20(ECHO) as input (explicitly)
LPC_GPIO0->FIOCLR |= TRIG;    //Set P1.20 LOW initially


	while(1)
	{
		LPC_GPIO0->FIOPIN |= TRIG;
		delayUS(10);
		LPC_GPIO0->FIOCLR |= TRIG;

		while(!(LPC_GPIO0->FIOPIN & ECHO)); //Wait for a HIGH on ECHO pin
		startTimer0(); //Start counting
		while(LPC_GPIO0->FIOPIN & ECHO); //Wait for a LOW on ECHO pin
		echoTime = stopTimer0(); //Stop counting and save value(us) in echoTime

		distance = (0.0343 * echoTime)*10/2;	
		sprintf(vtg,"%d    ",distance);
		
		for(i=0;i<2000;i++);

		temp1 = 0xc0;
		lcd_com();
		delay_lcd(800);
		lcd_puts(&vtg[0]);

//		temp1 = 0xCa;
//		lcd_com();
//		lcd_puts(&blank[0]);
//
//		temp1 = 0xCB;
//		lcd_com();
//		delay_lcd(800);
//		lcd_puts(&dval[0]);

		for(i=0;i<200000;i++);
		for(i=0;i<7;i++)
		vtg[i] = dval[i] = 0x00;
		distance = 0;
	}
}

 



