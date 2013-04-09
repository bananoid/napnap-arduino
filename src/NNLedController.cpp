#include "NNLedController.h"
#include <Arduino.h>

#define rPin 9
#define gPin 10
#define bPin 11

NNLedController::NNLedController(){

}
void NNLedController::begin(){
  pinMode(rPin,OUTPUT);
  pinMode(gPin,OUTPUT);
  pinMode(bPin,OUTPUT);
  digitalWrite(rPin,0);
  digitalWrite(gPin,0);
  digitalWrite(bPin,0);
}

void NNLedController::process(){

}

void NNLedController::doAlarmRingSignal(bool on){
  digitalWrite(rPin,on);
  digitalWrite(gPin,on);
  digitalWrite(bPin,on);
}

void NNLedController::doAlarmSetSignal(){
  digitalWrite(rPin,1);
  delay(300);
  digitalWrite(rPin,0);
  digitalWrite(gPin,1);
  delay(300);
  digitalWrite(gPin,0);
  digitalWrite(bPin,1);
  delay(300);
  digitalWrite(bPin,0);
}
