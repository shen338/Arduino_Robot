
#include <IRremote.h>

const int RECV_PIN = 5;
const int switchU = 3;
const int switchD = 4;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(switchU, OUTPUT);
  pinMode(switchU, OUTPUT);
  pushDown();
  Serial.println("Ready.");
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    switch(results.value) {
      case 0xaaa:
        pushUp();
        break;
      case 0xbbb:
        pushDown();
        break;
    }
    irrecv.resume(); // Receive the next value
  }
  delay(50);
}

void pushUp() {
  digitalWrite(switchU, HIGH);
  Serial.println("Push up.");
  while(digitalRead(switchU));
  stopPush();
}

void pushDown() {
  digitalWrite(switchD, HIGH);
  Serial.println("Push down");
  while(digitalRead(switchD));
  stopPush();
}

void stopPush() {
  digitalWrite(switchU, LOW);
  digitalWrite(switchD, LOW);
}
