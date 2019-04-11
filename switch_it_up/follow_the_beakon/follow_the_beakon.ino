
int sensory_turns_high = 400;
int highest_turn = 0;
int turn = 0;
int go = 0;

// Motor Speed
int Left_Motor_Speed = 127;   //200
int Right_Motor_Speed = 127;   //200
int start_time = millis();

int sensorPinLeft = A7;    // select the input pin for the potentiometer
int sensorPinMiddle = A6; 
int sensorPinRight = A2; 

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
  
  // activate left and right motors
  pinMode(Left_Motor_onOff, OUTPUT);
  pinMode(Left_Motor_Forward, OUTPUT);
  pinMode(Left_Motor_Backward, OUTPUT);

  pinMode(Right_Motor_onOff, OUTPUT);
  pinMode(Right_Motor_Forward, OUTPUT);
  pinMode(Right_Motor_Backward, OUTPUT);

  pinMode(sensorPinLeft, INPUT);
  pinMode(sensorPinMiddle, INPUT);
  pinMode(sensorPinRight, INPUT);

}


void loop(){
  if(go == 0){
    light_find();
  }
  if (turn >= 20 and go == 0){
    roverStop();
    delay(2000);
    light_go();
    go = 1;
  }
  if(go == 1){
    light_move();
  }
}



//look back towards strongest light source
void light_go(){
  for(int i = 0; i <= highest_turn; i++){
    turn_left();
    delay(260);
    roverStop();
    delay(350);
  }
}

//this code will make the rover correct it self
void light_move(){
  int sensorValueLeft = analogRead(sensorPinLeft);
  int sensorValueRight = analogRead(sensorPinRight);
  forward();
  if(sensorValueLeft < sensorValueRight){
    Left_Motor_Speed = 50;
    Right_Motor_Speed = 200;
  }
  
  else if(sensorValueLeft > sensorValueRight){
    Right_Motor_Speed = 50;  
    Left_Motor_Speed = 200;
  }
  else{
    Right_Motor_Speed = 200;   //127
    Left_Motor_Speed = 200;   //127
  }
}

void light_find(){
  // read the value from the sensor:
  //int sensorValueLeft = analogRead(sensorPinLeft);
  int sensorValueMiddle = analogRead(sensorPinMiddle);
  //int sensorValueRight = analogRead(sensorPinRight);
  if(sensorValueMiddle < sensory_turns_high){;
    sensory_turns_high = sensorValueMiddle;
    highest_turn = turn;
  }
  delay(250);
  Serial.print(sensorValueMiddle);
  Serial.println(" sensorValueMiddle");
  turn_left();
  turn ++;
  delay(260);
  roverStop();
  delay(200);
}

  //Serial.print(sensorValueRight);
  //Serial.println(" sensorValueRight");
  //Serial.print(sensorValueLeft);
  //Serial.println(" sensorValueLeft");
