#include "NNWebServer.h"
#include "wifiCommands.h"
#include "Credentials.h"
#include "MemoryFree.h"
#include <aJSON.h>

time_t GetSyncTime() {
  NNWebServer *nnWebServer = NNWebServer::getInstance();
  WiFlySerial *wifi = nnWebServer->wifi;
  long timeOffset = (long) (2 * 60 * 60);
  unsigned long t =  wifi->getTime();
  t += timeOffset;
  time_t tCurrent = (time_t) t;
  wifi->exitCommandMode();
  // Serial << "TIME :: " << t << endl;
  return tCurrent;
}

NNWebServer::NNWebServer(){

  // Serial << "before wifi new memory free " << getFreeMemory() << endl;

  wifi = new WiFlySerial(ARDUINO_RX_PIN ,ARDUINO_TX_PIN);

  // Serial << "after wifi new memory free " << getFreeMemory() << endl;


  // wifi->setDebugChannel(&Serial);
}

void NNWebServer::begin(){
  wifi->begin();
  wifi->setAuthMode( WIFLY_AUTH_WPA2_PSK);
  wifi->setJoinMode(  WIFLY_JOIN_AUTO );
  wifi->setDHCPMode( WIFLY_DHCP_ON );

  connect();

  char bufRequest[REQUEST_BUFFER_SIZE];
  char bufTemp[TEMP_BUFFER_SIZE];

  Serial << F("DateTime:") << year() << "-" << month() << "-" << day() << " " << hour() << ":" << minute() << ":" << second() << F(" UTC+1") << " ---> TIME ::" << now() << endl;

  Serial << GetBuffer_P(IDX_WT_MSG_WIFI,bufTemp,TEMP_BUFFER_SIZE) << endl
    << F("IP: ") << wifi->getIP(bufRequest, REQUEST_BUFFER_SIZE) << endl
    << F("Netmask: ") << wifi->getNetMask(bufRequest, REQUEST_BUFFER_SIZE) << endl
    << F("Gateway: ") << wifi->getGateway(bufRequest, REQUEST_BUFFER_SIZE) << endl
    << F("DNS: ") << wifi->getDNS(bufRequest, REQUEST_BUFFER_SIZE) << endl
    << F("RSSI: ") << wifi->getRSSI(bufRequest, REQUEST_BUFFER_SIZE) << endl
    << F("battery: ") <<  wifi->getBattery(bufRequest, REQUEST_BUFFER_SIZE) << endl;

}

void NNWebServer::connect(){
  char bufRequest[REQUEST_BUFFER_SIZE];
  char bufTemp[TEMP_BUFFER_SIZE];

  wifi->SendCommand(GetBuffer_P(IDX_WT_SETUP_01,bufTemp,TEMP_BUFFER_SIZE), ">",bufRequest, REQUEST_BUFFER_SIZE);
  wifi->setDHCPMode(WIFLY_DHCP_CACHE );
  wifi->SendCommand(GetBuffer_P(IDX_WT_SETUP_02,bufTemp,TEMP_BUFFER_SIZE),">",bufRequest, REQUEST_BUFFER_SIZE);

  wifi->leave();

  wifi->setPassphrase(passphrase);
  wifi->join(ssid);

  wifi->setNTP(ntp_server);
  wifi->setNTP_Update_Frequency(" 15");

  for (int i = 0; i< 7 ; i++) {
    wifi->SendCommand(GetBuffer_P(IDX_WT_SETUP_01 + i,bufTemp,TEMP_BUFFER_SIZE),">",bufRequest, REQUEST_BUFFER_SIZE);
  }
  wifi->getDeviceStatus();

  setSyncProvider( GetSyncTime );

  wifi->setRemotePort(NN_SERVER_PORT);
}

void NNWebServer::process(){
  if(! wifi->isAssociated() ) {
    connect();
  }
}

bool NNWebServer::requestAlarm(){
  // Serial << "memory free 1 " << getFreeMemory() << endl;

  // char bufRequest[REQUEST_BUFFER_SIZE];
  // PString strRequest(bufRequest, REQUEST_BUFFER_SIZE);
  // strRequest
  //   << F("GET ") << "/api/alarms?current=true"
  //   << F(" HTTP/1.1") << "\n"
  //   << F("Host: ") << NN_SERVER_URL << "\n"
  //   << F("Connection: close") << "\n"
  //   << "\n\n";

  wifi->setRemotePort(NN_SERVER_PORT);
  if (wifi->openConnection( NN_SERVER_URL ) ) {

    // Serial << strRequest;

    // Serial << "memory free 2 " << getFreeMemory() << endl;
    // wifi->print(strRequest);
    wifi->println("GET /api/alarms?current=true HTTP/1.1");
    wifi->print("Host: "); wifi->println(NN_SERVER_URL);
    wifi->println("Connection: close");
    wifi->print("\n\n");

    // delete bufRequest;
    // delete strRequest;
    // Serial << "memory free 3 " << getFreeMemory() << endl;

    char jsonBuffer[200];

    getHttpBody(jsonBuffer, 4000);
    wifi->closeConnection();

    Serial << "BODY ::\r\n" << jsonBuffer << "\r\n-----------\r\n" ;

    // //JSON PARSING
    aJsonObject* root = aJson.parse(jsonBuffer);
    aJsonObject* alarmObj = aJson.getArrayItem(root, 0);
    if(!alarmObj) return false;
    aJsonObject* playTimeObj = aJson.getObjectItem(alarmObj, "loadTime");
    playTime = playTimeObj->valueint;
    aJson.deleteItem(root);


  } else {
    // Failed to open connection
    char bufTemp[TEMP_BUFFER_SIZE];
    Serial << GetBuffer_P(IDX_WT_MSG_FAIL_OPEN,bufTemp,TEMP_BUFFER_SIZE) << NN_SERVER_URL << endl;
    return false;
  }

  return true;
}

void NNWebServer::getHttpBody(char *buffer, int timeOut){
  char *jbp = buffer;
  char r;
  bool messageBegin = false;
  // Show server response
  unsigned long longTimeOut = millis() + timeOut;

  while ( longTimeOut > millis() && wifi->isConnectionOpen() ) {
    if ( wifi->available() > 0 ) {
      *jbp = wifi->read();

      if(!messageBegin){

        if( *(jbp-3) == 13 && *(jbp-2) == 10 && *(jbp-1) == 13 && *(jbp) == 10 ){

          messageBegin = true;
          jbp = buffer;

        }else{
          // Serial << *jbp;
          // Serial << *jbp << "::" << (int)*jbp << "==" << (int)'\n' << " " << (*jbp == '\n' ? "true" : "false") << endl;
          jbp++;
        }

        continue;
      }

      // Serial << *jbp << "::" << (int)*jbp << "==" << (int)'\n' << " " << (*jbp == '\n' ? "true" : "false") << endl;

      if( *(jbp-3) == '*' && *(jbp-2) == 'C' && *(jbp-1) == 'L' && *(jbp) == 'O' ){
        *(jbp-3) = 0;
        break;
      }

      // Serial << *jbp;
      jbp++;

    }
  }
}

