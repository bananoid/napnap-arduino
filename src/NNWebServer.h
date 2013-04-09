#include <Arduino.h>
#include <Time.h>
#include <SoftwareSerial.h>
#include <Streaming.h>
// #include <PString.h>
#include <WiFlySerial.h>
#include "MemoryFree.h"

#define ARDUINO_RX_PIN  2
#define ARDUINO_TX_PIN  3

// #define MY_SERVER "napnap.meteor.com"

#define NN_SERVER_URL "192.168.1.68"
#define NN_SERVER_PORT 3000
#define NN_SERVER_SOCKET_URI "/sockjs/websocket"

#define REQUEST_BUFFER_SIZE 100
// #define POST_BUFFER_SIZE 60
#define TEMP_BUFFER_SIZE 60

class NNWebServerDelegate{
public:
  virtual void nnwebServerAlarmSet();
};


class NNWebServer{
private:

  // char bufRequest[REQUEST_BUFFER_SIZE];
  // char bufTemp[TEMP_BUFFER_SIZE];

  unsigned long processTimeOut;
  char* getReqNextValue(char* begin);
public:

  NNWebServer();
  NNWebServerDelegate *delegate;
  WiFlySerial *wifi;

  static NNWebServer* getInstance()
  {
    // The only instance
    // Guaranteed to be lazy initialized
    // Guaranteed that it will be destroyed correctly
    static NNWebServer* instance = new NNWebServer();
    return instance;
  }

  unsigned long int processDelay;

  void begin();
  void connect();
  bool process();

  bool requestAlarm();
  void sendWakeUpData(int intensity, unsigned long int reactionTime);

  void getHttpBody(char *buffer, int timeOut);

  char *alarmId; // 7LybKfTggdpJuHFJH
  unsigned long playTime;
};

