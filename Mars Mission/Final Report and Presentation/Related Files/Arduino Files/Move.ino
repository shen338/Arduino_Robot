void left(int PWM) {
  int pin1 = LOW;
  int pin2 = LOW;
  
  if(PWM > 0) {
    pin1 = HIGH;
  } else if(PWM < 0){
    PWM = -PWM;
    pin2 = HIGH;
  }
  PWM = constrain(PWM, 0, 255);
  
  digitalWrite(motorL1, pin1);
  digitalWrite(motorL2, pin2);
  analogWrite(motorLPWM, PWM);
}

void right(int PWM) {
  int pin1 = LOW;
  int pin2 = LOW;
  
  if(PWM > 0) {
    pin1 = HIGH;
  } else if(PWM < 0){
    PWM = -PWM;
    pin2 = HIGH;
  }
  PWM = constrain(PWM, 0, 255);
  
  digitalWrite(motorR1, pin1);
  digitalWrite(motorR2, pin2);
  analogWrite(motorRPWM, PWM);
}

void moveMotor(int leftPWM, int rightPWM) {
  left(leftPWM);
  right(rightPWM);
}


void stopMove() {
  moveMotor(0, 0);
}

void breakMove() {
  digitalWrite(motorL1, LOW);
  digitalWrite(motorL2, LOW);
  analogWrite(motorLPWM, 255);
  
  digitalWrite(motorR1, LOW);
  digitalWrite(motorR2, LOW);
  analogWrite(motorRPWM, 255);

  delay(200);
  stopMove();
}


void FollowBlock(int trackedBlock) {
  int forwardSpeed = 140;
    
  // Steering differential is proportional to the off center value
  int differential = 160 - pixy.blocks[trackedBlock].x;
  
  // Adjust the left and right speeds by the steering differential.
  int leftSpeed = constrain(forwardSpeed - 0.8*differential, -SPEED, SPEED);
  int rightSpeed = constrain(forwardSpeed + 0.8*differential, -SPEED, SPEED);

  moveMotor(leftSpeed, rightSpeed);
}


void ScanForBlocks() {
  static uint32_t lastMove = 0L;
  static uint32_t lastStraight = 0L;
  static int forwardCount = 0;
  
  if (millis() - lastMove > 20) {
    int frontDist = analogRead(irFront);
    int rightDist = analogRead(irRight);
    lastMove = millis();
    

    if(rightDist > 500) {
      dir = LEFT;
    } else {
      if(dir == LEFT) {
        dir = FORWARD;
      } else if(millis() - lastStraight > 2000){
        {
          if(forwardCount < 10) {
            forwardCount++;
            dir = FORWARD;
          }
          else {
            dir = RIGHT;
            forwardCount = 0;
            lastStraight = millis();
          }
        }
      } else{
        dir = RIGHT;
      }
    }
     

    if(frontDist > 500) {
      dir = BACKWARD;
      forwardCount = 0; 
      lastStraight = millis();
    }
    switch(dir) {
      case FORWARD:
        moveMotor(160, 160);
        break;
      case LEFT:
        moveMotor(-100, 100);
        break;
      case RIGHT:
        moveMotor(100, -100);
        break;
      case BACKWARD:
        moveMotor(-200, -200);
        break;
    }
  }
  /*

  static uint32_t lastMove = 0L;
  int leftSpeed = 100;
  int rightSpeed = -100;
  
  if (millis() - lastMove > 20) {
    if(millis() - lastStraight > 3000) {
      lastStraight = millis();
      leftSpeed = 140;
      rightSpeed = 140;
    }
    
    lastMove = millis();

    if(getRightDistance() > 500) {
      //Right obstacle
      leftSpeed = -1;
      rightSpeed = 140;
      delay(100);
    }

    if(getFrontDistance() > 500) {
      //Front obstacle
      leftSpeed = -140;
      rightSpeed = -140;
      lastStraight = millis();
    }
    
    moveMotor(leftSpeed, rightSpeed);
  }
*/
}
