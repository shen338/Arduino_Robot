#include <SPI.h>
#include <Pixy.h>
#include <Servo.h>
#include <IRremote.h>


#define DEBUG true
#define TIMEOUT 40*1000
#define DELAY_DOOR 30
#define SERVO_CLOSE 100
#define SERVO_OPEN 0
#define SIGNATURE_BALL 1
#define SIGNATURE_CONTAINER 2
#define DEFAULT_BLOB_SIZE 200
#define MIN_BLOB_SIZE 10
#define SPEED 140

//All pins
const int motorL1 = 7;
const int motorL2 = 8;
const int motorLPWM = 6;

const int motorR1 = 12;
const int motorR2 = 13;
const int motorRPWM = 11;

const int switchF = 3;
const int switchR = 4;

const int irFront = 0;
const int irRight = 7;

const int interruptPin = 2;

bool started;

int blob_x;
int blob_y;
int blobSize;
bool foundBlob;
int ballCount;

bool doorClosed;
int trackedBlock;

enum State {
    BALL,
    COLLECT,
    CONTAINER,
    EMPTY,
    HALT
  } state;

enum Dir {
    FORWARD,
    LEFT,
    RIGHT,
    BACKWARD
} dir;


Servo doorservo;
Pixy pixy;
IRsend irsend;

void setup()
{
  
  if(DEBUG) {
    Serial.begin(9600);
    Serial.print("Initializing...\n");
  }
  pixy.init();
  doorservo.attach(10);
  
  pinMode(switchF, OUTPUT);
  pinMode(switchR, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), eStop, FALLING);
  
  foundBlob = false;
  doorClosed = false;
  ballCount = 0;
  trackedBlock = -1;
  state = BALL;
  dir = FORWARD;
  
  closeDoor();
  pushIn();
  stopMove();
  stopPush();

  if(DEBUG)
    Serial.print("Ready\n");
}

void eStop() {
  state = HALT;
}

void loop()
{
  switch(state) {
    case BALL:
      findBall();
      break;

    case HALT:
      stopMove();
      break;
  
    case COLLECT:
      collectBall();
      break;
  
    case CONTAINER:
      findContainer();
      break;
  
    case EMPTY:
      empty();
      break;
  }
}
