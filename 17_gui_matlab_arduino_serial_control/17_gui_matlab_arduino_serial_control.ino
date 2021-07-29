String value;
int integerFromPC;
void setup()
{
Serial.begin(9600);
pinMode(10, OUTPUT);
}

void loop()
{
  if(Serial.available()>0)
  {
    //value= Serial.readString();
 integerFromPC = atoi(Serial.readString());
    if  (value == 1)           
    { 
    digitalWrite(10, HIGH);
    }
    if(value == 0)         
    { 
    digitalWrite(10, LOW);
    }
  }
}
