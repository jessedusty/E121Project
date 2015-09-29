#include <ArduinoInit.h>  // no space between # and the word include
#include <SendOnlySoftwareSerial.h> 


#define leftSpeed 51
#define rightSpeed 50


void setup() {
  // put your setup code here, to run once:
  configArduino();


  // b forward, a reverse 
  // motor 1 Left, motor 2 Right
  

  motors('1', 'b', leftSpeed);
  motors('2', 'b', rightSpeed);

  delay(3000);

  motors('1', 'o', leftSpeed);
  motors('2', 'o', rightSpeed);
}


void loop() {
  // put your main code here, to run repeatedly:


}
