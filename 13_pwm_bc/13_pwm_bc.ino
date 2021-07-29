int TMP36 = A0;            //Der Sensor soll am analogen Pin A0 angeschlossen werden. Wir nennen den Pin ab jetzt "TMP36"
int namerana_teplota=0;
int error=0;
int minimum_T=0;
////////////////////////////
float supply_voltage = 5;
/////////////////////////////
int t=2000;                 //Der Wert für „t“ gibt im Code die zeitlichen Abstände zwischen den einzelnen Messungen vor.
int konst=0;
////////////////////////////

int nastavena_teplota=0;

/*********************************************************************************************/

void setup()
{
pinMode(2, OUTPUT);
Serial.begin(9600); //Im Setup beginnt die serielle Kommunikation, damit die Temperatur an den serial monitor übertragen wird. Über die serielle Kommunikation sendet das Board die Messwerte an den Computer. In der Arduino-Software kann man unter „Werkzeuge“ den „Seriellen Monitor“ starten um die Messwerte zu sehen.
}

/*********************************************************************************************/

int zmeraj_teplotu()
{
 //getting the voltage reading from the temperature sensor
 int reading = analogRead(TMP36);  
 
 // converting that reading to voltage,
 float voltage = reading * supply_voltage / 1024;
 
 // print out the voltage
 //Serial.print(voltage); Serial.println(" volts");
 
 // now print out the temperature
 float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree with 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)
 Serial.print(temperatureC); Serial.println(" degrees C");
 delay(t);  
 return temperatureC;
 }

/**********************************************************************************************/

void loop()
{
  namerana_teplota=zmeraj_teplotu();
error=nastavena_teplota-namerana_teplota;
minimum_T=nastavena_teplota-konst;

if (namerana_teplota<minimum_T) digitalWrite(2, HIGH);
if (namerana_teplota>minimum_T) digitalWrite(2, LOW);
if (namerana_teplota==minimum_T) Serial.println(" Teplota je nastavena");

}
