#include <OneWire.h>
#include <DallasTemperature.h>                                 
#define pin 12                         // pin, kde bude senzor zapojený
float data;
String receivedChar;
int hodnota;
OneWire oneWire(pin);                  // nastavení komunikace senzoru přes pin              
DallasTemperature sensors(&oneWire);   // převedeme onewire do Dallasu         

 
void setup(void)
{
   pinMode(10, OUTPUT);
  Serial.begin(9600);                 // nastavení rychlosti sériové komunikace                     
  sensors.begin();                    // zapnutí senzoru                           
}


void recvOneChar() 
{
 if (Serial.available() > 0) 
 {
   receivedChar =Serial.readString();
   hodnota=receivedChar.toInt();
  if  (hodnota >= 1) digitalWrite(10, HIGH);       
  if(hodnota == 0) digitalWrite(10, LOW); 
 }
}
 
void loop(void)
{
  recvOneChar();                     //nacitanie komunikacie a dat
  sensors.requestTemperatures();      // požádáme senzor o hodnotu teploty          
  data=sensors.getTempCByIndex(0);             //  nacitaj teplotu
  Serial.print(data); Serial.print(' ');       // posli data
  delay(1000);
}
