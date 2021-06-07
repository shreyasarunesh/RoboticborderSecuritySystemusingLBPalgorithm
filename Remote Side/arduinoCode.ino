#include<LiquidCrystal.h>

#define full 5.00
#define low  0.00
#define mid  2.50
float v1,v2,v3,v4;
int tswitch=13;
void setup() {
  // put your setup code here, to run once:
  LCD.begin(20,4);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  Serial.begin(9600);
 
}
void serialEvent()
 
 {
  Serial.println("n");
 }
 else
 {
  if(v1>=3.5)
  {
    Serial.println("F");
  }
  if(v2>=3.5)
  {
    Serial.println("R");
  }
  else if(v1<=1.5)
  {
    Serial.println("B");
  }
  else if(v2<=1.5)
  {
    Serial.println("L");
  }
 
}
