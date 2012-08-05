/*
  Example for simple calculator with version
  
  https://github.com/threez/SCProtocol
*/

#include <SCProtocol.h>

SCProtocol scProtocol = SCProtocol();

void checkCallback(char* data) {
  Serial.println("OK AwesomeApp Version: 0.0.1");
}

void addTwo(char* data) {
  short a = data[0] - '0';
  short b = data[1] - '0'; 
  Serial.print("OK ");
  Serial.println(a + b);
}

void setup() {
  Serial.begin(9600);
  scProtocol.attach('C', checkCallback, 0);
  scProtocol.attach('+', addTwo, 2);
}

void loop() {
  while(Serial.available()) scProtocol.process(Serial.read());
}
