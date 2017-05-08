void findBall() {
    bool found = track(SIGNATURE_BALL);
    
    if(found) {
      if(!foundBlob)
        breakMove();
      foundBlob = true;
      
      FollowBlock(trackedBlock);
       
      if( blob_y > 100 ) {
        state = COLLECT;
        if(DEBUG)
          Serial.println("BALL >>> COLLECT"); 
      }  
    } else if(!foundBlob){
      //search for the ball
      if(DEBUG)
        Serial.println("Searching balls");
      ScanForBlocks();
    }
}
