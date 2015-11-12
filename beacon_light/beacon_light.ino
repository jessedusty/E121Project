#include <ArduinoInit.h>  // no space between # and the word include
#include <SendOnlySoftwareSerial.h> 
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif


#define leftSpeed 51
#define rightSpeed 50


Adafruit_NeoPixel strip = Adafruit_NeoPixel(5, 5, NEO_GRB + NEO_KHZ800);

int last;


boolean startingFloor; 

void setup() {
  // put your setup code here, to run once:
  configArduino();
  
  Serial.begin(115200);
  while (!Serial) {
    NOP;
  }

  outputHigh(4);
 
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  moveMotors(0, 25); 
  last = getScaledReading(); 

  attachInterrupt(0, bumperPressed, LOW);
  attachInterrupt(1, bumperPressed, LOW);

  startingFloor = floorSensor(); 
}

int getScaledReading() { 
  return map(readADC(3), 20000, 50000, 0, 2550);
}
boolean interuptActive = false; 

void bumperPressed() {
  if (interuptActive) return;
  interuptActive = true; 
  halt();
  pause(50);
  
  bool leftB = !readInput(2);
  bool rightB = !readInput(3);
  
  strip.setPixelColor(1, !leftB ? strip.Color(0,0,0) : strip.Color(0,255,0));
  strip.setPixelColor(3, !rightB ? strip.Color(0,0,0) : strip.Color(0,255,0));

  strip.show();
  
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

  leftB = !readInput(2);
  rightB = !readInput(3);
  strip.setPixelColor(1, !leftB ? strip.Color(0,0,0) : strip.Color(0,255,0));
  strip.setPixelColor(3, !rightB ? strip.Color(0,0,0) : strip.Color(0,255,0));
  strip.show();

  interuptActive = false;
}

int floorSensor() {
    // 41000 - 13000 
    return map(readADC(0), 13000, 41000, 0, 100) > 50;
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("\033[0H\033[0J");
  
  Serial.print("A0: ");
  Serial.println(readADC(0)); 
  
  Serial.print("A1: ");
  Serial.println(readADC(1)); 
  
  Serial.print("A2: ");
  Serial.println(readADC(2));
  
  Serial.print("A3: ");
  Serial.println(readADC(3));
  
  delay(50);


  
  int top = getScaledReading(); 
  
  strip.setPixelColor(2, strip.Color(255-top/10, 0 ,top/10));
  strip.show();

   if (startingFloor == floorSensor()) {
     if (last < top) {
      moveMotors(100,75);    
     } else {
      moveMotors(75,100);
     }
  
    last = top;
   } else {
    halt();
   }
  

}
