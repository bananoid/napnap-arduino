#include "MemoryFree.h"
#include "NNWebServer.h"

NNWebServer *nnWebServer = NNWebServer::getInstance();

void setup(){
  Serial.begin(115200);
  Serial.println("--NAPNAP--");

  Serial.print("Free Memory = ");
  Serial.println(getFreeMemory());

  nnWebServer->begin();
}

void loop(){
  nnWebServer->process();
  nnWebServer->requestAlarm();
}
