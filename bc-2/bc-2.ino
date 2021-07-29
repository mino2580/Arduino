/////////////////////////////////////// Teplotní čidlo DS18B20/////////////////////////////////////////////////
                                 
#include <OneWire.h>                // připojení knihoven
#include <DallasTemperature.h>
/**************************************************************************************************/                                 

const int pinCidlaDS = A0;                 // nastavení čísla vstupního pinu                                
OneWire oneWireDS(pinCidlaDS);            // vytvoření instance oneWireDS z knihovny OneWire                                 
DallasTemperature senzoryDS(&oneWireDS);  // vytvoření instance senzoryDS z knihovny DallasTemperature
int temperatureC;
int DS18B20 = A0;
int namerana_teplota=0;
int error=0;
int minimum_T=0;
float supply_voltage = 5;

int t=5000; 
int nastavena_teplota=0;
int konst=2;

/****************************************************************************************************/

void setup()
{
pinMode(2, OUTPUT);               //nastaveni pinu 2 na vzstup pro sepnuti trenzistoru bc
                                         
 Serial.begin(9600);              // komunikace přes sériovou linku rychlostí 9600 baud
                                         
 senzoryDS.begin();             // zapnutí komunikace knihovny s teplotním čidlem
}

///////////////////////

int zmeraj_teplotu()
{
 
 return temperatureC;
 }
/*************************************/

void loop()
{
  namerana_teplota=zmeraj_teplotu();
error=nastavena_teplota-namerana_teplota;
minimum_T=nastavena_teplota-konst;


if (namerana_teplota<minimum_T) 
digitalWrite(2, HIGH);
if (namerana_teplota>minimum_T) digitalWrite(2, LOW);
if (namerana_teplota==minimum_T) Serial.println(" Teplota je nastavena");

 

}
