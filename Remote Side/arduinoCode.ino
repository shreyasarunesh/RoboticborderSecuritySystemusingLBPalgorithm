#include<LiquidCrystal.h>
int readValue,temp2;
char temp[11];
char rxtemp;
char rxflag;
char rxcount;
char metal,vtg1,vtg2;
float temperature;
#define full 5.00
#define low  0.00
#define mid  2.50
float v1,v2,v3,v4;
int tswitch=13;

void serialEvent()
{
  if(Serial.available())
  {
    rxtemp = (char)Serial.read();
    //if(rxflag==255)
    //{
      //temp[rxcount]=rxtemp;
      //rxcount++;
      //LCD.print(rxtemp);
      
    //}
    /*else if(rxcount==2)
    {
      rxcount=0;
    }*/
  }
  }

void loop() {
  // put your main code here, to run repeatedly:
  readValue=analogRead(A0);
  v1=(5./1023.)*readValue;
  //Serial.println(voltage);

  readValue=analogRead(A1);
  v2=(5./1023.)*readValue;
  //Serial.println(voltage);

  readValue=analogRead(A2);
  v3=(5./1023.)*readValue;
  //Serial.println(voltage);

  readValue=analogRead(A3);
  v4=(5./1023.)*readValue;
  //Serial.println(voltage);
  //Serial.println(" ");
  //delay(2000);
  if(v1==full)
  {
    Serial.println("F");
    delay(500);
    v1=mid;
  }
  else if(v2==full)
  {
    Serial.println("R");
    delay(500);
    v2=mid;
  }
  else if(v1==low)
  {
    Serial.println("B");
    delay(500);
    v1=mid;
  }
  else if(v2==low)
  {
    Serial.println("L");
    delay(500);
    v2=mid;
  }
  else
  {
    Serial.println("N");
    
  }
  if(v3==full)
  {
    Serial.println("f");
    delay(500);
    v2=mid;
  }
  else if(v4==full)
  {
    Serial.println("H");
    delay(500);
    v4=mid;
  }
  else if(v3==low)
  {
    Serial.println("b");
    delay(500);
    v3=mid;
  }
  else if(v4==low)
  {
    Serial.println("r");
    delay(500);
    v2=mid;
  }
  else
  {
    Serial.println("n");
  }
  if(rxtemp=='T')
  {
    rxflag = '1';
   // Serial.println(rxtemp);
    LCD.setCursor(0,1);
    LCD.print("temperature=");
    rxtemp=0;
  }
    if(rxtemp=='M')
  {
    Serial.println(rxtemp);
    LCD.setCursor(0,0);
    LCD.print("metal");
    rxtemp=0;
  }
       
   }
}
