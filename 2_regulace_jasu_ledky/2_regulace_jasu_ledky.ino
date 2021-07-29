byte led=6;  //pin s led diodou
byte pot=A0;  //pin s pripojenym potenciometrem
int val;  //promenna pripravena k uchovani hodnot

void setup() {
  //nic se nepiše

}

void loop() {
  val=analogRead(pot)/4;
  //cteni hodnoty na A0 a uprava rozsahu
  analogWrite(led,val);
  //generovani pwm

}
