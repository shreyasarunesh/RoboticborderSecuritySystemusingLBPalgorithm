 #include<LiquidCrystal.h>
#include<SPI.h>
#include<nRF24L01.h>
#include <RF24.h>
LiquidCrystal LCD(6,7,5,3,4,2);
RF24 radio (9,10); //CNS,CE Pins
const byte addresses[][6] = {"00001","00002"};
struct Data_Package {
  byte j1PotX;
  byte j1PotY;
  byte j2PotX;
  byte j2PotY;
};

Data_Package data; //Create a variable with the above structure

void setup() {
    pinMode(A0,INPUT);
    pinMode(A1,INPUT);
    pinMode(A2,INPUT);
    pinMode(A3,INPUT);
    
    LCD.begin(20,4);
    Serial.begin(9600);
    radio.begin();
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1,addresses[1]);
    radio.setPALevel(RF24_PA_MIN);  
}

void loop() {
  delay(5);
  radio.startListening();
  if(radio.available()){
    while(radio.available()){
      int data=0;
      radio.read(&data,sizeof(data));
      LCD.setCursor(0,0);
      LCD.print(data);
    }
    delay(5);
    radio.stopListening();
    data.j1PotX = map(analogRead(A1), 0, 1023, 0, 255); // Convert the analog read value from 0 to 1023 into a BYTE value from 0 to 255
    data.j1PotY = map(analogRead(A0), 0, 1023, 0, 255);
    data.j2PotX = map(analogRead(A2), 0, 1023, 0, 255);
    data.j2PotY = map(analogRead(A3), 0, 1023, 0, 255);
    radio.write(&data, sizeof(Data_Package));
    Serial.println(data.j1PotX);
    
  }

}
