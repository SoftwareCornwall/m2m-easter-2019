//makes a square where when it gets to the corners it turns right
void square_right(){

    
    forward();
    delay(1200);
    roverStop();
    turn_right();
    delay(1150);
    roverStop();
    delay(200);

    
    forward();
    delay(1200);
    roverStop();
    turn_right();
    delay(1110);
    roverStop();
    delay(200);

    
    forward();
    delay(1200);
    roverStop();
    turn_right();
    delay(1260);
    roverStop();
    delay(200);

    
    forward();
    delay(1200);
    roverStop();
    turn_left();
    delay(1200);
    roverStop();
    delay(200);
  
}
//makes a square where when it gets to the corners it turns left
void square_left(){

    
    forward();
    delay(1200);
    roverStop();
    turn_left();
    delay(1000);
    roverStop();
    delay(200);

    
    forward();
    delay(1200);
    roverStop();
    turn_left();
    delay(970);
    roverStop();
    delay(200);

    
    forward();
    delay(1200);
    roverStop();
    turn_left();
    delay(1040);
    roverStop();
    delay(200);

    
    forward();
    delay(1200);
    roverStop();
    turn_right();
    delay(1100);
    roverStop();
    delay(200);
  
}

//turn right
void turn_right(){

  analogWrite(Left_Motor_onOff, 140);
  analogWrite(Right_Motor_onOff, 140);

  digitalWrite(Left_Motor_Forward, HIGH);
  digitalWrite(Right_Motor_Backward, HIGH);
}

//turn left
void turn_left(){

  analogWrite(Right_Motor_onOff, 140);
  analogWrite(Left_Motor_onOff, 140);

  digitalWrite(Right_Motor_Forward, HIGH);
  digitalWrite(Left_Motor_Backward, HIGH);
}

//moves forward at a constant speed
void forward() {
  analogWrite(Left_Motor_onOff, Left_Motor_Speed);
  analogWrite(Right_Motor_onOff, Right_Motor_Speed);

  digitalWrite(Left_Motor_Forward, HIGH); 
  digitalWrite(Right_Motor_Forward, HIGH);
}
//moves backwards at a constant speed
void backward(){
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

//turns the rover to the spot that had the strongest light source
void light_go(){
  for(int i = 0; i <= highest_turn; i++){
    turn_left();
    delay(260);
    roverStop();
    delay(100);
  }
}

//this code will make the rover correct it self and move it to the light
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

//makes the rover do a turn, scan to find the strongest light and repeat until it does a 360
void light_find(){
  // read the value from the sensor:
  int sensorValueMiddle = analogRead(sensorPinMiddle);
  if(sensorValueMiddle < sensory_turns_high){;
    sensory_turns_high = sensorValueMiddle;
    highest_turn = turn;
  }
  delay(40);
  Serial.print(sensorValueMiddle);
  Serial.println(" sensorValueMiddle");
  turn_left();
  turn ++;
  delay(260);
  roverStop();
  delay(40);
}

void turn_left_max(){

  analogWrite(Right_Motor_onOff, 255);
  analogWrite(Left_Motor_onOff, 255);

  digitalWrite(Right_Motor_Forward, HIGH);
  digitalWrite(Left_Motor_Backward, HIGH);
}
