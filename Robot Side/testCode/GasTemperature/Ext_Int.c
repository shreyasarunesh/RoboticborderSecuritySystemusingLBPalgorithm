/****************************************************
 * VIBRATOR CODE   
 * Developed by: 
 * Raghavendra Prasad Y, Bengaluru                    
 *---------------------------------------------------
 *****************************************************/

 #include<LPC17xx.h>
 #include "AN_LCD.h"
 #define THR_EMPTY 0x20 
 #define RRB_EMPTY 0x01

 void EINT3_IRQHandler(void);
 void time_int(void);
 void uart_init(void);
 void TIMER0_IRQHandler(void);
 void TIMER1_IRQHandler(void);
 void TIMER2_IRQHandler(void);
 void count_loop(void);
 unsigned int key_read;
 unsigned int read_key,i;
 unsigned char set_value = 0;
 unsigned char sot_value = 0;
 unsigned char display = 0xff;
 unsigned char int_count = 0;
 unsigned char sot1,sot2,sot3,enter,sot1v,sot2v,sot3v,temp;
 unsigned char ser_con,ser_con1,buf1[8];
 unsigned char ser_add,ser_data,sot1d,sot2d,sot3d,int_flag;
 unsigned char dec_asci,no_data,ser_char,wait_data,wait_end,ser_data_count,write_data,read_data,ton_flag;
 float mul_val1;
