const int elm = 9; // Enable left motor
const int erm = 10; // enable right motor
const int rfm = 12;// right motor forwards
const int lfm = 8;// left motor forwards
const int rrm = 11;// right motor reverse
const int lrm = 7;// left motor reverse

const int lip = 2;// Left motor interrupt 
const int rip = 3; //right motor interrupt
//const int test = 3; //right motor interrupt

volatile int rpulseCount = 0;
volatile int lpulseCount = 0;


class motor
{

  private:
  
  const int enablePin;
  const int forwardPin;
  const int reversePin; 
  
  public:
  
  motor(int ePin, int fPin, int rPin);
  ~motor();

  void enable();
  void moveForward(int speed);
  void moveBackward(int speed);
  void halt(); 
  void pulse(); 
  void correctPath();
  void goForward();

  volatile int pulseCount;
  volatile int thisSpeed = 200;
};

motor::motor(int ePin, int fPin, int rPin) :
  enablePin(ePin),
  forwardPin(fPin),
  reversePin(rPin)

{  
  pinMode(enablePin, OUTPUT);
  pinMode(forwardPin, OUTPUT);
  pinMode(reversePin, OUTPUT);

  pulseCount = 0; 

}


motor::~motor()
{
}

void motor::enable()
{
  analogWrite(enablePin, thisSpeed);
}

void motor::moveForward(int speed) 
{
  analogWrite(forwardPin, speed);
  thisSpeed = speed;
}

void motor::moveBackward(int speed) 
{
  analogWrite(reversePin, speed);
  thisSpeed = speed;
}

void motor::goForward(){
  analogWrite(enablePin, 255);
  analogWrite(forwardPin, thisSpeed);
  analogWrite(reversePin, thisSpeed);
  
}

//void motor::turnRight90()
//{
  
 // leftMotor.forwardPin()
 // rightMotor.reversePin()
 // if(millis() >=10000) {
//stopRover(30000);
//}

void motor::halt()
{
  analogWrite(forwardPin, 0);
  analogWrite(reversePin, 0);
  analogWrite(enablePin, 0);
}

void motor::pulse()
{
  pulseCount++;
}

//void motor::correctPath()


motor leftMotor(elm, lfm, lrm);
motor rightMotor(erm, rfm, rrm);

void lMotorPulse()
{
  lpulseCount++;
}

void rMotorPulse()
{
  rpulseCount++;
}

void stopRover(int time)
{
  rightMotor.halt();
  leftMotor.halt();
  delay(time);
}

void setup() 
{
  // put your setup code here, to run once:
 
  leftMotor.enable();
  rightMotor.enable();

  Serial.begin(115200); 

  attachInterrupt(digitalPinToInterrupt(lip), lMotorPulse, RISING);
  attachInterrupt(digitalPinToInterrupt(rip), rMotorPulse, RISING);

}

void loop() 
{
  // put your main code here, to run repeatedly:
  /*Serial.print ("Left Motor Pulse Count:");
  Serial.print (leftMotor.pulseCount);
  Serial.print ("\n");
  Serial.print ("Right Motor Pulse Count:");
  Serial.print (rightMotor.pulseCount);
  /Serial.print ("\n");
  //delay(100);
  
  leftMotor.moveForward(220);
  rightMotor.moveForward(150);
  
  if (rightMotor.pulseCount > leftMotor.pulseCount){
      leftMotor.moveForward(220);
      Serial.print ("\n");
      Serial.print ("left adj");
      Serial.print ("\n");
       Serial.print ("\n");
    Serial.print (leftMotor.thisSpeed);
    Serial.print (" - ");
    Serial.print (rightMotor.thisSpeed);
    Serial.print ("\n");
  

  } else if (leftMotor.pulseCount > rightMotor.pulseCount) {
    rightMotor.moveForward(220);
    Serial.print ("\n");
    Serial.print ("right adj");
    Serial.print ("\n");
    Serial.print (leftMotor.thisSpeed);
    Serial.print (" - ");
    Serial.print (rightMotor.thisSpeed);
    Serial.print ("\n");
  } else {
    
  }

 // if(millis() >=10000) {
    //stopRover(30000);
  //}


 if(leftMotor.pulseCount > rightMotor.pulseCount){
  //leftMotor - 1;
  leftMotor.moveForward(leftMotor.thisSpeed - 1);
  rightMotor.moveForward(rightMotor.thisSpeed + 1);
 }
 else if(rightMotor.pulseCount > leftMotor.pulseCount){
  //rightMotor - 1;
  rightMotor.moveForward(rightMotor.thisSpeed - 1);
  leftMotor.moveForward(leftMotor.thisSpeed + 1);
 }

 else if(rightMotor.pulseCount - leftMotor.pulseCount <= 2){
  //leftMotor + 1;
  leftMotor.moveForward(leftMotor.thisSpeed + 1);
  
 }*/

 if(millis() >=10000) {
    stopRover(30000);
 } else {
  //leftMotor.goForward();
  //rightMotor.goForward();

  if(lpulseCount > rpulseCount){
    //leftMotor - 1;
    leftMotor.moveForward(leftMotor.thisSpeed - 1);
    rightMotor.moveForward(rightMotor.thisSpeed + 1);
  }
  if(rpulseCount > lpulseCount){
    //rightMotor - 1;
    rightMotor.moveForward(rightMotor.thisSpeed - 1);
    leftMotor.moveForward(leftMotor.thisSpeed + 1);
  }else {
    leftMotor.moveForward(leftMotor.thisSpeed);
    rightMotor.moveForward(rightMotor.thisSpeed);
  }
 }
}

