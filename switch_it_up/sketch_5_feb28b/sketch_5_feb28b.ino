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
int Left_Motor_Speed = 200;   //127
int Right_Motor_Speed = 200;   //127
int start_time = millis();


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

  
}

void loop() {

  square_right();
  square_left();
  square_Left_back();
  square_Right_back();
  roverStop();
  exit(0);
  
}

void two_metres(){
  
  if(leftcounter > 871 or rightcounter > 871){
    roverStop();
    exit(0);
  }
  
  Serial.println("Left Counter ");
  Serial.print(leftcounter);

  Serial.println("Right Counter ");
  Serial.print(rightcounter);

  forward();

  if((rightcounter-leftcounter)<=-3){
    Left_Motor_Speed = 72;
    Right_Motor_Speed = 128;
  }
  else if((rightcounter-leftcounter)>=3){
    Right_Motor_Speed = 72;   //70
    Left_Motor_Speed = 128;   //127
  }
  else{
    Right_Motor_Speed = 128;   //127
    Left_Motor_Speed = 128;   //127
  }
}



void triangle(){

  for(int corner=0; corner<3; corner++){
    forward();
    delay(3000);
    roverStop();
    turn_right();
    delay(2400);
    roverStop();
    delay(1000);
  }
}

void LeftMotorISR(){
  leftcounter++;
}

void RightMotorISR(){
  rightcounter++;
}
void forward() {
  analogWrite(Left_Motor_onOff, Left_Motor_Speed);
  analogWrite(Right_Motor_onOff, Right_Motor_Speed);

  digitalWrite(Left_Motor_Forward, HIGH); 
  digitalWrite(Right_Motor_Forward, HIGH);
}

void backward() {
  digitalWrite(Left_Motor_onOff, HIGH);
  digitalWrite(Right_Motor_onOff, HIGH);

  digitalWrite(Left_Motor_Backward, HIGH); 
  digitalWrite(Right_Motor_Backward, HIGH);
}

//stop rover
void roverStop() {
  digitalWrite(Left_Motor_onOff, LOW);
  digitalWrite(Right_Motor_onOff, LOW);

  digitalWrite(Left_Motor_Forward, LOW); 
  digitalWrite(Right_Motor_Forward, LOW);

  digitalWrite(Left_Motor_Backward, LOW);
  digitalWrite(Right_Motor_Backward, LOW);
}

//go forward for 10 seconds
void forward10() {
  // put your main code here, to run repeatedly:
  
  // motor indicator lights on
  digitalWrite(Left_Motor_onOff, HIGH);
  digitalWrite(Right_Motor_onOff, HIGH);
  // wait one second
  delay(1000);
    
  // move forward for 10 seconds 
  digitalWrite(Left_Motor_Forward, HIGH); 
  digitalWrite(Right_Motor_Forward, HIGH);
  delay(10000);
  //stop
  digitalWrite(Left_Motor_Forward,LOW);
  digitalWrite(Right_Motor_Forward,LOW); 
  delay(1000);
  digitalWrite(Left_Motor_onOff, LOW);
  digitalWrite(Right_Motor_onOff, LOW);
  exit(0);
}


