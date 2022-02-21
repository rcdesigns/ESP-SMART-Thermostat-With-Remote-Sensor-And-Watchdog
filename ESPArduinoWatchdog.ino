int pinToRead = 5;
int pinToWrite = 2;
unsigned long lastTimeUpdate = 0;
int lastPinRead = 0;

void setup() {
   // put your setup code here, to run once:
   Serial.begin(9600);
   Serial.println();

   pinMode(pinToRead, INPUT);
   pinMode(pinToWrite, OUTPUT);   // initialize the digital pin as an output.
   digitalWrite(pinToWrite, LOW);
   delay(10000); // wait to give the ESP32 controller chance to set its output pin on start-up 
}

void loop() {
   // put your main code here, to run repeatedly:
   int pinRead = digitalRead(pinToRead);
   if (pinRead != lastPinRead)
   {
      // turn on output
      digitalWrite(pinToWrite, HIGH); // turn output on
      lastTimeUpdate = millis();
   }
   else
   {
      if ((millis() - lastTimeUpdate) > 120000)
      {
         // turn output off
         digitalWrite(pinToWrite, LOW);
      }
   }
   lastPinRead = pinRead;
   delay(10000);
}
