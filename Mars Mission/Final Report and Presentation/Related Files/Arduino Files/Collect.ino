void collectBall() {
  bool found = track(SIGNATURE_BALL);
  
  if(found) {
    FollowBlock(trackedBlock);
    openDoor();
  } else if(blob_y > 190){
      delay(400);
      if(closeDoor()) {
        ballCount++;
        foundBlob = false;
      }
      if(ballCount >= 2) {
        state = CONTAINER;
        if(DEBUG) {
          Serial.println("COLLECT >>> CONTAINER");
        }
      } else {
        state = BALL;
        if(DEBUG) {
          Serial.println("COLLECT >>> BALL");
        }
      }
  }
}


bool openDoor() {
    if(doorClosed) {
      doorservo.write(SERVO_OPEN); //change number here
      
      if(DEBUG)
        Serial.println("Opened door.");

      doorClosed = false;
      return true;
    }
    return false;
}

bool closeDoor() {
    if(!doorClosed) {
      doorservo.write(SERVO_CLOSE); //change number here
      
      if(DEBUG) 
        Serial.println("Closed door.");
        
      doorClosed = true;
      return true;
    }
    return false;
}
