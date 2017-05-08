void findContainer() {
  bool found = track(SIGNATURE_CONTAINER);

  if(found){
    if(!foundBlob) {
      breakMove();
      openContainer();
      openDoor();
    }
    foundBlob = true;
          
    FollowBlock(trackedBlock);
    Serial.println(blob_y);
    if( blob_y > 100 ) {
      state = EMPTY;
      if(DEBUG)
        Serial.println("CONTAINER->EMPTY");
    }
  } else if(!foundBlob) {
      ScanForBlocks();
  }
}

void openContainer() {
  Serial.println("Opened container.");
  for (int i = 0; i < 50; i++) {
    irsend.sendSony(0xaaa,12);
    delay(40);
  }
}

void closeContainer() {
  Serial.println("Closed container.");
  for (int i = 0; i < 5; i++) {
    irsend.sendSony(0xbbb,12);
    delay(40);
  } 
}
