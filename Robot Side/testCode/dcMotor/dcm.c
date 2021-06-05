#include<lpc17xx.h>
unsigned int temp3,i;
int main (void)
{ 
LPC_GPIO1->FIODIR = 0x0F000000;
LPC_GPIO1->FIOSET = 0x0F000000;
while(1)
{
 temp3 = LPC_GPIO1->FIOPIN;
 temp3 &=0x00F00000;
for(i=0;i<20000;i++);
while(temp3 == 0x00F00000)
{
 temp3 = LPC_GPIO1->FIOPIN;
 temp3 &=0x00F00000;
 LPC_GPIO1->FIOSET = 0x0F000000;
}
 if(temp3 == 0x00700000)
 {
 // LPC_GPIO1->FIOSET = 0x0F000000;
  LPC_GPIO1->FIOCLR = 0x05000000;
 }
 else if(temp3 == 0x00B00000)
 {
 // LPC_GPIO1->FIOSET = 0x0F000000;
  LPC_GPIO1->FIOCLR = 0x0A000000;
 }
 else if(temp3==0x00D00000)
 {
 // LPC_GPIO1->FIOSET = 0x0F000000;
  LPC_GPIO1->FIOCLR = 0x01000000;
 }
   else if(temp3==0x00E00000)
 {
 // LPC_GPIO1->FIOSET = 0x0F000000;
  LPC_GPIO1->FIOCLR = 0x04000000;
 }
 }
}

