int motor1 = 7;
int motor2 = 8;
int motorEnA = 9;

const int FOR = 100;
const int REV = 101;
char state;

void setup() {
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(motorEnA, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  state = Serial.read();
  switch(state){
    case 'q':
    digitalWrite(motor1, HIGH);
    digitalWrite(motor2, LOW);
    analogWrite(motorEnA, 255);
    break;

    case 'e':
    digitalWrite(motor1, LOW);
    digitalWrite(motor2, HIGH);
    analogWrite(motorEnA, 255);
    break;

    case 'w':
    digitalWrite(motor1, LOW);
    digitalWrite(motor2, LOW);
    break;
  }


}
