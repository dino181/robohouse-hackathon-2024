#define LED 3

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  Serial.begin(115200);
  Serial.println("Start blinky");
}

void loop() {
  // put your main code here, to run repeatedly:
  
}


void ledON() {
  Serial.println(
}
