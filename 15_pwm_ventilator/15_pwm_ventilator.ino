#define topeni 11
#define fanT1 10


void setup() {
  // put your setup code here, to run once:
  pinMode(topeni,OUTPUT);
   pinMode(fanT1,OUTPUT);

  Serial.begin(9600);
  //safety speed reset of the motor
  analogWrite(topeni,0);
  analogWrite(fanT1,0);

}

void loop() {
  // put your main code here, to run repeatedly:
 
 
  analogWrite(topeni, 0); //here's how to generate PWM signal from Digital arduino pin
  analogWrite(fanT1, 0);
}
