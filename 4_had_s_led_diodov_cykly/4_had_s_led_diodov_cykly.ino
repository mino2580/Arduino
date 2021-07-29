byte led[] = {2,3,4,5,6}; //piny s LED diodami
 byte pocet = 5; //pocet diod
 int rychlost = 1000; //jakou prodlevu maji jednotliva bliknuti

 void setup() {
 for(int i = 0; i < pocet; i++) {
 pinMode(led[i], OUTPUT); //nastaveni pinu
                            }
 }

 void loop() {
 for(int i = 0; i < pocet; i++) {
 digitalWrite(led[i], HIGH);
 delay(rychlost/2);
 digitalWrite(led[i], LOW);
 delay(rychlost/2);   //hodnota 1000 =1 sekunda
 }
 }
