// functions related to movement

#define leftSpeed 50 // left motor speed
#define rightSpeed 50 // right motor speed

char dirToChar(int value) {
  if (value > 0) return 'b';
  else if (value < 0) return 'a';
  return 'o';
}

void moveMotors(int left, int right) {
  motors('1', dirToChar(left), abs(left));
  motors('2', dirToChar(right), abs(right));
}

void halt() {
  moveMotors(0,0);
  delay(100);
}

void forward(int milliseconds) { 
  moveMotors(leftSpeed, rightSpeed); 
  delay(milliseconds);
  halt(); 
}

void reverse(int milliseconds) {
  moveMotors(-leftSpeed, -rightSpeed); 
  delay(milliseconds);
  halt(); 
}

void left(int milliseconds) {
  moveMotors(-leftSpeed, rightSpeed);
  delay(milliseconds);
  halt(); 
}

void right(int milliseconds) {
  moveMotors(leftSpeed, -rightSpeed);
  delay(milliseconds);
  halt(); 
}

