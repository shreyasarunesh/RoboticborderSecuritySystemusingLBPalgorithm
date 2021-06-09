#include<LiquidCrystal.h>
LiquidCrystal LCD(6,7,5,3,4,2);
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
void setup()
{
  // put your setup code here, to run once:
  LCD.begin(20,4);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(13,INPUT);
  digitalWrite(tswitch,HIGH);
  Serial.begin(9600);
  temp[0] = '0';
  temp[1] = '1';
  temp[2] = '2';
  temp[3] = '3';
  temp[4] = '4';
  temp[5] = '5';
  temp[6] = '6';
  temp[7] = '7';
  temp[8] = '8';
  temp[9] = '9';
}
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
int  val = digitalRead(tswitch);
  
  if(val==low)
  {
    Serial.println('T');
    delay(500);
  }
  if(rxflag=='1')
  {
    //Serial.println('R');
      if((rxcount<'7')&(rxtemp != 0))
      {
          //Serial.println('D');
          if(rxtemp=='0')
          {
            LCD.print(temp[0]);
          }
          else if(rxtemp=='1')
          {
            LCD.print(temp[1]);
          }
          else if(rxtemp=='2')
          {
            LCD.print(temp[2]);
          }
          else if(rxtemp=='3')
          {
            LCD.print(temp[3]);
          }
          else if(rxtemp=='4')
          {
            LCD.print(temp[4]);
          }
          else if(rxtemp=='5')
          {
            LCD.print(temp[5]);
          }
           else if(rxtemp=='6')
          {
            LCD.print(temp[6]);
          }
          else if(rxtemp=='7')
          {
            LCD.print(temp[7]);
          }
           else  if(rxtemp=='8')
          {
            LCD.print(temp[8]);
          }
          else if(rxtemp=='9')
          {
            LCD.print(temp[9]);
          }
          else
          {
            LCD.print('.');
          }
          rxtemp = 0;
      }     
   }
}
