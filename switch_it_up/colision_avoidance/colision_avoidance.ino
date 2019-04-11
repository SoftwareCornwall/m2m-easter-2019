// LEFT MOTOR PINS
int Left_Motor_onOff = 9;
int Left_Motor_Forward = 8;
int Left_Motor_Backward = 7;

// RIGHT MOTOR PINS
int Right_Motor_onOff = 10;
int Right_Motor_Forward = 12;
int Right_Motor_Backward = 11;

//set pins
const int Left_Feedback = 2;
const int Right_Feedback = 3;

volatile int leftcounter = 0;

volatile int rightcounter = 0;

// Motor Speed
int Left_Motor_Speed = 127;   //200
int Right_Motor_Speed = 127;   //200
int start_time = millis();

#include <NewPing.h>

#define TRIGGER_PIN  13  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     17  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


void setup() {
  //current time for start (milli-seconds)
 
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(Left_Feedback),LeftMotorISR,RISING);
  attachInterrupt(digitalPinToInterrupt(Right_Feedback),RightMotorISR,RISING);
  
  // put your setup code here, to run once:
  pinMode(Left_Motor_onOff, OUTPUT);
  pinMode(Left_Motor_Forward, OUTPUT);
  pinMode(Left_Motor_Backward, OUTPUT);

  
  pinMode(Right_Motor_onOff, OUTPUT);
  pinMode(Right_Motor_Forward, OUTPUT);
  pinMode(Right_Motor_Backward, OUTPUT);

  Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result
  
}

void loop() {
  // drive forwards
  forward();
  // find distance
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");

  int down_distance = sonar.ping_cm();
 
  // if close enough to a wall
  if (down_distance >= 15 ) {
    Serial.print("greater than 12");
    roverStop();
    delay(1000);
    backward();
    delay(350);
    roverStop();
    exit(0);
  }
  

}
