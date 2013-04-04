#include "MemoryFree.h"
#include "NNWebServer.h"
#include "SensorController.h"

NNWebServer *nnWebServer;
SensorController *sensorController;

void setup(){
  Serial.begin(9600);
  Serial.println("--NAPNAP--");

  Serial << "SETUP " << getFreeMemory() << endl;

  nnWebServer = NNWebServer::getInstance();
  nnWebServer->processDelay = 15000;
  nnWebServer->begin();

  sensorController = new SensorController(100);
  sensorController->begin();

}

void loop(){
  // Serial << "BEFORE LOOP " << getFreeMemory() << endl;

  nnWebServer->process();



  Serial << "AFTER LOOP " << getFreeMemory() << endl;

  sensorController->process();

}
