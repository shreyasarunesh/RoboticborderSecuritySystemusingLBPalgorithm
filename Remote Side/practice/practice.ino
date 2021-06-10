float a[8]={000000};
struct Data_Package {
  byte j1PotX;
  byte j1PotY;
  byte j2PotX;
   byte j2PotY;
};
Data_Package data;
void setup() {
  // put your setup code here, to run once:
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
Serial.begin(9600);
data.j1PotY = 127;
  data.j2PotX = 127;
  data.j2PotY = 127;
  data.j2PotX = 127;
}

void loop() {
  // put your main code here, to run repeatedly:
  data.j1PotX = map(analogRead(A1), 0, 1023, 0, 255); // Convert the analog read value from 0 to 1023 into a BYTE value from 0 to 255
  data.j1PotY = map(analogRead(A0), 0, 1023, 0, 255);
  data.j2PotX = map(analogRead(A2), 0, 1023, 0, 255);
  data.j2PotY = map(analogRead(A3), 0, 1023, 0, 255);
Serial.println(data, sizeof(&Data_Package));
delay(1000);
}
