#include "NNWebServer.h"
#include "SensorController.h"

class NNMainController{
private:
  void doRequest();
  void doRing();

public:
  static NNMainController* getInstance()
  {
    // The only instance
    // Guaranteed to be lazy initialized
    // Guaranteed that it will be destroyed correctly
    static NNMainController* instance = new NNMainController();
    return instance;
  }
  NNMainController();

  NNWebServer *nnWebServer;
  SensorController *sensorController;

  static const int kModeRequest = 0;
  static const int kModeRing = 1;
  int mode;

  void begin();
  void process();

  bool isAlarmTime();
  void setMode(int m);
};
