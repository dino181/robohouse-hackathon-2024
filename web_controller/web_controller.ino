 #include <controller.h>
#include <HTTPClient.h>
#include <ESP32Servo.h>

// NOTE: These are the leds fill in the pins pls
// #define LED_1 x 
// #define LED_2 x 
// #define LED_3 x 
// #define LED_4 x 

#define MOTOR_1_FORWARD 4
#define MOTOR_1_BACKWARD 6
#define MOTOR_2_FORWARD 7
#define MOTOR_2_BACKWARD 5
#define SERVO_1 2 // pins 2,4,12-19,21-23,25-27,32-33 are recommended

#define CONTROLLER_SENSITIVITY 64 // out of 128
#define SERVO_MAX_ROTATION 70
#define SERVO_MIN_ROTATION 0
#define ROTATION_STEP 10
#define ROTATION_SPEED 1000

#define IP 173 // expands to 192.168.1.173
#define PASS "brum" // Add this to the end of the url 192.168.1.173/brum


Controller c(IP, PASS);

Servo servo = Servo();
bool buttonPressed = false;
bool movingUp = false;
int direction = 0;
bool driving = false;

void a_callback(bool pressed) {
  moveServo(true);
}

void b_callback(bool pressed) {
  moveServo(false);
}

void x_callback(bool pressed){
  movingUp = true;
  buttonPressed = pressed;
}

void y_callback(bool pressed){
  movingUp = false;
  buttonPressed = pressed;
}


void fw_callback(bool pressed) {
   driving = pressed;
   direction = 1; 
}

void bw_callback(bool pressed) {
   driving = pressed;
   direction = 2; 
}

void l_callback(bool pressed) {
   driving = pressed;
   direction = 3;
}

void r_callback(bool pressed) {
   driving = pressed;
   direction = 4;
}



void joystick_callback(int8_t x, int8_t y) {
  if (y > CONTROLLER_SENSITIVITY){
    forward();
  }
  else if (y < -CONTROLLER_SENSITIVITY) {
    backward();
  }
  else if (x > CONTROLLER_SENSITIVITY){
    left();
  }
  else if (x < -CONTROLLER_SENSITIVITY) {
    right();
  }
  else {
    stop();
  }
   
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
  c.on_fw(&fw_callback);
  c.on_bw(&bw_callback);
  c.on_l(&l_callback);
  c.on_r(&r_callback);
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

  if (driving){
     if (direction == 1){
       forward();
     }
     else if (direction == 2){
       backward();
     }
     else if (direction == 3){
       left();
     }
     else if (direction == 4){
       right();
     }
   }
   else {
     stop();
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

void stop(){
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
