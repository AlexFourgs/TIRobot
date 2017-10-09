#include "Servo.h"

Servo servoPan, servoTilt;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  
  servoPan.attach(6);
  servoTilt.attach(5);
  
}

void loop() {
  if(Serial.available()) {
    char c = Serial.read();
    Serial.println(c);
  }
  
  // put your main code here, to run repeatedly:
  servoPan.write(0);
  //servoTilt.write(180);
  delay(1000);
  servoPan.write(180);
  delay(1000);
 }
