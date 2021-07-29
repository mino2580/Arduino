

#include <OneWire.h>
#include <DallasTemperature.h>

// pin, kde bude senzor zapojený
#define pin 12
float data;
// nastavení komunikace senzoru přes pin
OneWire oneWire(pin);     
// převedeme onewire do Dallasu                     
DallasTemperature sensors(&oneWire);           
 
void setup(void)
{
  // nastavení rychlosti sériové komunikace
  Serial.begin(9600);
  // zapnutí senzoru                          
  sensors.begin();                             
}
 
void loop(void)
{
  // požádáme senzor o hodnotu teploty
  sensors.requestTemperatures();               
 // Serial.print("Teplota je: ");
  // tento řádek je vysvětlený v článku
  data=sensors.getTempCByIndex(0);
  Serial.println(data);  // Serial.print(' ');     
  //Serial.println(" stupnu Celsia");
 // delay(5000);
}
