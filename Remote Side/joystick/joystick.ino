int readValue,v1,v2,v3,v4;
float voltage;
void setup() {
  // put your setup code here, to run once:
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  readValue=analogRead(A0);
  v1=(5./1023.)*readValue;
  Serial.println(v1);

  readValue=analogRead(A1);
  v2=(5./1023.)*readValue;
  Serial.println(v2);
  
  readValue=analogRead(A2);
  v3=(5./1023.)*readValue;
  Serial.println(v3);

  readValue=analogRead(A3);
  v4=(5./1023.)*readValue;
  Serial.println(v4);
  
if(v1==2.5&&v2==2.5)
 {
  Serial.println("n");
 }
 else
 {
  if(v1=5)
  {
    Serial.println("F");
  }
  if(v2==5)
  {
    Serial.println("R");
  }
  if(v1==0)
  {
    Serial.println("B");
  }
   if(v2==0)
  {
    Serial.println("L");
  }
  
if(v3==2.5&&v4==2.5)
{
  Serial.println("n");
 }
 else
 {
  if(v3=5)
  {
    Serial.println("h");
  }
  if(v4==5)
  {
    Serial.println("r");
  }
  if(v3==0)
  {
    Serial.println("f");
  }
   if(v4==0)
  {
    Serial.println("b");
  }
 }

}}
