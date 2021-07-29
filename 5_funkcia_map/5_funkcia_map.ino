//uprava jasu LED pomoci potenciometru

 int analog, pwm;

 void setup() {
 Serial.begin(9600);
 }

 void loop() {
 analog = analogRead(A0);
 pwm = map(analog, 0, 1023, 0, 255);
 Serial.print("Analog: ");
 Serial.print(analog);
 Serial.print(" PWM: ");
 Serial.println(pwm);

 analogWrite(11, pwm);
 }
