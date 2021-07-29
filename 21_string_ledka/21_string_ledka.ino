String receivedChar="0";
 

void setup() {
 Serial.begin(9600);
 pinMode(10, OUTPUT);
 //Serial.println("<Arduino is ready>");
}

void loop() {
 recvOneChar();
  
}

void recvOneChar() {
 
 
 
  if  (receivedChar == "1")           
    { 
    digitalWrite(10, HIGH);
    }
    if(receivedChar == "0")         
    { 
    digitalWrite(10, LOW);
    }
  
  
}
