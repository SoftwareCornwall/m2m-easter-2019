
#include <NewPing.h>
#include </home/pi/Desktop/y2k/story_13_starwars/starWars.ino>
// Distance Sensors
#define TRIGGER_PIN 4
#define ECHO_PIN 5
#define TRIGGER_PIN_BOTTOM 13
#define ECHO_PIN_BOTTOM 17
#define MAX_DISTANCE 300
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
NewPing sonarBottom(TRIGGER_PIN_BOTTOM, ECHO_PIN_BOTTOM, MAX_DISTANCE);


// Motor Pins
int LME = 9;
int LMR = 7;
int LMF = 8;
int RME = 10;
int RMR = 11;
int RMF = 12;
/*
int LLS = A0;
int MLS = A1;
int RLS = A2;
*/
int LLS = A7;
int MLS = A6;
int RLS = A2;

int leftspeed = 200;
int rightspeed = 200;
//int turn90 = 582 * 1.37;
int turn90 = 800 * 1.37;
int mill = 10000;
const int LEFT_FEEDBACK = 3; // Pin numbers on Rover
const int RIGHT_FEEDBACK = 3; 
int distanceBottom;
int distance;
int highestNumber = 1000;
int numOfLoops = 25;
int numberOfTurns;
int reverseLoop;
int df;
volatile int leftcounter = 0; // initiate counter to zero for start 
volatile int rightcounter = 0; // counter could always be reset
int sensorValueLeft; 
int sensorValueMiddle; 
int sensorValueRight;


void setup() {
  Serial.begin(115200);
  pinMode(LME, OUTPUT);
  pinMode(RMR, OUTPUT);
  pinMode(RME, OUTPUT);
  pinMode(LMF, OUTPUT);
  pinMode(LMR, OUTPUT);
  pinMode(LME, OUTPUT);
  pinMode(MLS, OUTPUT);
  pinMode(6, OUTPUT);
  //pinMode(LLS, INPUT);
  //pinMode(MLS, INPUT);
  //pinMode(RLS, INPUT);

  attachInterrupt(digitalPinToInterrupt(LEFT_FEEDBACK),LeftMotorISR,RISING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_FEEDBACK),RightMotorISR,RISING);
  //attachInterrupt(digitalPinToInterrupt(LEFT_FEEDBACK),LeftMotorISR,RISING);
}

void loop() {
  //playTone();

                        

 
//turnRightIncrement(1000);
   delay(50);
   //forwards();

   followLightSource();
   stopMoving();
   exit(0);
}

void forwards() {
  /*
   * Moves rover forwards and doesn't stop
   */
  analogWrite(LME, leftspeed);
  analogWrite(RME, rightspeed);
  digitalWrite(LMF, HIGH);
  digitalWrite(RMF, HIGH);
  digitalWrite(LMR, LOW);
  digitalWrite(RMR, LOW);
}

void backwards() {
  /*
   * Moves rover backwards and doesn't stop
   */
  analogWrite(LME, leftspeed);
  analogWrite(RME, rightspeed);
  digitalWrite(LMF, LOW);
  digitalWrite(RMF, LOW);
  digitalWrite(LMR, HIGH);
  digitalWrite(RMR, HIGH);
}

void turnLeft(int turn){
  /*
   * Turns left 90 degrees 
   */
  analogWrite(LME, (leftspeed * 0.76));
  analogWrite(RME, (rightspeed * 0.76));
  digitalWrite(LMR, HIGH);
  digitalWrite(LMF, LOW);
  digitalWrite(RMR, LOW);
  digitalWrite(RMF, HIGH);
  delay(turn);
} 

void turnRight(int turn){
  /*
   * Turns right 90 degrees 
   */
  analogWrite(LME, (leftspeed * 0.735));
  analogWrite(RME, (rightspeed * 0.735));
  digitalWrite(RMR, HIGH);
  digitalWrite(RMF, LOW);
  digitalWrite(LMR, LOW);
  digitalWrite(LMF, HIGH);
  delay(turn);
}

void returnLeft(int turn){
  /*
   * Reverse Turns left 90 degrees 
   */
  analogWrite(LME, (leftspeed * 0.7));
  analogWrite(RME, (rightspeed * 0.7));
  digitalWrite(LMR, LOW);
  digitalWrite(LMF, HIGH);
  digitalWrite(RMR, HIGH);
  digitalWrite(RMF, LOW);
  delay(turn);
} 

void returnRight(int turn){
  /*
   * Reverse Turns right 90 degrees 
   */
  analogWrite(LME, (leftspeed * 0.767));
  analogWrite(RME, (rightspeed * 0.767));
  digitalWrite(RMR, LOW);
  digitalWrite(RMF, HIGH);
  digitalWrite(LMR, HIGH);
  digitalWrite(LMF, LOW);
  delay(turn);
}

