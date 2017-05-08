bool track(int signature) {
  uint16_t blocks;
  blocks = pixy.getBlocks();
  if (blocks){
    trackedBlock = TrackBlock(blocks, signature);
    
    if(trackedBlock == -1) {
      return false;
    }
      
    blobSize = pixy.blocks[trackedBlock].width * pixy.blocks[trackedBlock].height;
    blob_x = pixy.blocks[trackedBlock].x;
    blob_y = pixy.blocks[trackedBlock].y;
   
    if(blobSize > MIN_BLOB_SIZE) {
      return true;
    }
  }
  
  return false;
}


int TrackBlock(int blockCount, int targetSignature) {
  int trackedBlock = -1;
  long maxblobSize = -1;
  
  for (int i = 0; i < blockCount; i++) {
    if (pixy.blocks[i].signature == targetSignature) {
      long newblobSize = pixy.blocks[i].height * pixy.blocks[i].width;
      if (newblobSize > maxblobSize){
        trackedBlock = i;
        maxblobSize = newblobSize; 
      }
    }
  }

  return trackedBlock;
}

