#include "DHT.h"

// číslo pinu Arduina, kam je připojený DATA pin senzoru DHT
#define DHTPIN 2
 
// pro případ, že by byl senzor typu DHT-11 
#define DHTTYPE DHT11
// do proměné dht uložíme údaje o již nadefinovaném senzoru 
DHT dht(DHTPIN, DHTTYPE); 

// vytvoříme proměnou pro vlhkost (humidity)
float hum;
// vytvoříme proměnou pro teplotu (temperature)
float temp;  
                                
void setup()
{
  // zapneme sériovou linku a určíme rychlost 9600 baudů
  Serial.begin(9600);   
  // aktivujeme komunikaci senzoru DHT                      
  dht.begin();                                
}

void loop()
{
  // načteme informaci (vlhkost) z čidla a uložíme jí do proměné hum  
  hum = dht.readHumidity();  
  // načteme informaci (teplota) z čidla a uložíme jí do proměné temp
  temp = dht.readTemperature();             

  // vypíšeme informace po sériové lince
  Serial.print("Vlhkost: ");                
  Serial.print(hum);
  Serial.print(" %, Teplota: ");
  Serial.print(temp);
  Serial.println(" Celsius");

  // počkáme 2s před opakováním měření
  delay(2000);                              
}
