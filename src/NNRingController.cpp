#include "NNRingController.h"
#include <Arduino.h>

NNRingController::NNRingController(int pin){
  this->pin = pin;
}
void NNRingController::begin(){
  pinMode(pin,OUTPUT);
}

void NNRingController::process(){
  // digitalWrite(pin,0);
  // delay(1);
  // digitalWrite(pin,1);
  // delay(1);
  digitalWrite(pin,random(0,2));
  delay(2);
}
