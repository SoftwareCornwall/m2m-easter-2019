// LEFT MOTOR PINS
int Left_Motor_onOff = 9;
int Left_Motor_Forward = 8;
int Left_Motor_Backward = 7;

// RIGHT MOTOR PINS
int Right_Motor_onOff = 10;
int Right_Motor_Forward = 12;
int Right_Motor_Backward = 11;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(Left_Motor_onOff, OUTPUT);
  pinMode(Left_Motor_Forward, OUTPUT);
  pinMode(Left_Motor_Backward, OUTPUT);

  
  pinMode(Right_Motor_onOff, OUTPUT);
  pinMode(Right_Motor_Forward, OUTPUT);
  pinMode(Right_Motor_Backward, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {                  

  // motor indicator lights on
  digitalWrite(Left_Motor_onOff, HIGH);
  digitalWrite(Right_Motor_onOff, HIGH);
  // wait one second
  delay(1000);
    
  // move forward for 10 seconds 
  digitalWrite(Left_Motor_Forward, HIGH); 
  digitalWrite(Right_Motor_Forward, HIGH);
  delay(1000);
    
  // turn on backward momentum to stop rover
  digitalWrite(Left_Motor_Backward, HIGH);
  digitalWrite(Right_Motor_Backward,HIGH);
  delay(1000);
  
  //reverse
  digitalWrite(Right_Motor_Forward, LOW);
  digitalWrite(Left_Motor_Forward, LOW);
  delay(1000);
  //stop
  digitalWrite(Left_Motor_Backward,LOW);
  digitalWrite(Right_Motor_Backward,LOW); 
  delay(1000);
  digitalWrite(Left_Motor_onOff, LOW);
  digitalWrite(Right_Motor_onOff, LOW);
  exit(0);
}


