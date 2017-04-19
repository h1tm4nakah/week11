#include <Wire.h>
#include "Platform.h"

#define DRIVER_ENABLE 5
#define DRIVER_STEP 6
#define DRIVER_DIR 7
#define LED 2
#define SERVO_1 9
#define SERVO_2 10
#define THERMISTOR A1

#define MAX_TUBES 18
#define STEPS_PER_TUBE 30

Platform platform(DRIVER_ENABLE,DRIVER_STEP,DRIVER_DIR, MAX_TUBES, STEPS_PER_TUBE);

int tube_number = 0;
int pump_one = 0;
int pump_two;

void setup() {
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  while (Serial.available() > 0) {
    int tube_number = Serial.parseInt();
    int pump_one = Serial.parseInt();
    int pump_two = Serial.parseInt();
    if (Serial.read() == '\n') {
        platform.goTo(tube_number);
        blink_led(1);
        delay(500);
        Wire.beginTransmission(10);  // transmit to pump number 1
        Wire.write(pump_one);       // send the % to flow
        Wire.endTransmission();     // stop transmitting
        blink_led(2);
        delay(500);
        Wire.beginTransmission(20);  // transmit to pump number 2
        Wire.write(pump_two);       // send the % to flow
        Wire.endTransmission();     // stop transmitting
        blink_led(2);
        delay(500);
        Serial.println(1);          // send the ACK back to the computer
    }
  }
}

void blink_led(int numb) {
  for (int i=0; i<numb ; i++)
  {
      digitalWrite(LED, HIGH);
      delay(200);
      digitalWrite(LED, LOW);
      delay(200);
  }
}


