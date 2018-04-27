// Include the required Wire library for I2C<br>
#include<Wire.h>

int joyVal; // Variable to read the values from the analog pins
int joyX = A0; // Define joystick pins (Analog)


void setup() {
  // Start the I2C Bus as Master
  Wire.begin(); 
  Serial.print("Hello, David!");
}

void loop() {
  // Read the joystick here
  joyVal = analog.read(joyX);
  Wire.beginTransmission(9); // transmit to device #9
  Wire.write(map(joyVal, 0, 1023, 0, 180);        // sends joyVal
  Wire.endTransmission();    // stop transmitting
  delay(15);

  Serial.print (joyVal);  
}

