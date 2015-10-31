// functions related to movement

#define leftSpeed 75 // left motor speed
#define rightSpeed 75 // right motor speed

char dirToChar(int value) {
  if (value > 0) return 'b';
  else if (value < 0) return 'a';
  return 'o';
}

void moveMotors(int left, int right) {
  if (left == 0) motors('1', 'o', 100);
  if (right == 0) motors('2', 'o', 100);
  
  motors('1', dirToChar(left), abs(left));
  motors('2', dirToChar(right), abs(right));
}

void moveMotors(int left, int right, int milliseconds) {
  moveMotors(left, right);
  pause(milliseconds);
  halt();
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

