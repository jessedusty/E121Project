#include <ArduinoInit.h>  // no space between # and the word include
#include <SendOnlySoftwareSerial.h> 

// Code by Jesse Stevenson 

void setup() {
  // put your setup code here, to run once:

  configArduino();

}

#define green   12
#define yellow  11
#define red     10

#define numBlinks 3
void blink(int pin, int interval, bool endWait) {
  
  for (int i = 0; i < numBlinks; i++) {
    outputHigh(pin);
    pause(interval);
    outputLow(pin);
    pause(!endWait && i == numBlinks - 1? 0 : interval );  
  }
}

void loop() {
  blink(green, 1000, true);
  blink(yellow, 3000, false);
  blink(red, 1000, true); 
}
