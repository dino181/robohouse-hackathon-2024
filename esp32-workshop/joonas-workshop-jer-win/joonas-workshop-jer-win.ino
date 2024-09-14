#define LED 1

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  Serial.begin(115200);
  Serial.println("Start blinky");
}

void loop() {
  // put your main code here, to run repeatedly:
  ledON();
  delay(200);

  ledOFF();
  delay(200);
}

void ledON() {
  Serial.println("LED ON");
  digitalWrite(LED, LOW);
}

void ledOFF() {
  Serial.println("LED OFF");
  digitalWrite(LED, HIGH);
}
