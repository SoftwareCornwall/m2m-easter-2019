int LME = 9;
int LMR = 7;
int LMF = 8;
int RME = 10;
int RMR = 11;
int RMF = 12;
int leftspeed = 211;
int rightspeed = 172;
int turn90 = 947;

const int LEFT_FEEDBACK = 3; // Pin numbers on Rover
const int RIGHT_FEEDBACK = 3; 

volatile int leftcounter = 0; // initiate counter to zero for start 
volatile int rightcounter = 0; // counter could always be reset

void setup() {
  Serial.begin(115200);
  pinMode(LME, OUTPUT);
  pinMode(RMR, OUTPUT);
  pinMode(RME, OUTPUT);
  pinMode(LMF, OUTPUT);
  pinMode(LMR, OUTPUT);
  pinMode(LME, OUTPUT);
  
  attachInterrupt(digitalPinToInterrupt(LEFT_FEEDBACK),LeftMotorISR,RISING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_FEEDBACK),RightMotorISR,RISING);
}

void loop() {
   forwards();
   makesquare(4);
    forwards();
    delay(1100);
    leftsquare(4);
   stop(5000);
  
  /*if(millis() >= 10000){
    stop(20000);
  }else{
    
    
 // }
  */
}
void forwards() {
  analogWrite(LME, leftspeed);
  analogWrite(RME, rightspeed);
  digitalWrite(LMF, HIGH);
  digitalWrite(RMF, HIGH);
  digitalWrite(LMR, LOW);
  digitalWrite(RMR, LOW);
}

void turnright(int turn90){
  analogWrite(LME, leftspeed);
  analogWrite(RME, rightspeed);
  digitalWrite(RMR, HIGH);
  digitalWrite(RMF, LOW);
  delay(turn90);
}

void makesquare(int turns) {
  for (int i = 0; i < turns; i++) {
    forwards();
    delay(1100);
    turnright(turn90);
   }
}

void leftsquare(int turns) {
  for (int i = 0; i < turns; i++) {
    forwards();
    delay(1100);
    turnleft(turn90);
   }
}   
void turnleft(int turn90){
  analogWrite(LME, leftspeed);
  analogWrite(RME, rightspeed);
  digitalWrite(RMR, LOW);
  digitalWrite(RMF, HIGH);
  delay(turn90);
} 
void timedForward() {
  
    if (rightcounter < 975){
      forwards();
      
    } else {
      //exit(0);
      stop(20000);
    }
}

void forwardWithDelay(int time) {
  analogWrite(LME, leftspeed);
  analogWrite(RME, rightspeed);
  digitalWrite(LMF, HIGH);
  digitalWrite(RMF, HIGH);
  digitalWrite(LMR, LOW);
  digitalWrite(RMR, LOW);
  delay(10000);
    
}

void stop(int time) {
  digitalWrite(LME, HIGH);
  digitalWrite(RME, HIGH);
  digitalWrite(LMF, HIGH);
  digitalWrite(RMF, HIGH);
  digitalWrite(LMR, HIGH);
  digitalWrite(RMR, HIGH);
  delay(time);
}


void LeftMotorISR(){
    // adds one to the counter on each motor revolution
    leftcounter++;
}

void RightMotorISR(){
    // adds one to the counter on each motor revolution
    rightcounter++;
}

