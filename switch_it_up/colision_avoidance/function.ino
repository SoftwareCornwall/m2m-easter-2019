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


void left_turn_avoid() {
// drive forwards
  forward();
  // find distance
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");

  int distance = sonar.ping_cm();

  // if close enough to a wall
  if (distance <= 30 and distance != 0) {
    roverStop();
    delay(3000);
    turn_left();
    Serial.print("turning left");  // turn 90 degress left
    delay(1000);
    roverStop();
    exit(0);
   }

}
