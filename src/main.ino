#include "MemoryFree.h"
#include "NNWebServer.h"

NNWebServer *nnWebServer;

void setup(){
  Serial.begin(115200);
  Serial.println("--NAPNAP--");

  // Serial << "SETUP " << getFreeMemory() << endl;

  nnWebServer = NNWebServer::getInstance();
  nnWebServer->begin();
}

void loop(){
  // Serial << "BEFORE LOOP " << getFreeMemory() << endl;

  nnWebServer->process();

  if(nnWebServer->requestAlarm()){
    Serial << nnWebServer->playTime << endl;
  }

  Serial << "AFTER LOOP " << getFreeMemory() << endl;

}
