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

#include <NewPing.h>

#define TRIGGER_PIN  13  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     17  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

//varibles
int sensory_turns_high = 400;
int highest_turn = 0;
int turn = 0;
int go = 0;
int fall = 0;
int first_step = 0;

//sensor pin numbers
int sensorPinLeft = A7;    // select the input pin for the potentiometer
int sensorPinMiddle = A6; 
int sensorPinRight = A2; 

void RightMotorISR(){
  rightcounter++;
}


void LeftMotorISR(){
  leftcounter++;
}


void setup() {
  
  Serial.begin(115200);
  
  attachInterrupt(digitalPinToInterrupt(Left_Feedback),LeftMotorISR,RISING);
  attachInterrupt(digitalPinToInterrupt(Right_Feedback),RightMotorISR,RISING);

  //turning the motor on
  pinMode(Left_Motor_onOff, OUTPUT);
  pinMode(Left_Motor_Forward, OUTPUT);
  pinMode(Left_Motor_Backward, OUTPUT);

  pinMode(Right_Motor_onOff, OUTPUT);
  pinMode(Right_Motor_Forward, OUTPUT);
  pinMode(Right_Motor_Backward, OUTPUT);

  //sending a ping out that the rover use to scan how far an object is away
  Serial.print(sonar.ping_cm());

  //turn the light sensors on
  pinMode(sensorPinLeft, INPUT);
  pinMode(sensorPinMiddle, INPUT);
  pinMode(sensorPinRight, INPUT);

}

void loop(){

  //first makes a firgue of eight
  if(first_step == 0){
    square_right();    
    square_left();
    turn_left_max();
    delay(5200);
    first_step = 1;
  }

  //next does a scan to find the position of the strongest light in it's surroundings
  if(go == 0 and first_step == 1){
    light_find();
  }

  //it will then positon it self facing the strongest light
  if (turn >= 20 and go == 0){
    roverStop();
    delay(1000);
    light_go();
    go = 1;
  }
  
  //will start to move towards it and will correct it self to have the best precison
  if(go == 1){
    light_move();
  }

  //the rover will finally make it way up a ramp, it will start sending signals to the floor and eventually come towards an edge, stop before falling and move back
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");

  int down_distance = sonar.ping_cm();
 
  if (down_distance >= 14 and fall == 0){
    Serial.print("greater than 12");
    fall = 1;
    roverStop();
    delay(1000);
    backward();
    delay(350);
    roverStop();
  }

  //the rover will do a 360 left then another going right
  if (fall == 1){
    turn_left();
    delay(4000);
    turn_right();
    delay(6000);
    //forward();
  }

}


