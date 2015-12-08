void target_setup() {
  // put your setup code here, to run once:
  strip.show(); // Initialize all pixels to 'off' 
}

void target_light() {
  int leftVal = map(readADC(1), 0, 50000, 0, 255);
  int rightVal = map(readADC(2), 0, 50000, 0, 255);
  strip.setPixelColor(0, strip.Color(255-leftVal, 0 ,leftVal));
  strip.setPixelColor(4, strip.Color(255-rightVal, 0 ,rightVal));

  if (leftVal < rightVal) {
    moveMotors(50,75);
  } else if (leftVal > rightVal) {
    moveMotors(75,50);
  }
  
  strip.show();
}

