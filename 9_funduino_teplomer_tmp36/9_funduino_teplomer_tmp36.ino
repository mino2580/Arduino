
int TMP36 = A0;      // Senzor musí být připojen k analogovému kolíku A0. Od této chvíle budeme volat hodnotu senzoru int  "TMP36"
int sensorwert;
int temperatur = 0;  // Hodnota teploty bude později uložena pod proměnnou „teplota“.
int t=2000;          // Hodnota pro „t“ určuje časové intervaly mezi jednotlivými měřeními v kódu.


void setup() {
Serial.begin(9600);
                  // Sériová komunikace začíná v nastavení, takže teplota je přenášena na sériový monitor.
                  //Deska odešle naměřené hodnoty do počítače přes sériovou komunikaci.
                  //V softwaru Arduino můžete spustit „Serial Monitor“ pod „Tools“ a zobrazit naměřené hodnoty.
}

void loop() {
sensorwert=analogRead(TMP36);                    // Odečtěte hodnotu senzoru.

temperatur= map(sensorwert, 0, 410, -50, 150);  // Převod hodnoty senzoru pomocí příkazu „map“.

delay(t);                        // Po každém měření je krátká pauza s dobou trvání „t“ v milisekundách.

Serial.print(temperatur);       // Nyní je hodnota „teploty“ odeslána do PC přes sériovou komunikaci. 
                                //Teplota lze odečíst otevřením sériového monitoru v softwaru Arduino.
                        
Serial.println(" Grad Celsius"); 
                               // Nyní je hodnota „teploty“ odeslána do PC přes sériovou komunikaci.
                             //Teplota lze odečíst otevřením sériového monitoru v softwaru Arduino.
Serial.print("analogova hodnotA ");
Serial.println(sensorwert);  
}
