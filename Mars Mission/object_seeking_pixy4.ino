#include <SPI.h>
#include <Pixy.h>
#include <Servo.h>
//#include <ZumoMotors.h>
#define X_CENTER 160L
#define Y_CENTER 100L
#define RCS_MIN_POS 0L
#define RCS_MAX_POS 1000L
#define RCS_CENTER_POS ((RCS_MAX_POS-RCS_MIN_POS)/2)

const int motorL1 = 7;
const int motorL2 = 8;
const int motorLPWM = 6;

const int motorR1 = 12;
const int motorR2 = 13;
const int motorRPWM = 11;

const int motorP1 = 3;
const int motorP2 = 4;
const int motorPPWM = 2;
const int switchf = 40;
const int switchr = 41;

const int TRACK = 100;
const int COLLECT = 101;
const int CONTAINER = 102;
const int PUSHING = 103;

int state = TRACK;

const int PUSHF = 110;
const int PUSHR = 111;
const int PUSHS = 112;
int PUSH = PUSHF;

int ball = 0;

Servo doorservo;

//---------------------------------------
// Servo Loop Class
// A Proportional/Derivative feedback loop for pan/tilt servo tracking of blocks.
// (Based on Pixy CMUcam5 example code) //---------------------------------------
class ServoLoop
{ public:
ServoLoop(int32_t proportionalGain, int32_t derivativeGain);
void update(int32_t error);
int32_t m_pos;
int32_t m_prevError; 
int32_t m_proportionalGain; 
int32_t m_derivativeGain;
};

// ServoLoop Constructor
ServoLoop::ServoLoop(int32_t proportionalGain, int32_t derivativeGain) {
m_pos = RCS_CENTER_POS;
m_proportionalGain = proportionalGain;
m_derivativeGain = derivativeGain; 
m_prevError = 0x80000000L;
}
// ServoLoop Update
// Calculates new output based on the measured error and the current state.
void ServoLoop::update(int32_t error)
{
long int velocity;
char buf[32];
if (m_prevError!=0x80000000) {
  velocity = (error*m_proportionalGain + (error - m_prevError)*m_derivativeGain)>>10;
  m_pos += velocity;
  if (m_pos>RCS_MAX_POS) {
    m_pos = RCS_MAX_POS; 
  }
  else if (m_pos<RCS_MIN_POS) {
    m_pos = RCS_MIN_POS; 
  }
}
m_prevError = error; 
}
// End Servo Loop Class //---------------------------------------
Pixy pixy; // Declare the camera object
ServoLoop panLoop(-200, -200); // Servo loop for pan 
ServoLoop tiltLoop(-150, -200); // Servo loop for tilt

//ZumoMotors motors; // declare the motors on the zumo
//---------------------------------------
// Setup - runs once at startup 
//--------------------------------------- 

void setup()
{
Serial.begin(9600);
Serial.print("Starting...\n");
pixy.init();
doorservo.attach(10);
pinMode(switchf, INPUT_PULLUP);
pinMode(switchr, INPUT_PULLUP);
}

uint32_t lastBlockTime = 0;
//---------------------------------------
// Main loop - runs continuously after setup //---------------------------------------
void loop()
{
switch(state){
  
  case TRACK:
  uint16_t blocks;
  blocks = pixy.getBlocks();
  // If we have blocks in sight, track and follow them 
  if (blocks){
    int trackedBlock = TrackBlock(blocks,1);
    FollowBlock(trackedBlock);
    lastBlockTime = millis();
    
    if(pixy.blocks[trackedBlock].width * pixy.blocks[trackedBlock].height > 300){ //next state
      state = COLLECT;
    }
  }
  else if(millis() - lastBlockTime > 100) {
    //motors.setLeftSpeed(0); //******
    //motors.setRightSpeed(0);
    digitalWrite(motorL1, HIGH);
    digitalWrite(motorL2, LOW);
    analogWrite(motorLPWM, 0);

    digitalWrite(motorR1, HIGH);
    digitalWrite(motorR2, LOW);
    analogWrite(motorRPWM, 0);
    ScanForBlocks();
  } 

  else if(millis() > 42000){ //no time state
    state = CONTAINER;
  }
  break;

  case COLLECT:
  BallCollecting();
  ball++;

  if (ball == 3){
    state = CONTAINER;
  }
  else if (ball < 3){
    state = TRACK;
  }
  break;

  case CONTAINER: //TrackBlock(blocks, 2)

  break;

  case PUSHING:
  BallPushing();
  break;
}
}

