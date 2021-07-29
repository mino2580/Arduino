byte led[] = {0,1,2,3,4}; //pole s piny pripojenych LED diod
byte pot = A0;
 int val;

 void setup() {
 pinMode(led[0], OUTPUT);
 pinMode(led[1], OUTPUT);
 pinMode(led[2], OUTPUT);
 pinMode(led[3], OUTPUT);
 pinMode(led[4], OUTPUT);
 }
 void loop(){
 val = analogRead(pot);

 if(val > 800){
 digitalWrite(led[0],HIGH);
 }
 else if(val > 600){
 digitalWrite(led[1],HIGH);
 }
 else if(val > 400){
 digitalWrite(led[2],HIGH);
 }
 else if(val > 200){
 digitalWrite(led[3],HIGH);
 }
 else{
 digitalWrite(led[4],HIGH);
 }

 
delay(250);

 digitalWrite(led[0],LOW);
 digitalWrite(led[1],LOW);
 digitalWrite(led[2],LOW);
 digitalWrite(led[3],LOW);
 digitalWrite(led[4],LOW);

}
