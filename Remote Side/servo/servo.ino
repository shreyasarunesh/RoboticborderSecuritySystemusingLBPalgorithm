
#include<Servo.h>             //Servo
int pos=0;
int servoPin=9;
int servodelay=25;
Servo myptr;
void setup() 
{ 
  Serial.begin(9600);
  myptr.attach(servoPin);
} 
  
void loop() 
{ 
  Serial.println("point it bro...");
  while(Serial.available()==0){
  }
  pos=Serial.parseInt();
  myptr.write(90);
 
}
