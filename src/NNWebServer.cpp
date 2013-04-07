#include "NNWebServer.h"
#include "wifiCommands.h"
#include "Credentials.h"
#include "MemoryFree.h"
// #include <aJSON.h>
#include <PString.h>
#include <stdlib.h>

time_t GetSyncTime() {
  NNWebServer *nnWebServer = NNWebServer::getInstance();
  WiFlySerial *wifi = nnWebServer->wifi;
  long timeOffset = (long) (2 * 60 * 60);
  unsigned long t =  wifi->getTime();
  // t += timeOffset;
  time_t tCurrent = (time_t) t;
  wifi->exitCommandMode();
  // Serial << "TIME :: " << t << endl;
  return tCurrent;
}

NNWebServer::NNWebServer(){

  // Serial << "before wifi new memory free " << getFreeMemory() << endl;

  wifi = new WiFlySerial(ARDUINO_RX_PIN ,ARDUINO_TX_PIN);

  processDelay = 1000000;
  processTimeOut = 0;

  alarmId = (char *)malloc( 18 * sizeof(char) );
  playTime = 0;

}

void NNWebServer::begin(){
  wifi->begin();
  wifi->setAuthMode( WIFLY_AUTH_WPA2_PSK);
  wifi->setJoinMode(  WIFLY_JOIN_AUTO );
  wifi->setDHCPMode( WIFLY_DHCP_ON );

  connect();

  char bufRequest[REQUEST_BUFFER_SIZE];
  char bufTemp[TEMP_BUFFER_SIZE];

  // Serial << F("DateTime:") << year() << "-" << month() << "-" << day() << " " << hour() << ":" << minute() << ":" << second() << F(" UTC+1") << " ---> TIME ::" << now() << endl;

  // Serial << GetBuffer_P(IDX_WT_MSG_WIFI,bufTemp,TEMP_BUFFER_SIZE) << endl
  //   << F("IP: ") << wifi->getIP(bufRequest, REQUEST_BUFFER_SIZE) << endl
  //   << F("Netmask: ") << wifi->getNetMask(bufRequest, REQUEST_BUFFER_SIZE) << endl
  //   << F("Gateway: ") << wifi->getGateway(bufRequest, REQUEST_BUFFER_SIZE) << endl
  //   << F("DNS: ") << wifi->getDNS(bufRequest, REQUEST_BUFFER_SIZE) << endl
  //   << F("RSSI: ") << wifi->getRSSI(bufRequest, REQUEST_BUFFER_SIZE) << endl
  //   << F("battery: ") <<  wifi->getBattery(bufRequest, REQUEST_BUFFER_SIZE) << endl;

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

bool NNWebServer::process(){
  if(! wifi->isAssociated() ) {
    connect();
  }

  if(millis() < processTimeOut) return false;

  processTimeOut = millis() + processDelay;

  // Serial << "Process WebServer" << endl;

  if(requestAlarm()){
    Serial << playTime << endl;
  }

  return true;
}

char* NNWebServer::getReqNextValue(char* begin){
  char *p = begin;

  while( *p ){
    if(*(p-1) == 13 && *(p) == 10){
      *(p-1) = 0;
      return (p+1);
    }
    p++;
  }

  return p-1;
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
  delay(200);
  wifi->setRemotePort(NN_SERVER_PORT);
  if (wifi->openConnection( NN_SERVER_URL ) ) {

    // Serial << strRequest;

    // Serial << "memory free 2 " << getFreeMemory() << endl;
    // wifi->print(strRequest);
    wifi->println("GET /api/alarms/next HTTP/1.1");
    wifi->print("Host: "); wifi->println(NN_SERVER_URL);
    wifi->println("Connection: close");
    wifi->print("\n\n");

    // delete bufRequest;
    // delete strRequest;
    // Serial << "memory free 3 " << getFreeMemory() << endl;

    char body[200];

    getHttpBody(body, 4000);
    wifi->closeConnection();

    // char *jbp = body;
    // while(*jbp){
    //   Serial << *jbp << "::" << (int)*jbp << endl;
    //   jbp++;
    // }

    char *id;
    char *t;
    id = getReqNextValue(body);
    t = getReqNextValue(id);
    getReqNextValue(t);

    strcpy(alarmId, id);
    playTime = strtoul(t,NULL,0);

    // Serial << "id >>" << id << "<< \r\n";
    // Serial << "t >>" << t << "<< \r\n";
    // Serial << "t >>" << playTime << "<< \r\n";

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

void NNWebServer::sendWakeUpData(int intensity, unsigned long int reactionTime){
  // Serial << "sendWakeUpData --> intensity :: " << intensity << " - reactionTime :: " << reactionTime << "\r\n";
  wifi->setRemotePort(NN_SERVER_PORT);
  if (wifi->openConnection( NN_SERVER_URL ) ) {

    char bufRequest[32];
    PString body(bufRequest, REQUEST_BUFFER_SIZE);
    body << "{\"int\":" << intensity << ",\"rt\":"<< reactionTime << "}";

    wifi->print("PUT /api/alarms/"); wifi->print( alarmId ); wifi->print(" HTTP/1.1\r\n");
    wifi->print("Host: "); wifi->print(NN_SERVER_URL); wifi->print("\r\n");
    wifi->print("Content-Type: application/xml\r\n");
    wifi->print("Content-Length: "); wifi->print(body.length()); wifi->print("\r\n");
    wifi->print("Cache-Control: no-cache\r\n");
    wifi->print("Connection: keep-alive\r\n\r\n");

    wifi->print(body);

  }
}


