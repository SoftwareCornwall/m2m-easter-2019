void square_right(){

    
    forward();
    delay(1200);
    roverStop();
    turn_right();
    delay(1050);
    roverStop();
    delay(1000);

    
    forward();
    delay(1200);
    roverStop();
    turn_right();
    delay(1050);
    roverStop();
    delay(1000);

    
    forward();
    delay(1200);
    roverStop();
    turn_right();
    delay(1100);
    roverStop();
    delay(1000);

    
    forward();
    delay(1200);
    roverStop();
    turn_left();
    delay(1050);
    roverStop();
    delay(1000);
  
}

void square_left(){

    
    forward();
    delay(1200);
    roverStop();
    turn_left();
    delay(950);
    roverStop();
    delay(1000);

    
    forward();
    delay(1200);
    roverStop();
    turn_left();
    delay(950);
    roverStop();
    delay(1000);

    
    forward();
    delay(1200);
    roverStop();
    turn_left();
    delay(1020);
    roverStop();
    delay(1000);

    
    forward();
    delay(1200);
    roverStop();
    turn_right();
    delay(1100);
    roverStop();
    delay(1000);
  
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
