int ledPin = 13;
int ledPin2 = 12;

void setup() {
  pinMode(ledPin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ledPin, HIGH);
  digitalWrite(ledPin2, HIGH);
  delay(100);
  digitalWrite(ledPin, LOW);
  digitalWrite(ledPin2, LOW);
  delay(100);
}

