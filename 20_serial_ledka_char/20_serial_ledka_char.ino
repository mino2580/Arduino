char receivedChar;
 int hodnota;

void setup() {
 Serial.begin(9600);
 pinMode(10, OUTPUT);
  
}

void loop() {
 recvOneChar();
 
}

void recvOneChar() {
  
 if (Serial.available() > 0) 
 {
   receivedChar =Serial.read();
   
  if  (receivedChar == '1') digitalWrite(10, HIGH);       
  if(receivedChar == '0') digitalWrite(10, LOW); 
 }
 
}
