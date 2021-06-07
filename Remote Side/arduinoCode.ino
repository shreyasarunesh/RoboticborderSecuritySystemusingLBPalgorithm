#include<LiquidCrystal.h>

#define full 5.00
#define low  0.00
#define mid  2.50
float v1,v2,v3,v4;
int tswitch=13;
void setup()
{
  // put your setup code here, to run once:
  LCD.begin(20,4);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
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
  
}
