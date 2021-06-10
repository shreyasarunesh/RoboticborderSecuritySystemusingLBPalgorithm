 #include<LiquidCrystal.h>
 LiquidCrystal LCD(10,9,5,4,3,2);
 int i,j,k,l,m,n,o,p;
 
 void setup() {
  // put your setup code here, to run once:
  LCD.begin(20,4);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(i=1;i<=20;i=i+1) {
  LCD.setCursor(i,0);
  LCD.print(" hello");
  LCD.setCursor(i,1);
  LCD.print(" hello");
  LCD.setCursor(i,2);
  LCD.print(" hello");
  LCD.setCursor(i,3);
  LCD.print(" hello");
  delay(1000);
  }
}
