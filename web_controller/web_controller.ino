#include <controller.h>
#include <HTTPClient.h>
#include <ESP32Servo.h>

// NOTE: These are the leds fill in the pins pls
// #define LED_1 x 
// #define LED_2 x 
// #define LED_3 x 
// #define LED_4 x 

#define MOTOR_1_FORWARD 6
#define MOTOR_1_BACKWARD 4
#define MOTOR_2_FORWARD 5
#define MOTOR_2_BACKWARD 7
#define SERVO_1 2 // pins 2,4,12-19,21-23,25-27,32-33 are recommended

#define CONTROLLER_SENSITIVITY 64 // out of 128
#define SERVO_MAX_ROTATION 70
#define SERVO_MIN_ROTATION 0
#define ROTATION_STEP 10
#define ROTATION_SPEED 1000

#define IP 173 // expands to 192.168.1.173
#define PASS "brum" // Add this to the end of the url 192.168.1.173/brum

Controller c(IP, PASS);
// String serverPath = "http://192.168.1.138:8080";
// String direction = "/stop";

Servo servo = Servo();
bool buttonPressed = false;
bool movingUp = false;

void a_callback(bool pressed) {
  moveServo(true);
}

void b_callback(bool pressed) {
  moveServo(false);
}

void x_callback(bool pressed){
  movingUp = true;
  buttonPressed ^= pressed;
}

void y_callback(bool pressed){
  movingUp = false;
  buttonPressed ^= pressed;
}

void joystick_callback(int8_t x, int8_t y) {
  // Joystick changed position
  // HTTPClient http;
  String newDirection = "";

  if (y > CONTROLLER_SENSITIVITY){
    forward();
    newDirection = "/forward";
  }
  else if (y < -CONTROLLER_SENSITIVITY) {
    backward();
    newDirection = "/backward";
  }
  else if (x > CONTROLLER_SENSITIVITY){
    left();
    newDirection = "/left";
  }
  else if (x < -CONTROLLER_SENSITIVITY) {
    right();
    newDirection = "/right";
  }
  else {
    off();
    newDirection="/stop";
  }
   
  // if (newDirection != direction){
  //   http.begin((serverPath + newDirection).c_str());
  //   int httpResponse = http.GET();
  //   http.end();
  // }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(MOTOR_1_FORWARD, OUTPUT);
  pinMode(MOTOR_1_BACKWARD, OUTPUT);
  pinMode(MOTOR_2_FORWARD, OUTPUT);
  pinMode(MOTOR_2_BACKWARD, OUTPUT);
  servo.attach(SERVO_1);

  c.on_a(&a_callback);
  c.on_b(&b_callback);
  c.on_x(&x_callback);
  c.on_y(&y_callback);
  c.on_joystick(&joystick_callback);

  c.init();
  // NOTE: This is for the leds:
  // LedOn(LED_1)
  // LedOn(LED_2)
  // LedOn(LED_3)
  // LedOn(LED_4)
  
}

void loop() {
  if (buttonPressed){
    moveServoContinous(movingUp);
  }

}

void forward(){
	digitalWrite(MOTOR_1_FORWARD, HIGH);
	digitalWrite(MOTOR_2_FORWARD, HIGH);
	digitalWrite(MOTOR_1_BACKWARD, LOW);
	digitalWrite(MOTOR_2_BACKWARD, LOW);
}

void backward(){
	digitalWrite(MOTOR_1_FORWARD, LOW);
	digitalWrite(MOTOR_2_FORWARD, LOW);
	digitalWrite(MOTOR_1_BACKWARD, HIGH);
	digitalWrite(MOTOR_2_BACKWARD, HIGH);
}

void left(){
	digitalWrite(MOTOR_1_FORWARD, LOW);
	digitalWrite(MOTOR_2_FORWARD, HIGH);
	digitalWrite(MOTOR_1_BACKWARD, HIGH);
	digitalWrite(MOTOR_2_BACKWARD, LOW);
}

void right(){
	digitalWrite(MOTOR_1_FORWARD, HIGH);
	digitalWrite(MOTOR_2_FORWARD, LOW);
	digitalWrite(MOTOR_1_BACKWARD, LOW);
	digitalWrite(MOTOR_2_BACKWARD, HIGH);
}

void off(){
	digitalWrite(MOTOR_1_FORWARD, LOW);
	digitalWrite(MOTOR_2_FORWARD, LOW);
	digitalWrite(MOTOR_1_BACKWARD, LOW);
	digitalWrite(MOTOR_2_BACKWARD, LOW);
}

void moveServo(bool up){
  if (up){
    servo.write(SERVO_MAX_ROTATION);
  }
  else{
    servo.write(SERVO_MIN_ROTATION);
  }
}


void moveServoContinous(bool up){
  if (up){
    int currentRotation = servo.read();
    servo.write(currentRotation + ROTATION_STEP);
  }
  else{
    int currentRotation = servo.read();
    servo.write(currentRotation - ROTATION_STEP);
  }
  delay(ROTATION_SPEED);
}

void LedOn(int led) {
  digitalWrite(led, HIGH);
}

void LedOff(int led) {
  digitalWrite(led, LOW);
}

