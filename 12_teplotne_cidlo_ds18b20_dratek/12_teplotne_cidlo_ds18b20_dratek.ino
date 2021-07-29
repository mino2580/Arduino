// Teplotní čidlo DS18B20

// připojení knihoven
#include <OneWire.h>
#include <DallasTemperature.h>

// nastavení čísla vstupního pinu
const int pinCidlaDS = A0;
// vytvoření instance oneWireDS z knihovny OneWire
OneWire oneWireDS(pinCidlaDS);
// vytvoření instance senzoryDS z knihovny DallasTemperature
DallasTemperature senzoryDS(&oneWireDS);

void setup(void) {
  // komunikace přes sériovou linku rychlostí 9600 baud
  Serial.begin(9600);
  // zapnutí komunikace knihovny s teplotním čidlem
  senzoryDS.begin();
}

void loop(void) {
  // načtení informací ze všech připojených čidel na daném pinu
  senzoryDS.requestTemperatures();
  // výpis teploty na sériovou linku, při připojení více čidel
  // na jeden pin můžeme postupně načíst všechny teploty
  // pomocí změny čísla v závorce (0) - pořadí dle unikátní adresy čidel
  Serial.print("Teplota cidla DS18B20: ");
  Serial.print(senzoryDS.getTempCByIndex(0));
  Serial.println(" stupnu Celsia");
  // pauza pro přehlednější výpis
  delay(1000);
}
