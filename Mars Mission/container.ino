int motor_for = 7;
int motor_rev = 8;
int motorEn = 9;
int button = 6;
//int LED = 6;
const int state1 = 14;
const int state2 = 15;
const int state3 = 16;
const int idle = 20;
int state = idle;
//int prevst = 0;



void setup() {

  pinMode(motorEn, OUTPUT);
  pinMode(button, INPUT);
  pinMode(motor_for,OUTPUT);
  pinMode(motor_rev,OUTPUT);
  //pinMode(LED, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  
int A = digitalRead(button);

switch (state)
{
  case idle:
  digitalWrite(motorEn, LOW);
  digitalWrite(motor_for, LOW);
  digitalWrite(motor_rev, LOW);
  
  if (A==HIGH){
    state = state1;
  }
  break;

  case state1:
  digitalWrite(motorEn, HIGH);
  digitalWrite(motor_for, HIGH);
  digitalWrite(motor_rev, LOW);
  delay(5000);
  state = state2;
  break;

  case state2:
  digitalWrite(motorEn, LOW);
  digitalWrite(motor_for, LOW);
  digitalWrite(motor_rev, LOW);
  
  if (A==LOW){
    state = state3;
  }
  break;

  case state3:
  digitalWrite(motorEn, HIGH);
  digitalWrite(motor_for, LOW);
  digitalWrite(motor_rev, HIGH);
  delay(5000);
  state = idle;
  break;
  }
}