//
 unsigned char Msg11[17] = "                ";
 unsigned char Msg21[17] = "                ";
 unsigned char arr3[]	 = "SOT1 PVALUE     ";
 unsigned char arr4[]	 = "SOT1 SVALUE     ";
 unsigned char arr5[]	 = "SOT2 PVALUE     ";
 unsigned char arr6[]	 = "SOT2 SVALUE     ";
 unsigned char arr7[]	 = "SOT3 PVALUE     ";
 unsigned char arr8[]	 = "SOT3 SVALUE     ";
 unsigned char arr9[]	 = " SELECT THE SOT ";
 unsigned char arra[]	 = ">SOT1<          ";
 unsigned char arrb[]	 = "     >SOT2<     ";
 unsigned char arrc[]	 = "          >SOT3<";
 unsigned char arrd[]	 = "   HMI CONTROL  ";
 unsigned char arre[]	 = " NO HMI CONTROL ";
 unsigned char arrf[]	 = "   press a key  ";
 unsigned char clrd[]	 = "                ";

 unsigned char disp[4];

 int main(void)
 {
	time_int();
	uart_init();

	no_data = 0x00;
	ser_char = 0x00;
	wait_data = 0x00;
	int_flag = 0x00;
	ser_data_count = 0x00;
//
	LPC_GPIO1->FIODIR = 0xC3FFC713;
	LPC_GPIO1->FIOCLR = 0x03E00000;
	LPC_GPIO1->FIOCLR = 0x001C0000;
	LPC_GPIO1->FIOCLR = 0xC0000000;
//
	LPC_PINCON->PINSEL0 = 0x40000050;
	LPC_PINCON->PINSEL1 = 0x01400001;
	LPC_PINCON->PINSEL2 = 0x00000000;
	LPC_PINCON->PINSEL3 = 0x00000000;
	LPC_PINCON->PINSEL4 = 0x01400000;	//01400015
	LPC_PINCON->PINSEL5 = 0x00000000;
	LPC_PINCON->PINSEL6 = 0x00000000;
	LPC_PINCON->PINSEL7 = 0x00000000;
	LPC_PINCON->PINSEL8 = 0x00000000;
	LPC_PINCON->PINSEL9 = 0x00000000;

	lcd_init();
	if((LPC_GPIO0->FIOPIN & 0x00000200)	== 0x00000200)
	{
		dec_asci = 0x00;
		ser_con1 = 0x02;
	}
	else
	{
		dec_asci = 0xff;
		ser_con1 = 0x06;
	}
	if((LPC_GPIO0->FIOPIN & 0x00000080)	== 0x00000080)
	{
		mul_val1 = 156.86274509803921568627450980392;//173.91304347826086956521739130435
	}
	else
	{
		mul_val1 = 62.745098039215686274509803921569;
	}
	if((LPC_GPIO0->FIOPIN & 0x00000010)	== 0x00000010)
	{
			temp1 = 0x80;								//point to first line of LCD
			lcd_com();
			delay_lcd(800);
			lcd_puts(&arrd[0]);	 						//display the messsage
	}
	else
	{
			temp1 = 0x80;								//point to first line of LCD
			lcd_com();
			delay_lcd(800);
			lcd_puts(&arre[0]);	 						//display the messsage
	}
	for(i = 0;i<60000;i++);
	for(i = 0;i<60000;i++);
	for(i = 0;i<60000;i++);
	for(i = 0;i<60000;i++);
	temp1 = 0x80;								//point to first line of LCD
	lcd_com();
	delay_lcd(800);
	lcd_puts(&arrf[0]);	 						//display the messsage
	for(i = 0;i<60000;i++);
	for(i = 0;i<60000;i++);
// read the switch for the serial input
	key_read = LPC_GPIO0->FIOPIN;
	if((key_read	& 0x00800000)  == 0x00000000)
	{
		while((key_read & 0x00800000) == 0x00000000)
		{
			key_read = LPC_GPIO0->FIOPIN;
			wait_data = 0xff;
		}
	}
	while((wait_data == 0xff)&&(wait_end != 0xff))
	{
	    LPC_TIM3->TCR  = 0x01;  //* Start timer by setting the Counter Enable*/
		while ((wait_end != 0xff)&&(LPC_UART0->LSR & RRB_EMPTY) != RRB_EMPTY);
			ser_data = LPC_UART0->RBR;
		if(wait_end != 0xff)
		{
			LPC_TIM3->TC   = 0x00;
			if(ser_data_count < 16)
			{
				Msg11[ser_data_count] = ser_data;
			}
			else if(ser_data_count != 32)
			{
				Msg21[ser_data_count-16] = ser_data;
			}
			else
			{
				wait_end = 0xff;
				write_data = 0xff;
			}
			ser_data_count = ser_data_count + 1;
		}
 	}
	// check for the set switch
	//wait for ten sec with in 10 sec if i receive 32 characters then exit this loop
	//load blank space for eeprom if there is no alpha numeric value with in 10 sec
	//load default value if no input
	//continue  
		

	LPC_SC->EXTINT   = 0x00000002;		//writing 1 cleares the interrupt, get set if there is interrupt
	LPC_SC->EXTMODE  = 0x00000002;		//EINT3 is initiated as edge senitive, 0 for level sensitive
	LPC_SC->EXTPOLAR = 0x00000002;		//EINT3 is falling edge sensitive, 1 for rising edge
										// above registers, bit0-EINT0, bit1-EINT1, bit2-EINT2,bit3-EINT3	
	NVIC_EnableIRQ(EINT1_IRQn);			//core_cm3.h
//	NVIC_EnableIRQ(EINT2_IRQn);			//core_cm3.h


	LPC_UART0->IER = 0X03;	   		//select Transmit and receive interrupt
	NVIC_EnableIRQ(UART0_IRQn);		//Assigning channel
    LPC_TIM3->TCR  = 0x00;  		//* Stop timer by setting the Counter Enable*/
	LPC_TIM3->MR0  = 8000;			//time set for 500u sec
	while(1) 	
	{
		if(display == 0xff)
		{
			temp1 = 0x80;								//point to first line of LCD
			lcd_com();
			delay_lcd(800);
			lcd_puts(&Msg11[0]);	 						//display the messsage
			  
			temp1 = 0xC0;								//point to first line of LCD
			lcd_com();
			delay_lcd(800);
			lcd_puts(&Msg21[0]);	 						//display the messsage
			display = 0x00;
		 }
		key_read = LPC_GPIO0->FIOPIN;
//		read_key = key_read	& 0x00800000;
		if((key_read	& 0x00800000)  == 0x00000000)
		{
			while((key_read & 0x00800000) == 0x00000000)
			{
				key_read = LPC_GPIO0->FIOPIN;
			}
			set_value = 0xff;
			sot1 = 0xff;
			temp1 = 0x80;								//point to first line of LCD
			lcd_com();
			delay_lcd(800);
			lcd_puts(&arr9[0]);	 						//display the messsage
		}
		while(set_value == 0xff)
		{
			if(sot1 == 0xff)
			{
				temp1 = 0xC0;								//point to second line of LCD
				lcd_com();
				delay_lcd(800);
				lcd_puts(&arra[0]);	 						//display the messsage
			}
			else if(sot2 == 0xff)
			{
				temp1 = 0xC0;								//point to second line of LCD
				lcd_com();
				delay_lcd(800);
				lcd_puts(&arrb[0]);	 						//display the messsage
			}
			else if(sot3 == 0xff)
			{
				temp1 = 0xC0;								//point to second line of LCD
				lcd_com();
				delay_lcd(800);
				lcd_puts(&arrc[0]);	 						//display the messsage
			}
			key_read = LPC_GPIO0->FIOPIN;
			if((key_read & 0x00800000) == 0x00000000)
			{
				while((key_read & 0x00800000) == 0x00000000)
				{
					key_read = LPC_GPIO0->FIOPIN;
				}
				set_value = 0x00;
				display = 0xff;	
			}
			else if((key_read & 0x01000000) == 0x00000000)//inc key
			{
				while((key_read & 0x01000000) == 0x00000000)
				{
					key_read = LPC_GPIO0->FIOPIN;
				}
				if(sot1 == 0xff)
				{
					sot2 = 0xff;
					sot1 = 0x00;
				}
				else if(sot2 == 0xff)
				{
					sot2 = 0x00;
					sot3 = 0xff;
				}
				else if(sot3 == 0xff)
				{
					sot3 = 0x00;
					sot1 = 0xff;
				}
			}
			else if((key_read & 0x02000000) == 0x00000000)
			{
				while((key_read & 0x02000000) == 0x00000000)
				{
					key_read = LPC_GPIO0->FIOPIN;
				}
				if(sot1 == 0xff)
				{
					sot3 = 0xff;
					sot1 = 0x00;
				}
				else if(sot2 == 0xff)
				{
					sot2 = 0x00;
					sot1 = 0xff;
				}
				else if(sot3 == 0xff)
				{
					sot3 = 0x00;
					sot2 = 0xff;
				}
			}
			else if((key_read & 0x04000000) == 0x00000000)
			{
				enter = 0xff;
				set_value = 0x00;
				while((key_read & 0x04000000) == 0x00000000)
				{
					key_read = LPC_GPIO0->FIOPIN;
				}
			}
		}
		while(enter == 0xff)
		{
			if(sot1 == 0xff)
			{
				temp1 = 0x80;								//point to first line of LCD
				lcd_com();
				delay_lcd(800);
				lcd_puts(&arr3[0]);	 						//display the messsage
				  
				temp1 = 0xC0;								//point to first line of LCD
				lcd_com();
				delay_lcd(800);
				lcd_puts(&arr4[0]);	 						//display the messsage

				temp = sot1v;
				count_loop();
				temp1 = 0x8C;								//point to first line of LCD
				lcd_com();
				delay_lcd(800);
				lcd_puts(&disp[0]);	 						//display the messsage

			}	
			while(sot1 == 0xff)
			{
				if(sot1d == 0xff)
				{
					temp = sot1v;
					count_loop();
					temp1 = 0x8C;								//point to first line of LCD
					lcd_com();
					delay_lcd(800);
					lcd_puts(&disp[0]);	 						//display the messsage
					sot1d = 0x00;
				}
				key_read = LPC_GPIO0->FIOPIN;
				if((key_read & 0x01000000) == 0x00000000)//inc key
				{
					for(i = 0;i<15000;i++);
					key_read = LPC_GPIO0->FIOPIN;
					if((key_read & 0x01000000) == 0x0000000)//inc key
					{
						sot1v = sot1v + 1;
						for(i = 0;i<15000;i++);
						if(sot1v>254)
						{
							sot1v = 1;
						}
						if(sot1v < 1)
						{
							sot1v = 255;
						}
						temp = sot1v;
						count_loop();
						temp1 = 0xCC;								//point to first line of LCD
						lcd_com();
						delay_lcd(800);
						lcd_puts(&disp[0]);	 						//display the messsage
					}
				}
				else if((key_read & 0x02000000) == 0x00000000)
				{
					for(i = 0;i<15000;i++);
					key_read = LPC_GPIO0->FIOPIN;
					if((key_read & 0x02000000) == 0x00000000)//dec key
					{
						sot1v = sot1v - 1;
						for(i = 0;i<15000;i++);
						if(sot1v>254)
						{
							sot1v = 1;
						}
						if(sot1v < 1)
						{
							sot1v = 255;
						}
						temp = sot1v;
						count_loop();
						temp1 = 0xCC;								//point to first line of LCD
						lcd_com();
						delay_lcd(800);
						lcd_puts(&disp[0]);	 						//display the messsage
					}
				}
				else if((key_read & 0x04000000) == 0x00000000)
				{
					while((key_read & 0x04000000) == 0x00000000)
					{
						key_read = LPC_GPIO0->FIOPIN;
					}
					enter = 0x00;
					set_value = 0x00;
					display = 0xff;
					sot1 = 0x00;
					sot_value = 0xff;
				}
			}
			if(sot2 == 0xff)
			{
				temp1 = 0x80;								//point to first line of LCD
				lcd_com();
				delay_lcd(800);
				lcd_puts(&arr5[0]);	 						//display the messsage
				  
				temp1 = 0xC0;								//point to first line of LCD
				lcd_com();
				delay_lcd(800);
				lcd_puts(&arr6[0]);	 						//display the messsage
				temp = sot2v;
				count_loop();
				temp1 = 0x8C;								//point to first line of LCD
				lcd_com();
				delay_lcd(800);
				lcd_puts(&disp[0]);	 						//display the messsage
			}	
			while(sot2 == 0xff)
			{
				if(sot2d == 0xff)
				{
					temp = sot2v;
					count_loop();
					temp1 = 0x8C;								//point to first line of LCD
					lcd_com();
					delay_lcd(800);
					lcd_puts(&disp[0]);	 						//display the messsage
					sot2d = 0x00;
				}
				key_read = LPC_GPIO0->FIOPIN;
				if((key_read & 0x01000000) == 0x00000000)//inc key
				{
					for(i = 0;i<15000;i++);
					key_read = LPC_GPIO0->FIOPIN;
					if((key_read & 0x01000000) == 0x00000000)//inc key
					{
						sot2v = sot2v + 1;
						for(i = 0;i<15000;i++);
						if(sot2v>254)
						{
							sot2v = 1;
						}
						if(sot2v < 1)
						{
							sot2v = 255;
						}
						temp = sot2v;
						count_loop();
						temp1 = 0xCC;								//point to first line of LCD
						lcd_com();
						delay_lcd(800);
						lcd_puts(&disp[0]);	 						//display the messsage
					}
				}
				else if((key_read & 0x02000000) == 0x00000000)
				{
					for(i = 0;i<15000;i++);
					key_read = LPC_GPIO0->FIOPIN;
					if((key_read & 0x02000000) == 0x00000000)//dec key
					{
						sot2v = sot2v - 1;
						for(i = 0;i<15000;i++);
						if(sot2v>254)
						{
							sot2v = 1;
						}
						if(sot2v < 1)
						{
							sot2v = 255;
						}
						temp = sot2v;
						count_loop();
						temp1 = 0xCC;								//point to first line of LCD
						lcd_com();
						delay_lcd(800);
						lcd_puts(&disp[0]);	 						//display the messsage
					}
				}
				else if((key_read & 0x04000000) == 0x00000000)
				{
					while((key_read & 0x04000000) == 0x00000000)
					{
						key_read = LPC_GPIO0->FIOPIN;
					}
					enter = 0x00;
					set_value = 0x00;
					display = 0xff;
					sot2 = 0x00;
					sot_value = 0xff;
				}
			}
			if(sot3 == 0xff)
			{
				temp1 = 0x80;								//point to first line of LCD
				lcd_com();
				delay_lcd(800);
				lcd_puts(&arr7[0]);	 						//display the messsage
				  
				temp1 = 0xC0;								//point to first line of LCD
				lcd_com();
				delay_lcd(800);
				lcd_puts(&arr8[0]);	 						//display the messsage
				temp = sot3v;
				count_loop();
				temp1 = 0x8C;								//point to first line of LCD
				lcd_com();
				delay_lcd(800);
				lcd_puts(&disp[0]);	 						//display the messsage

			}	
			while(sot3 == 0xff)
			{
				if(sot3d == 0xff)
				{
					temp = sot3v;
					count_loop();
					temp1 = 0x8C;								//point to first line of LCD
					lcd_com();
					delay_lcd(800);
					lcd_puts(&disp[0]);	 						//display the messsage
					sot3d = 0x00;
				}
				key_read = LPC_GPIO0->FIOPIN;
				if((key_read & 0x01000000) == 0x00000000)//inc key
				{
					for(i = 0;i<15000;i++);
					key_read = LPC_GPIO0->FIOPIN;
					if((key_read & 0x01000000) == 0x00000000)//inc key
					{
						sot3v = sot3v + 1;
						for(i = 0;i<15000;i++);
						if(sot3v>254)
						{
							sot3v = 1;
						}
						if(sot3v < 1)
						{
							sot3v = 255;
						}
						temp = sot3v;
						count_loop();
						temp1 = 0xCC;								//point to first line of LCD
						lcd_com();
						delay_lcd(800);
						lcd_puts(&disp[0]);	 						//display the messsage
					}
				}
				else if((key_read & 0x02000000) == 0x00000000)
				{
					for(i = 0;i<15000;i++);
					key_read = LPC_GPIO0->FIOPIN;
					if((key_read & 0x02000000) == 0x00000000)//dec key
					{
						sot3v = sot3v - 1;
						for(i = 0;i<15000;i++);
						if(sot3v>254)
						{
							sot3v = 1;
						}
						if(sot3v < 1)
						{
							sot3v = 255;
						}
						temp = sot3v;
						count_loop();
						temp1 = 0xCC;								//point to first line of LCD
						lcd_com();
						delay_lcd(800);
						lcd_puts(&disp[0]);	 						//display the messsage
					}
				}
				else if((key_read & 0x04000000) == 0x00000000)
				{
					while((key_read & 0x04000000) == 0x00000000)
					{
						key_read = LPC_GPIO0->FIOPIN;
					}
					enter = 0x00;
					set_value = 0x00;
					display = 0xff;
					sot3 = 0x00;
					sot_value = 0xff;
				}
			}
		}
	}
 }

 void EINT1_IRQHandler(void)
 {
    unsigned int isrMask;

	isrMask = LPC_SC->EXTINT;		//cleares the interrupt
	LPC_SC->EXTINT = isrMask;
	LPC_GPIO1->FIOSET = 0xC3FC0000;
	LPC_TIM3->TCR  = 0x00;  //* Stop timer by setting the Counter Disable*/
	LPC_TIM3->TC   = 0x00;
	LPC_TIM2->TC   = 0x00;
	LPC_TIM1->TC   = 0x00;
	LPC_TIM0->TC   = 0x00;
	LPC_TIM3->MR0  = 6000;
	int_flag = 0xff;
	if(sot_value == 0xff)  //0xff
	{
		LPC_TIM0->MR0  = 71500-(sot1v * mul_val1);//80000-(sot1v * mul_val1);
		LPC_TIM1->MR0  = 71500-(sot2v * mul_val1);//80000-(sot2v * mul_val1);
		LPC_TIM2->MR0  = 71500-(sot3v * mul_val1);//80000-(sot3v * mul_val1);
		sot_value = 0x00;
	}
//	LPC_TIM0->TCR  = 0x00;  //* Start timer by setting the Counter Enable*/
//	LPC_TIM1->TCR  = 0x00;  //* Start timer by setting the Counter Enable*/
//	LPC_TIM2->TCR  = 0x00;  //* Start timer by setting the Counter Enable*/
	LPC_TIM3->TCR  = 0x01;  //* Start timer by setting the Counter Enable*/
 }