int oldX, oldY, oldSignature;
//---------------------------------------
// Track blocks via the Pixy pan/tilt mech
// (based in part on Pixy CMUcam5 pantilt example) //---------------------------------------
int TrackBlock(int blockCount, int target)
{
int trackedBlock = 0;
long maxSize = 0;

Serial.print("blocks =");
Serial.println(blockCount);

for (int i = 0; i < blockCount; i++) {
  if (pixy.blocks[i].signature == target) {
    long newSize = pixy.blocks[i].height * pixy.blocks[i].width;
    if (newSize > maxSize){
      trackedBlock = i;
      maxSize = newSize; 
    }
  }
}

int32_t panError = X_CENTER - pixy.blocks[trackedBlock].x; 
int32_t tiltError = pixy.blocks[trackedBlock].y - Y_CENTER;

panLoop.update(panError);
tiltLoop.update(tiltError);

pixy.setServos(panLoop.m_pos, tiltLoop.m_pos);

oldX = pixy.blocks[trackedBlock].x;
oldY = pixy.blocks[trackedBlock].y;
//oldSignature = pixy.blocks[trackedBlock].signature;
return trackedBlock;
}

//---------------------------------------
// Follow blocks via the Zumo robot drive //
// This code makes the robot base turn
// and move to follow the pan/tilt tracking
// of the head. 
//--------------------------------------- 
int32_t size = 400;
void FollowBlock(int trackedBlock) {
int32_t followError = panLoop.m_pos - RCS_CENTER_POS; // How far off-center are we looking now?
// Size is the area of the object.
// We keep a running average of the last 8.
size += pixy.blocks[trackedBlock].width * pixy.blocks[trackedBlock].height; 
size -= size >> 3;

// Forward speed decreases as we approach the object (size is larger) 
int forwardSpeed = constrain(200 - (size/256), -100, 200);

// Steering differential is proportional to the error times the forward speed 
int32_t differential = (followError + (followError * forwardSpeed)) >> 8;
differential /= 2;

// Adjust the left and right speeds by the steering differential.
int leftSpeed = constrain(forwardSpeed + differential, -180, 180); //forward + diff
int rightSpeed = constrain(forwardSpeed - differential, -180, 180); //forward - diff

// And set the motor speeds 
//motors.setLeftSpeed(leftSpeed); //******
//motors.setRightSpeed(rightSpeed);
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

//---------------------------------------
// Random search for blocks
//
// This code pans back and forth at random until a block is detected //---------------------------------------
int scanIncrement = (RCS_MAX_POS - RCS_MIN_POS) / 150;
uint32_t lastMove = 0;

void ScanForBlocks() {
if (millis() - lastMove > 20) {
  lastMove = millis();
  panLoop.m_pos += scanIncrement;
    if ((panLoop.m_pos >= RCS_MAX_POS)||(panLoop.m_pos <= RCS_MIN_POS)) {
      tiltLoop.m_pos = random(RCS_MAX_POS * 0.5, RCS_MAX_POS); 
      scanIncrement = -scanIncrement;
      /*
        if (scanIncrement < 0){
            //motors.setLeftSpeed(-250); //*****
            //motors.setRightSpeed(250);
            digitalWrite(motorL1, LOW);
            digitalWrite(motorL2, HIGH);
            analogWrite(motorLPWM, 150); 

            digitalWrite(motorR1, HIGH);
            digitalWrite(motorR2, LOW);
            analogWrite(motorRPWM, 150);
           }
        else {
            //motors.setLeftSpeed(+180);
            //motors.setRightSpeed(-180); 
            digitalWrite(motorL1, HIGH);
            digitalWrite(motorL2, LOW);
            analogWrite(motorLPWM, 100);

            digitalWrite(motorR1, LOW);
            digitalWrite(motorR2, HIGH);
            analogWrite(motorRPWM, 100);
            }
      delay(random(250, 500)); 
      */
      }
  pixy.setServos(panLoop.m_pos, tiltLoop.m_pos);
  }
}

void BallCollecting(){
  doorservo.write(90); //open door with servo rotating 90 deg
  delay(10);
  digitalWrite(motorL1, HIGH); //forward to eat the ball
  digitalWrite(motorL2, LOW);
  analogWrite(motorLPWM, 255);
  digitalWrite(motorR1, HIGH);
  digitalWrite(motorR2, LOW);
  analogWrite(motorRPWM, 255);
  delay(700);
  doorservo.write(0); //close door the ensure the ball stay inside

  ball++;
}

void BallPushing(){
  doorservo.write(90); //open door with servo rotating 90 deg
  delay(200);
  switch(PUSH){
    case PUSHF:
    digitalWrite(motorP1, HIGH);
    digitalWrite(motorP2, LOW);
    analogWrite(motorPPWM, 255);

    if (digitalRead(switchf == LOW)){
      PUSH = PUSHR;
      delay(20);
    }
    break;

    case PUSHR:
    digitalWrite(motorP1, LOW);
    digitalWrite(motorP2, HIGH);
    analogWrite(motorPPWM, 255);

    if (digitalRead(switchr == LOW)){
      PUSH = PUSHS;
      delay(20);
    }
    break;

    case PUSHS:
    digitalWrite(motorP1, LOW);
    digitalWrite(motorP2, LOW);
    break;
  }
}

