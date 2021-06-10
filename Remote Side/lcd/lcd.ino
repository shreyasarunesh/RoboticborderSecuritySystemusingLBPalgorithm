 #include<LiquidCrystal.h>
 LiquidCrystal LCD(6,7,5,3,4,2);
 int readValue;
float voltage;
 void setup() {
  // put your setup code here, to run once:
  LCD.begin(20,4);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
   
 readValue=analogRead(A0);
  voltage=(5./1023.)*readValue;
 LCD.setCursor(0,0);
  LCD.print(voltage);
  readValue=analogRead(A1);
  voltage=(5./1023.)*readValue;
 LCD.setCursor(0,1);
  LCD.print(voltage);
  readValue=analogRead(A2);
  voltage=(5./1023.)*readValue;
 LCD.setCursor(0,2);
  LCD.print(voltage);
  readValue=analogRead(A3);
  voltage=(5./1023.)*readValue;
 LCD.setCursor(0,3);
  LCD.print(voltage);
  
  delay(250); 
}
