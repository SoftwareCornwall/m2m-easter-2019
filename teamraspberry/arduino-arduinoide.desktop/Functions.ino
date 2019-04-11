void straightforward(){  
  forward();

  if (lc>rc){
    analogright=190;//190
    analogleft =185;//185
    //Serial.println("Right Speed");
  }
  else if (rc>lc){
    analogleft=190;//190
    analogright=185;//185
    //Serial.println("Left Speed");
  }
  else {
    analogleft = 185;//185  
    analogright =185;//185
    //Serial.println("Same Speed");
  }
}
void straightback(){  
  back();

  if (lc>rc){
    analogright=190;//190
    analogleft =185;//185
    //Serial.println("Right Speed");
  }
  else if (rc>lc){
    analogleft=190;//190
    analogright=185;//185
    //Serial.println("Left Speed");
  }
  else {
    analogleft = 185;//185  
    analogright =185;//185
    //Serial.println("Same Speed");
  }
}
void corner(int ticks, String direct){
  Serial.print(direct);
  Serial.print(" Corner Called");
  Serial.print("\n");
  delay (1000);
   
  analogleft = 127;//127
  analogright = 127;//127
  while (lc<ticks){ 
    analogWrite(motor_left_enable,analogleft);
    analogWrite(motor_right_enable,analogright);
    //Serial.print("analog");
    //Serial.print(direct);
    //Serial.print(": ");
    //Serial.print("\n");
    //Serial.print(analogright);
    if (direct == "left"){
      //Serial.print("I'm turning left!");
      digitalWrite(motor_left_reverse,HIGH);
      digitalWrite(motor_right_forward,HIGH);
      digitalWrite(motor_left_forward,LOW);
      digitalWrite(motor_right_reverse,LOW);
    } else if (direct == "right"){
      //Serial.print("I'm turning right");
      digitalWrite(motor_left_reverse,  LOW);
      digitalWrite(motor_right_forward,LOW);
      digitalWrite(motor_left_forward,HIGH);
      digitalWrite(motor_right_reverse,HIGH);
     }
     else {
      roverstop();
      lc = 0;
     }
  }
}
// angle 70

void roverstop(){
  Serial.println("Rover stop: END");
  stopping();
  delay(4000);
}

void rightsquare(){
  while(lc<75){
    straightforward();
  }
  //Serial.println("out");
  if (lc >= 75 and count == 0) { //50cm 215
    Serial.println("0");
    stopping();
    delay (1000);
    lc = 0;
    corner(65, "right"); //85
    lc = 0;
    count++;
  }
  
  while(lc<75){
    straightforward();
  }
  
  if (lc >= 75 and count == 1) { //50cm 215
    Serial.println("1");
    stopping();
    delay (1000);
    lc = 0;
    corner(65, "right");//85
    //delay(1000);
    lc = 0;
    count++;
  }
  
  while(lc<75){
    straightforward();
  }
  
  if (lc >= 75 and count == 2) { //50cm 215
    Serial.println("2");
    stopping();
    delay (1000);
    lc = 0;
    corner(65, "right");//85
    //delay(1000);
    lc = 0;
    count++;
  }
  
  while(lc<75){
    straightforward();
  }
  
  if (lc >= 75 and count == 3) { //50cm 215
    Serial.println("3");
    stopping();
    delay (1000);
    
  }
}

void leftsquare(){

  while(lc<75){
    straightforward();
  }
  
  Serial.println("out");
  if (lc >= 75 and leftcount == 0) { //50cm 215
    Serial.println("0");
    stopping();
    
    delay (1000);
    lc = 0;
    corner(65, "left");
    //delay(1000);
    lc = 0;
    leftcount++;
  }
  
  while(lc<75){
    straightforward();
  }
  
  if (lc >= 75 and leftcount == 1) { //50cm 215
    Serial.println("1");
    stopping();
    delay (1000);
    lc = 0;
    corner(65, "left");//40
    //delay(1000);
    lc = 0;
    leftcount++;
  }
  
  while(lc<75){
    straightforward();
  }
  
  if (lc >= 75 and leftcount == 2) { //50cm 215
    Serial.println("2");
    stopping();
    delay (1000);
    lc = 0;
    corner(65, "left");
    //delay(1000);
    lc = 0;
    leftcount++;
  }
  
  while(lc<75){
    straightforward();
  }
  
  
  if (lc >= 75 and leftcount == 3) { //50cm 215
    Serial.println("3");
    stopping();
    
    delay (1000);
    lc = 0;
    corner(65, "right");
    lc = 0;
    leftcount++;
  
  }
  if (leftcount == 4){
    roverstop();
  }

}


