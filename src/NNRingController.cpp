#include "NNRingController.h"
#include <Arduino.h>

NNRingController::NNRingController(int pin){
  this->pin = pin;
}
void NNRingController::begin(){
  pinMode(pin,OUTPUT);
  timeOut = 0;
}

void NNRingController::process(){
  // digitalWrite(pin,0);
  // delay(1);
  // digitalWrite(pin,1);
  // delay(1);
  // digitalWrite(pin,random(0,2));

  if( millis() < timeOut ) return;
  timeOut = millis() + 50;

  int frq = random(0,1500);
  tone(pin, frq, 30);
}
