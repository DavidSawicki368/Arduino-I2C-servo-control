#include <Servo.h>
#include <Wire.h>

// Roles
bool isJoystickLocal = true;
bool isServoLocal = false;
bool trace = true;

Servo servo1;
int servoI2CAddress = 8;

// Pin Assignments
int xJoy = A0;
// int yJoy = A1;
int servoPin = 9;
int ledPin = 13;

void setup() {
  if (isServoLocal) {
    servo1.attach(servoPin);
  }

  if (isJoystickLocal && isServoLocal) {
    // Both are local no need for i2c.
  } else if (isJoystickLocal && !isServoLocal) {
    // Local joystick, we're i2c master.
    Wire.begin();
  } else {
    Wire.begin(servoI2CAddress);
    Wire.onReceive(remoteJoystick);
  }

  if (trace) {
    Serial.begin(9600);
  }

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // Identify ourselves.
  if (isJoystickLocal) {
    blink(3, 500, 250);
  }
  delay(1000);
  if (isServoLocal) {
    blink(1, 2000, 0);
  }
}

void loop() {
  static int lastJoystickPosition = 0;

  if (isJoystickLocal) {
    int joystickXPosition = localJoystick();
    if (joystickXPosition != lastJoystickPosition) {
      // Only send if joystick has moved.
      setServo(isServoLocal, joystickXPosition);
      lastJoystickPosition = joystickXPosition;

      // Blink LED on each I2C packet.
      blink(1, 200, 100);

      if (trace) {
        String out;
        // out = "\f";
        // out += "\e[?25l"; // ANSI hide cursor.
        out += "x = ";
        out += joystickXPosition;
        Serial.println(out);
      }
    }
  } else {
    // Everything happens in remoteJoystick().
  }
}

int localJoystick() {
  return map(analogRead(xJoy), 0, 1023, 0, 180);
}

void remoteJoystick(int bytes) {
  // Blink LED on each I2C packet.
  blink(1, 200, 100);

  // Collect position value(s) and send to servo.
  while (Wire.available()) {
    int pos = Wire.read();
    setServo(true, pos);
    if (trace) {
      Serial.println(pos);
    }
  }
}

void setServo(bool local, int position) {
  if (local) {
    // Write to servo.
    servo1.write(position);
  } else {
    // Send to remote servo via i2c.
    Wire.beginTransmission(servoI2CAddress);
    Wire.write(position);
    Wire.endTransmission();
  }
}

void blink(int times, int on, int off) {
  for (int i = 0; i < times; i++) {
    digitalWrite(ledPin, HIGH);
    delay(on);
    digitalWrite(ledPin, LOW);
    delay(off);
  }
}
