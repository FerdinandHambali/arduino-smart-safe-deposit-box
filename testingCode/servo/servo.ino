#include <Servo.h>
Servo doorServo;
#define doorServoPin 12

int pos = 0;
void setup() {
  doorServo.attach(doorServoPin);
}

void loop() {
  for (pos = 0; pos <= 180; pos += 5) {
    doorServo.write(pos);
    delay(15);
  }
  for (pos = 180; pos >= 0; pos -=5){
    doorServo.write(pos);
    delay(15);
  }
}
