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
  beacon_setup(); 
  beacon_light();
  target_setup();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if (startingFloor == floorSensor()) {
    halt();
    moveMotors(-100,-100,1000);
    left(250);
    moveMotors(100,100,500); 
  }

  target_light();  
}
