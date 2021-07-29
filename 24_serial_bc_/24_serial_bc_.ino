                                   // Teplotní čidlo DS18B20
#define topeni 11                  //nastavenie pinu pre pwm spinanie tranzistorov pre hod.prudu 0-255          
#include <OneWire.h>               // připojení knihoven
#include <DallasTemperature.h>

/****************************************************************************************************************/

String receivedChar;                   //premenna pre serial komunikaciu
 float hodnota;


float namerana_teplota=0;                    //aktualne namerana teplota
float hodnota_prudu;
float pwm_f;
byte  pwm_b;
float  pwm;

float u_max=1.32;
float u_str=0;
float kp_max=0;
float kp;
float u;
float konstanta;
float konstanta2;
const int pinCidlaDS = 12;                   // nastavení čísla vstupního pinu
OneWire oneWireDS(pinCidlaDS);               // vytvoření instance oneWireDS z knihovny OneWire
DallasTemperature senzoryDS(&oneWireDS);     // vytvoření instance senzoryDS z knihovny DallasTemperature

////////////////////////////

//float nastavena_teplota=0;                  //teplota na ktoru sa ma nastavit komora
float sygma=0;
/**************************************************************************************************************/

void setup()
{
   pinMode(10, OUTPUT);
pinMode(topeni,OUTPUT);            //pin 11 nastav na vystup pre spinanie teplotnych telies
analogWrite(topeni,0);             //nastav pwm teplotnych telies na 0 hodnotu
Serial.begin(9600);                //prenosova rychlost komunikacie
senzoryDS.begin();                 // zapnutí komunikace knihovny s teplotním čidlem
}

/************************************************************************************************************/

float zmeraj_teplotu()                     //funkcia pre zmeranie teploty //teplomer tmp36
{
 
  senzoryDS.requestTemperatures();         // načtení informací ze všech připojených čidel na daném pinu
                                           // výpis teploty na sériovou linku, při připojení více čidel
                                           // na jeden pin můžeme postupně načíst všechny teploty
                                           // pomocí změny čísla v závorce (0) - pořadí dle unikátní adresy čidel
 
 //Serial.print(senzoryDS.getTempCByIndex(0));
 //Serial.println(" stupnu Celsia");
  delay(1000);                             // pauza pro přehlednější výpis                       
 return (senzoryDS.getTempCByIndex(0));
 
 }

/***********************************************************************************************************/
float recvOneString() {                           //seriova komunikacia matalb prijimanie dat
  
 if (Serial.available() > 0) 
 {
   receivedChar =Serial.readString();
   hodnota=receivedChar.toFloat();
 }
 return (hodnota);
}
/**************************************************************************************************/

void loop()
{
float nastavena_teplota= recvOneString();                                         //nastav hodnotu pozadovanej  teploty 
analogWrite(10, nastavena_teplota); 
namerana_teplota=zmeraj_teplotu();                           //zmeraj teplotu

if (nastavena_teplota>=25&&nastavena_teplota<=35) {sygma=0.2;konstanta=1;konstanta2=0.2;}
if (nastavena_teplota>36&&nastavena_teplota<=50) {sygma=0.2;konstanta=1;konstanta2=0.25;}
if (nastavena_teplota>50&&nastavena_teplota<=65) {sygma=0.1;konstanta=1;konstanta2=0.3;}
if (nastavena_teplota>65&&nastavena_teplota<=70) {sygma=0.025;konstanta=0.3;konstanta2=0.4;}

hodnota_prudu=( (1.32/45)*(namerana_teplota-25) )+0.18;       //aktualna hodnota prudu
//Serial.print("prud pri teplote je ");Serial.print(hodnota_prudu);Serial.println();
//Serial.print("sygma je ");Serial.print(sygma);Serial.println();
//Serial.print("konstanta je ");Serial.print(konstanta);Serial.println();

kp_max=u_max/( (1.32/45)*(nastavena_teplota-25) +0.18 );       //vzpocet kp max penalizace
kp=1+ (1- ((nastavena_teplota-namerana_teplota)/nastavena_teplota ) *(1/sygma) )*(kp_max-1);
u=u_max/kp;  

pwm_f=( (70/1.32)*(u-0.18) )+10;        // Serial.print("pwm float ");Serial.print(pwm_f);Serial.println();
pwm_b=pwm_f;                             // Serial.print("pwm byte ");Serial.print(pwm_b);Serial.println();
pwm=pwm_f-pwm_b;

if (pwm>0.5) {
  pwm_b=pwm_b+1;  
} 

//Serial.print("pwm_b++ byte ");Serial.print(pwm_b);Serial.println();
Serial.print("Teplota cidla DS18B20: ");Serial.print(namerana_teplota);Serial.println(" stupnu Celsia");Serial.println();

if ((namerana_teplota<nastavena_teplota-konstanta)) analogWrite(topeni,pwm_b);                                                //zapnutie teplotnych telies  
                                                                                                                    //if (namerana_teplota>=nastavena_teplota-konstanta&&namerana_teplota<nastavena_teplota-konstanta2) analogWrite(topeni,0);             //vypnutie teplotnych telies
if (namerana_teplota>=nastavena_teplota-konstanta2&&namerana_teplota<=nastavena_teplota) analogWrite(topeni, pwm_b);         //zapnutie teplotnych telies
                                                                                                                    //if (namerana_teplota>=nastavena_teplota) analogWrite(topeni, 0);
if (namerana_teplota==nastavena_teplota) Serial.println(" Teplota je nastavena");                                    //zobrazenie  nastavenej teploty
   
 if (nastavena_teplota==0) analogWrite(topeni,0);    //vzpnutie regulatora
}