void time_int(void)
{
	LPC_SC->PCONP |= 0x00C0809E;			//TIMER0,1,2,3,I2C0,UART0,UART1 AND GPIO is powered
	LPC_TIM0->PR   = 0x00000000;
	LPC_TIM0->MCR  = 0x00000003;
	LPC_TIM0->MR0  = 71500;	   				//71500 (2mili sec pulse min) 31500(12 mili sec pulse)
    NVIC_EnableIRQ(TIMER0_IRQn);            //Enable Timer0 Interrupt
	LPC_TIM1->PR   = 0x00000000;
	LPC_TIM1->MCR  = 0x00000003;
	LPC_TIM1->MR0  = 71500;
    NVIC_EnableIRQ(TIMER1_IRQn);            //Enable Timer1 Interrupt
	LPC_TIM2->PR   = 0x00000000;
	LPC_TIM2->MCR  = 0x00000003;
	LPC_TIM2->MR0  = 71500;
    NVIC_EnableIRQ(TIMER2_IRQn);            //Enable Timer2 Interrupt
	LPC_TIM3->PR   = 0x00000000;
	LPC_TIM3->MCR  = 0x00000003;
	LPC_TIM3->MR0  = 40000000;				//time set for 10 sec
    NVIC_EnableIRQ(TIMER3_IRQn);            //Enable Timer0 Interrupt
}
//
void TIMER0_IRQHandler(void)
{    unsigned int isrMask;
    isrMask = LPC_TIM0->IR; 
    LPC_TIM0->IR = isrMask;         /* Clear the Interrupt Bit */
    LPC_TIM0->TCR  = 0x00;  //* Stop timer by reseting the Counter Enable*/
	LPC_GPIO1->FIOSET = 0x03E00000;
	LPC_TIM0->TC   = 0x00;
}
void TIMER1_IRQHandler(void)
{
    unsigned int isrMask;

    isrMask = LPC_TIM1->IR; 
    LPC_TIM1->IR = isrMask;         /* Clear the Interrupt Bit */
    LPC_TIM1->TCR  = 0x00;  //* Stop timer by reseting the Counter Enable*/
	LPC_GPIO1->FIOSET = 0x001C0000;
	LPC_TIM1->TC   = 0x00;
//	LPC_GPIO1->FIOCLR = 0x001C0000;
}
void TIMER2_IRQHandler(void)
{
    unsigned int isrMask;

    isrMask = LPC_TIM2->IR; 
    LPC_TIM2->IR = isrMask;         /* Clear the Interrupt Bit */
    LPC_TIM2->TCR  = 0x00;  //* Stop timer by reseting the Counter Enable*/
	LPC_GPIO1->FIOSET = 0xC0000000;
	LPC_TIM2->TC   = 0x00;
//	LPC_GPIO1->FIOCLR = 0xC0000000;
}
void TIMER3_IRQHandler(void)
{
    unsigned int isrMask;

    isrMask = LPC_TIM3->IR; 
    LPC_TIM3->IR = isrMask; //Clear the Interrupt Bit
    LPC_TIM3->TCR  = 0x00;  //Stop timer by reseting the Counter Enable
	wait_end = 0xff;
	LPC_TIM3->TC   = 0x00;
	LPC_GPIO1->FIOCLR = 0xC3FC0000;
	if(int_flag == 0xff)
	{
		LPC_TIM3->MR0  = 74200;//80000 - LPC_TIM0->MR0 - 2000;
		LPC_TIM0->TCR  = 0x01;	//* Start timer by setting the Counter Enable*/
		LPC_TIM1->TCR  = 0x01;	//* Start timer by setting the Counter Enable*/
		LPC_TIM2->TCR  = 0x01;	//* Start timer by setting the Counter Enable*/
		LPC_TIM3->TCR  = 0x01;	//* Start timer by setting the Counter Enable*/
		int_flag = 0x00;
	}
	else
	{
		LPC_TIM0->TCR  = 0x00;	//* Stop timer by setting the Counter Enable*/
		LPC_TIM1->TCR  = 0x00;	//* Stop timer by setting the Counter Enable*/
		LPC_TIM2->TCR  = 0x00;	//* Stop timer by setting the Counter Enable*/
		LPC_TIM3->TCR  = 0x00;	//* Stop timer by setting the Counter Enable*/
	}
}
//
void count_loop(void)
{
	unsigned char a;
	disp[0] = '0';
	disp[1] = '0';
	disp[2] = '0';
	disp[3]	= '0';
	a = temp;
	while(a!=0)
	{
		a--;
		disp[3]	= disp[3] + 1;
		if(disp[3] > '9')
		{
			disp[3] = '0';
			disp[2]	= disp[2] + 1;
			if(disp[2] > '9')
			{
				disp[2] = '0';
				disp[1]	= disp[1] + 1;
				if(disp[1] > '9')
				{
					disp[1] = '0';
					disp[0]	= disp[0] + 1;
					if(disp[0] > '9')
					{
						disp[0] = '9';
						disp[1] = '9';
						disp[2] = '9';
						disp[3]	= '9';
					}
				}
			}
		}
	}
}
//
void uart_init(void)
{
	LPC_SC->PCONP |= 0x00000008;	//UART0 peripheral enable
	LPC_PINCON->PINSEL0 &= ~0x000000F0;
	LPC_PINCON->PINSEL0 |= 0x00000050;
	LPC_UART0->LCR = 0x00000083;	//enable divisor latch, parity disable, 1 stop bit, 8bit word length
	LPC_UART0->DLM = 0X00; 
	LPC_UART0->DLL = 0x1A;      	//select baud rate 9600 bps
	LPC_UART0->LCR = 0X00000003;
	LPC_UART0->FCR = 0x07;
//	LPC_UART0->IER = 0X03;	   		//select Transmit and receive interrupt
//	NVIC_EnableIRQ(UART0_IRQn);		//Assigning channel
}
//
void UART0_IRQHandler(void)
{
	unsigned long Int_Stat;
	Int_Stat = LPC_UART0->IIR;		//reading the data from interrupt identification register
	Int_Stat = Int_Stat & 0x06;		//masking other than txmit int & rcve data indicator

	if((Int_Stat & 0x02)== 0x02)	//transmit interrupt
	{
	//		tx0_flag = 0xff;
	}
	else if( (Int_Stat & 0x04) == 0x04)  //recve data availble
	{
		buf1[ser_con] =LPC_UART0->RBR;
		ser_con ++;
		if(ser_con == ser_con1)
		{
			ser_con = 0;
			if(dec_asci == 0x00)
			{
				ser_add  = buf1[0];
				ser_data = buf1[1];
			}
			else
			{
				ser_add = ((0x64*(buf1[0]&0x0f))+(0x0A*(buf1[1]&0x0f))+(buf1[2]&0x0f));
				ser_data = ((0x64*(buf1[3]&0x0f))+(0x0A*(buf1[4]&0x0f))+(buf1[5]&0x0f));
			}
			if(ser_add == 0x56)
			{
				sot1v = ser_data;
				sot_value = 0xff;
				sot1d = 0xFF;
			}
			else if(ser_add == 0x5D)
			{
				sot2v = ser_data;
				sot_value = 0xff;
				sot2d = 0xFF;
			}
			else if(ser_add == 0x64)
			{
				sot3v = ser_data;
				sot_value = 0xff;
				sot3d = 0xFF;
			}
		}
	}
}
