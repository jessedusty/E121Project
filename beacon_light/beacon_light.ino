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

int followDirection = -1; 

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

  findMax(-35,35, 750); 
}

int getScaledReading() { 
  return map(readADC(3), 20000, 50000, 0, 2550);
}

int getUnscaledReading() {
  return readADC(3); 
}


void searchReverse() {
  moveMotors(-75,-75,200);
}

boolean interuptActive = false; 
int interupted = false;

void bumperPressed() {
  if (interuptActive || !(readInput(2) || readInput(3))) return;
  interuptActive = true; 
  interupted += 1; 
  followDirection *= -1;
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
    
    //moveMotors(-100,-100, 50);
    
    moveMotors(100,-100,50);
    
  } else {
    halt();
    //pause(1000);
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

#define maxSearchPeriod 1500

void findMax(int lowSpeed, int highSpeed) {
  findMax(lowSpeed, highSpeed, maxSearchPeriod);
}



void findMax(int lowSpeed, int highSpeed, int searchTime) {
  unsigned long start =  millis();
  moveMotors(highSpeed,lowSpeed);
  int maxMag = getUnscaledReading();
  unsigned int maxDir = 0;
  while (millis() < start + maxSearchPeriod) {
    if (interupted > 3) {
      searchReverse();
      interupted = 0;
      findMax(-25,50, 500);
      return;
    }
    if (maxMag > getUnscaledReading()) {
        maxDir = millis() - start;
        maxMag = getUnscaledReading();
    }
  }
  unsigned long endt = millis();
  halt();
  moveMotors(lowSpeed,highSpeed); 
  pause((endt - start) - maxDir); 
  halt();
}



void trackBeacon() {
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

    int lowVal = 25;
    int highVal = 100;

   if (startingFloor != floorSensor()) {
    strip.setPixelColor(0, strip.Color(255,255,255));
    halt();
   } else if (followDirection == -1) {
    strip.setPixelColor(0, strip.Color(255,0,0));
     if (last > top) {
      moveMotors(highVal,lowVal);    
     } else {
      moveMotors(lowVal,highVal);
     }
     
   } else if (followDirection == 1) {
    strip.setPixelColor(0, strip.Color(0,255,0));
    if (last < top) {
      moveMotors(highVal,lowVal);    
     } else {
      moveMotors(lowVal,highVal);
     }
    
   } else {
    followDirection = 1;
    strip.setPixelColor(0, strip.Color(0,0,255));
   }
   last = top;
   if (interupted > 2) {
      interupted = 0;
      findMax(0,100,100);
  }
}

void beaconFind() {
  if (floorSensor() == startingFloor) {
    if (interupted > 3) {
      interupted = 0;
      searchReverse();
      findMax(-50,50,100);
    }
    moveMotors(100,100);
  } else {
    halt();
  }
  if (!readInput(2) && !readInput(3)) bumperPressed();
}


void pointTowards() {
  findMax(-30,30,2000);
  halt();
  pause(2000);
}
void loop() {

  beaconFind();

  while (1) {
    trackBeacon();
  }

}
