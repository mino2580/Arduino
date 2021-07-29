                                   
#define topeni 11                  //nastavenie pinu pre pwm spinanie tranzistorov pre hod.prudu 0-255          
#include <OneWire.h>               // pripojenie knižnice
#include <DallasTemperature.h>
/****************************************************************************************************************/
String receivedChar;               //premenna pre serial komunikaciu
float  hodnota;
float  nastavena_teplota;
float data;                         //premenna pre od4itanu hodnotu z teplomera
float namerana_teplota=0;           //aktualne namerana teplota
float hodnota_prudu;
float pwm_f;
byte  pwm_b;
float  pwm;
float u_max=4.8;
float u_str=0;
float kp_max=0;
float kp;
float u;
float konstanta;
float konstanta2;
float k3;
const int pinCidlaDS = 12;               // nastavení čísla vstupního pinu
OneWire oneWireDS(pinCidlaDS);           // vytvorenie inštancie oneWireDS z knihovny OneWire
DallasTemperature senzoryDS(&oneWireDS); // vytvorenie inštancie senzoryDS z knihovny DallasTemperature
float sygma=0;
/**************************************************************************************************************/

void setup()
{
pinMode(topeni,OUTPUT);            //pin 11 nastav na vystup pre spinanie teplotnych telies
analogWrite(topeni,0);             //nastav pwm teplotnych telies na 0 hodnotu
Serial.begin(9600);                //prenosova rychlost komunikacie
senzoryDS.begin();                 // zapnutie komunikacie knihovny s teplotným čidlom
}

/************************************************************************************************************/

float zmeraj_teplotu()             //funkcia pre zmeranie teploty //teplomer Ds18b20
{
 //  pomocou zmeny čísla v zátvorke (0) - poradie podľa unikátny adresy
 // na jeden pin môžeme postupne načítať všetky teploty
 // výpis teploty na sériovú linku, pri pripojení viac snímačovčidel              
 // načítanie informácií zo všetkých pripojených snímačov na danom pinu                                                 
 //Serial.print(senzoryDS.getTempCByIndex(0));    
 //Serial.println(" stupnu Celsia");   
          
  senzoryDS.requestTemperatures();   
   data= senzoryDS.getTempCByIndex(0);             
  return (data); 
 }

/***********************************************************************************************************/
float recvOneString() {             //seriova komunikacia matalb prijimanie dat
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
nastavena_teplota= recvOneString();         //nastav hodnotu pozadovanej  teploty 
namerana_teplota=zmeraj_teplotu();          //zmeraj teplotu

//nastavenie sygma pre rozne teploty
  if (nastavena_teplota<30) {sygma=0.4;konstanta=0.6;konstanta2=0.2;}
else if (nastavena_teplota>=30&&nastavena_teplota<35) {sygma=0.3;konstanta=0.8;konstanta2=0.3;}
else if (nastavena_teplota>=35&&nastavena_teplota<45) {sygma=0.3;konstanta=1.1;konstanta2=0.35;}
else if (nastavena_teplota>=45&&nastavena_teplota<55) {sygma=0.2;konstanta=1;konstanta2=0.6;}
else if (nastavena_teplota>=55&&nastavena_teplota<65) {sygma=0.2;konstanta=1;konstanta2=0.6;}
else if (nastavena_teplota>=65&&nastavena_teplota<=70) {sygma=0.1;konstanta=1.5;konstanta2=1;k3=0;}
else nastavena_teplota=0;

//vypočet hodnoty prudu,pwm a konstat
hodnota_prudu=( (1.32/45)*(namerana_teplota-25) )+0.18;       //aktualna hodnota prudu
kp_max=u_max/( (1.32/45)*(nastavena_teplota-25) +0.18 );       //vypocet kp max penalizace
kp=1+ (1- ((nastavena_teplota-namerana_teplota)/nastavena_teplota ) *(1/sygma) )*(kp_max-1);
u=u_max/kp;  

//vypočet hodnoty pwm 
pwm_f=( (70/1.32)*(u-0.18) )+10;    //datovy typ float
pwm_b=pwm_f;                      // datovy typ bute-cele čislo ,pretypovanie
pwm=pwm_f-pwm_b;

                                 //zaokruhlenie byte 
if (pwm>=0.5) {
  pwm_b=pwm_b+1;  
  } 

//zapni -vypni telesa,pracuj z nastavenou hodnotou pwm pomocou penalizačnej konštanty
if ((namerana_teplota<nastavena_teplota-konstanta)) analogWrite(topeni,pwm_b);
else if ((namerana_teplota>=nastavena_teplota-konstanta&&namerana_teplota<nastavena_teplota-konstanta2)) analogWrite(topeni,0);            
else if ((namerana_teplota>=nastavena_teplota-konstanta2&&namerana_teplota<nastavena_teplota)) analogWrite(topeni,pwm_b);   
else if ((nastavena_teplota==70&&namerana_teplota<=nastavena_teplota)) analogWrite(topeni,pwm_b);         
else   analogWrite(topeni, 0);                                                                                                       

//pošli data do pc
Serial.println(namerana_teplota);   // posielanie dat do guide 
delay(5000);                        //čakaj 5s
 
}                                   //end a znova na štart
