String receivedChar;
 int hodnota;

void setup() {
 Serial.begin(9600);
 pinMode(10, OUTPUT);
   Serial.println("hodnota je :");  Serial.println( hodnota); 
}

void loop() {
 recvOneChar();
 
}

void recvOneChar() {
  
 if (Serial.available() > 0) 
 {
   receivedChar =Serial.readString();
   hodnota=receivedChar.toInt();
   analogWrite(10,hodnota);
     Serial.println("hodnota je :");  Serial.println( hodnota);      
  
 }
 
}

 
