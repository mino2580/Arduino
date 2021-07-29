String receivedChar;
 

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
   receivedChar =Serial.readString();
  if  (receivedChar == "11") digitalWrite(10, HIGH);       
  if(receivedChar == "0") digitalWrite(10, LOW); 
 }
 
}

 
