#include<LiquidCrystal.h>

#define full 5.00
#define low  0.00
#define mid  2.50
float v1,v2
 
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


