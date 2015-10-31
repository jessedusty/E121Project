#include <ArduinoInit.h>  // no space between # and the word include
#include <SendOnlySoftwareSerial.h> 

void setup() {
  // put your setup code here, to run once:
  configArduino();

  Serial.begin(115200);
  
  attachInterrupt(0, bumperPressed, LOW);
  attachInterrupt(1, bumperPressed, LOW);
}

void bumperPressed() {
  halt();
  pause(50);
  
  bool leftB = !readInput(2);
  bool rightB = !readInput(3);
  
  if (leftB && !rightB) {
    moveMotors(0, -100, 200);
  } else if (!leftB && rightB) {
    moveMotors(-100,0, 200);
  } else if (left && right) {
    moveMotors(-100,-100, 50);
    if (random(0,1)) {
      moveMotors(-100, 100, 250); 
    } else {
      moveMotors(100,-100,250);
    }
  } else {
    halt();
    pause(1000);
  }

  // bounce protection
  while (!readInput(2) || !readInput(3))  {
    moveMotors(30,30,30);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  moveMotors(50,50);
  
  pause(10);
}
