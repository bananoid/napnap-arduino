#include "NNMainController.h"
#include <Time.h>


NNMainController::NNMainController(){
  mode = kModeRequest;
}

void NNMainController::begin(){
  nnWebServer = NNWebServer::getInstance();
  nnWebServer->processDelay = 1000;
  nnWebServer->begin();

  sensorController = new SensorController(100);
  sensorController->begin();

  ringController = new NNRingController(8);
  ringController->begin();

  alarmStartTime = 0;
}

void NNMainController::process(){
  switch(mode){
    case kModeRequest:
      doRequest();
      break;
    case kModeRing:
      doRing();
      break;
  };
}

void NNMainController::setMode(int m){
  if(mode == m) return;
  mode = m;
  Serial << "Mode Changed to " << ( mode == kModeRequest ? ">>Request<<" : ">>Ring<<");
}

void NNMainController::doRequest(){
  nnWebServer->process();

  if(isAlarmTime()){
    alarmStartTime = millis();
    setMode(kModeRing);
  }

}

void NNMainController::doRing(){
  sensorController->process();
  if(sensorController->isMoving){
    setMode(kModeRequest);

    unsigned long reactionTime = millis() - alarmStartTime;
    nnWebServer->sendWakeUpData(sensorController->intensity, reactionTime );

    return;
  }
  ringController->process();
}

bool NNMainController::isAlarmTime(){
  unsigned long curTime = now();
  if(nnWebServer->playTime > 0  && curTime >= nnWebServer->playTime){
    nnWebServer->playTime = 0;
    return true;
  }

  Serial << "playTime ::" << nnWebServer->playTime << " now::"<< curTime <<"-----------\r\n" ;
  return false;
}