void rightSquare(int turns) {
  /*
   * Make a square by turning right, uses 'turns' variable to set number of turns.
   */
  for (int i = 0; i < turns; i++) {
    forwards();
    delay(1100);
    turnRight(turn90);
    stopMoving();
    delay(1000);
  }
}

void leftSquare(int turns) {
  /*
   * Make a square by turning left, uses 'turns' variable to set number of turns.
   */
  for (int i = 0; i < turns; i++) {
    forwards();
    delay(1100);
    turnLeft(turn90);
    stopMoving();
    delay(1000);
  }
}   

void rerightSquare(int turns) {
  /*
   * Make a square by turning right, uses 'turns' variable to set number of turns.
   */
  for (int i = 0; i < turns; i++) {
    backwards();
    delay(1100);
    returnRight(turn90);
    stopMoving();
    delay(1000);
  }
}

void releftSquare(int turns) {
  /*
   * Make a square by turning left, uses 'turns' variable to set number of turns.
   */
  for (int i = 0; i < turns; i++) {
    backwards();
    delay(1100);
    returnLeft(turn90);
    stopMoving();
    delay(1000);
  }
}   

void counterForward(int counter = 975) {
  /*
   * Moves forwards for a set amount of counter.
   */
  if (rightcounter < counter) {
    forwards();   
  } 
}

void timedForward(int mill) {
  /*
   * Moves forwards for a set amount of counter.
   */

   int currentMillis = millis();
   
   
  Serial.print("Moving forwards!");
  forwards();
  if(currentMillis + mill >= mill){
    stopMoving();  
  } 
}

void timedBackward(int mill) {
  /*
   * Moves forwards for a set amount of counter.
   */
  backwards();
  if(millis() >= mill){
    stopMoving();  
  } 
}

void stopMoving() {
  /*
   * stops rover from moving 
   */
  digitalWrite(LME, HIGH);
  digitalWrite(RME, HIGH);
  digitalWrite(LMF, HIGH);
  digitalWrite(RMF, HIGH);
  digitalWrite(LMR, HIGH);
  digitalWrite(RMR, HIGH);
  delay(100);
  digitalWrite(LME, LOW);
  digitalWrite(RME, LOW);
}

void LeftMotorISR(){
    // adds one to the counter on each motor revolution
    leftcounter++;
}

void RightMotorISR(){
    // adds one to the counter on each motor revolution
    rightcounter++;
}

void avoidFront() {
  int distance = sonar.ping_cm();
  if (distance < 13){
    stopMoving();
    turnLeft(turn90);
    stopMoving();
  }
}

void avoidBottom() {
  int distanceBottom = sonarBottom.ping_cm();
  if (distance >= 13){
    delay(200);
    backwards();
    delay(750);
    stopMoving(); 
  }
}
void sensorRead() {
  sensorValueLeft = analogRead(LLS);
  sensorValueMiddle = analogRead(MLS);
  sensorValueRight = analogRead(RLS);
  
  Serial.print (sensorValueLeft);
    Serial.print("\n");
    Serial.print (sensorValueMiddle);
    Serial.print("\n");
    Serial.print (sensorValueRight);
    Serial.print("\n");
}
void followLightSource() {
  
  
  for (int i = 0; i <= numOfLoops; i++) {
    delay(100);
    sensorRead();
    Serial.print ("Right Turn: ");
    Serial.print(i);
    Serial.print("\n");

    

    turnRightIncrement(2000);
    //stopMoving(); 
    
    if (sensorValueMiddle < highestNumber) {
      highestNumber = sensorValueMiddle;
      numberOfTurns = i;
    } 
  }
  int reverseLoop = numOfLoops - numberOfTurns;
  for (int i = 0; i <= reverseLoop; i++) {
    
    delay(100);
    Serial.print ("Left Turn: ");
    Serial.print(i);
    Serial.print("\n");
    turnLeftIncrement(10);
    //stopMoving(); 
  }
  timedForward(5000);
}

void turnRightIncrement(int turn){
  /*
   * Turns right 90 degrees 
   */
  analogWrite(LME, (150));
  analogWrite(RME, (150));
  digitalWrite(RMR, HIGH);
  digitalWrite(RMF, LOW);
  digitalWrite(LMR, LOW);
  digitalWrite(LMF, HIGH);
  delay(300);
  digitalWrite(LMR, LOW);
  digitalWrite(LMF, LOW);
  digitalWrite(RMR, LOW);
  digitalWrite(RMF, LOW);
  delay(300);
}
void turnLeftIncrement(int turn){
  /*
   * Turns left 90 degrees 
   */
  analogWrite(LME, (150));
  analogWrite(RME, (150));
  digitalWrite(LMR, HIGH);
  digitalWrite(LMF, LOW);
  digitalWrite(RMR, LOW);
  digitalWrite(RMF, HIGH);
  delay(300);
   digitalWrite(LMR, LOW);
  digitalWrite(LMF, LOW);
  digitalWrite(RMR, LOW);
  digitalWrite(RMF, LOW);
  delay(300);
} 

