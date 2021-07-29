boolean x = true;

 void setup() {
 Serial.begin(9600);
 while(x){
 Serial.println("OPAKUJI");
 x = false; //cyklus se tedy provede jednou
         }
   }

 void loop() {
 }
