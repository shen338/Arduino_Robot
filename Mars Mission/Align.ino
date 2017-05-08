void align(int signature){

  track(signature);
  
  int32_t panError = panLoop.m_pos - panLoop.m_centerPos;
  int32_t differential = (panError + (panError * 80)) >> 8;
  int leftSpeed = constrain(0 + differential, -80, 80); //forward + diff
  int rightSpeed = constrain(0 - differential, -80, 80); //forward - diff
  
  if (leftSpeed >= 0){
    digitalWrite(motorL1, HIGH);
    digitalWrite(motorL2, LOW);
    analogWrite(motorLPWM, leftSpeed);
  }
  else if (leftSpeed < 0){
    digitalWrite(motorL1, LOW);
    digitalWrite(motorL2, HIGH);
    analogWrite(motorLPWM, -leftSpeed);
  }
  if (rightSpeed >= 0){
    digitalWrite(motorR1, HIGH);
    digitalWrite(motorR2, LOW);
    analogWrite(motorRPWM, rightSpeed);
  }
  else if (rightSpeed < 0){
    digitalWrite(motorR1, LOW);
    digitalWrite(motorR2, HIGH);
    analogWrite(motorRPWM, -rightSpeed);
  }
}

