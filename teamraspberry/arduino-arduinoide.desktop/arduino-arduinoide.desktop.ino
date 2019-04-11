#include <NewPing.h>

#define TRIGGER_PIN  4  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     5  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define TRIGGER_height_PIN  13  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_height_PIN     17  // Arduino pin tied to echo pin on the ultrasonic sensor.
NewPing sonar_height(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar_distance(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);


const int left_light_pin = A7;
const int center_light_pin = A6;
const int right_light_pin = A2;

const int down_trigger = 13;
const int down_echo = 17;

int motor_left_enable = 9;
int motor_left_reverse = 7;
int motor_left_forward =8;
int motor_right_enable = 10 ;
int motor_right_reverse = 11;
int motor_right_forward = 12;

int analogleft = 127;  
int analogright =127;

//feedback stuff
const int LEFT_FEEDBACK = 2;
const int RIGHT_FEEDBACK = 3;

volatile int lc = 0;
volatile int rc = 0;


void setup() {

  pinMode(motor_left_reverse, OUTPUT);
  pinMode(motor_left_enable, OUTPUT);
  pinMode(motor_left_forward,OUTPUT);
  pinMode(motor_right_reverse, OUTPUT);
  pinMode(motor_right_enable, OUTPUT);
  pinMode(motor_right_forward,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(LEFT_FEEDBACK), LeftMotorISR, RISING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_FEEDBACK), RightMotorISR, RISING);
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.

  
}

int count=0;
int leftcount=0;


void loop() {
  
/*  rightsquare();
  forward();
  corner(65, "left");//65
  leftsquare();
  
  if (count == 4){
    roverstop();
  }*/

  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.

int height = sonar_height.ping_cm();
int distance = sonar_distance.ping_cm();

straightforward();   

if (height> 14 ) {
  stopping();
  analogWrite(motor_left_enable,analogleft );
  analogWrite(motor_right_enable,analogright);
  
  digitalWrite(motor_left_forward, LOW);
  digitalWrite(motor_right_forward,LOW);

  digitalWrite(motor_left_reverse, LOW);
  digitalWrite(motor_right_reverse, LOW);
  back();
  delay(350);
  analogWrite(motor_left_enable,analogleft );
  analogWrite(motor_right_enable,analogright);
  
  digitalWrite(motor_left_forward, LOW);
  digitalWrite(motor_right_forward,HIGH);

  digitalWrite(motor_left_reverse, HIGH);
  digitalWrite(motor_right_reverse, LOW);
  delay(1850);
}

straightforward();  
  
  if ((distance > 1)&&(distance<17)){
      stopping();
      delay(2500);
      analogWrite(motor_left_enable,analogleft );
      analogWrite(motor_right_enable,analogright);
  
      digitalWrite(motor_left_forward, LOW);
      digitalWrite(motor_right_forward,HIGH);

      digitalWrite(motor_left_reverse, HIGH);
      digitalWrite(motor_right_reverse, LOW);
      //corner(75, "left");
      delay(925);
      stopping();
      exit(0);
    }
     
}


void LeftMotorISR(){
    lc++;
}

void RightMotorISR(){
    rc++;
}

void forward() {
  analogWrite(motor_left_enable,analogleft );
  analogWrite(motor_right_enable,analogright);
  
  digitalWrite(motor_left_forward, HIGH);
  digitalWrite(motor_right_forward,HIGH);

  digitalWrite(motor_left_reverse, LOW);
  digitalWrite(motor_right_reverse, LOW);
}

void back() {
  analogWrite(motor_left_enable,analogleft );
  analogWrite(motor_right_enable,analogright);
  
  digitalWrite(motor_left_forward, LOW);
  digitalWrite(motor_right_forward,LOW);

  digitalWrite(motor_left_reverse, HIGH);
  digitalWrite(motor_right_reverse, HIGH);
}
void stopping() {
  Serial.print("STOPPING");
  Serial.print("\n");
  digitalWrite(motor_left_enable,LOW);
  digitalWrite(motor_right_enable,LOW);
  
  digitalWrite(motor_left_forward, LOW);
  digitalWrite(motor_right_forward, LOW);
  
  digitalWrite(motor_left_reverse,LOW);
  digitalWrite(motor_right_reverse,LOW);
}

