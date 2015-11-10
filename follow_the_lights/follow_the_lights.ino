#include <ArduinoInit.h>  // no space between # and the word include
#include <SendOnlySoftwareSerial.h> 
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif


#define leftSpeed 51
#define rightSpeed 50


Adafruit_NeoPixel strip = Adafruit_NeoPixel(5, 5, NEO_GRB + NEO_KHZ800);

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

  

  int leftVal = map(readADC(1), 0, 50000, 0, 255);
  int rightVal = map(readADC(2), 0, 50000, 0, 255);
  strip.setPixelColor(0, strip.Color(255-leftVal, 0 ,leftVal));
  strip.setPixelColor(4, strip.Color(255-rightVal, 0 ,rightVal));

  if (leftVal < rightVal) {
    moveMotors(25,50);
  } else if (leftVal > rightVal) {
    moveMotors(50,25);
  }
  
  strip.show();
  

}
