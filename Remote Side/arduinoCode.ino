
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

  }

void loop() {
  // put your main code here, to run repeatedly:
  readValue=analogRead(A0);
  v1=(5./1023.)*readValue;

  readValue=analogRead(A1);
  v2=(5./1023.)*readValue;


  readValue=analogRead(A2);
  v3=(5./1023.)*readValue;


  readValue=analogRead(A3);
  v4=(5./1023.)*readValue;

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
  
    
  }

      }     
   }
}
