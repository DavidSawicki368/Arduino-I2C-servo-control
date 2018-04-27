#include <Servo.h> // add the servo library
#include<Wire.h> // Include the required Wire library for I2C<br>
// Definee the servos
Servo servo1;

// Variable to read the values from the analog pins
int joyVal;

void setup() {
  // Attach servos on pins 3, 5
  servo1.attach(3);
  // Start the I2C Bus as Slave on address 9
  Wire.begin(9);
  // Attach a function to trigger when something is received.
  Wire.onReceive(receiveEvent);
}
void receiveEvent(int bytes) {
  joyVal = Wire.read();    // read one character from the I2C
  joyVal = map (joyVal, 0, 1023, 0, 180); // Servo value between 0-180
  servo1.write(joyVal); // Set the servo's position according to the joystick value
  delay(15);
}

void loop() {

}



