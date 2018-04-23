// Include the required Wire library for I2C<br>
#include<Wire.h>

int joyVal; // Variable to read the values from the analog pins
int joyX = A0; // Define joystick pins (Analog)


void setup() {
  // Start the I2C Bus as Master
  Wire.begin(); 

}

void loop() {

  
  
  Wire.beginTransmission(9); // transmit to device #9
  Wire.write(joyX);        // sends joyVal
  Wire.endTransmission();    // stop transmitting
  delay(15);

Serial.print (joyX);
  
}

