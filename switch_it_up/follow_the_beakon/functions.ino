


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


