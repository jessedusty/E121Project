#include <ArduinoInit.h>  // no space between # and the word include
#include <SendOnlySoftwareSerial.h> 

void doTheDance();

void setup() {
  // put your setup code here, to run once:
  configArduino();
  
  doTheDance();
}

// ** movement functions defined in movement file **

int feetToTime(int feet) {
  return 1400 * feet; 
}

void doTheDance() {
  forward(feetToTime(4));
  delay(2000);
  reverse(feetToTime(2));
  delay(2000); 
  right(5000);
  delay(2000);
  left(5000);
}

void loop() {
  
}
