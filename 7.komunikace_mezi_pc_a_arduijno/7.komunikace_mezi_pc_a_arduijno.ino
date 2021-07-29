char prijato;
 void setup() {
 Serial.begin(9600);
 }

 void loop() 
 {
 if (Serial.available() > 0) {
 prijato = Serial.read();
 Serial.print("Prijato: ");
 Serial.println(prijato);    }

 }
