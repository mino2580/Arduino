String receivedChar;
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
   receivedChar =Serial.readString();
   hodnota=receivedChar.toInt();
   
  if  (hodnota >= 1) digitalWrite(10, HIGH);       
  if(hodnota == 0) digitalWrite(10, LOW); 
 }
 
}

 
