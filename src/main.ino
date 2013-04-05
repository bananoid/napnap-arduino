#include "MemoryFree.h"
#include "NNMainController.h"

NNMainController *mainController;

void setup(){
  Serial.begin(9600);
  Serial.println("--NAPNAP--");

  Serial << "SETUP " << getFreeMemory() << endl;

  mainController = NNMainController::getInstance();
  mainController->begin();

}

void loop(){
  mainController->process();
}
