prog_char s_WT_SETUP_00[] PROGMEM = "nist1-la.ustiming.org";  /* change to your favorite NTP server */
prog_char s_WT_SETUP_01[] PROGMEM = "set u m 0x1";
prog_char s_WT_SETUP_02[] PROGMEM = "set comm remote 0";
prog_char s_WT_SETUP_03[] PROGMEM = "set comm idle 30";
prog_char s_WT_SETUP_04[] PROGMEM = "set comm time 2000";
prog_char s_WT_SETUP_05[] PROGMEM = "set comm size 64";
prog_char s_WT_SETUP_06[] PROGMEM = "set comm match 0x9";
prog_char s_WT_SETUP_07[] PROGMEM = "time";
prog_char s_WT_STATUS_SENSORS[] PROGMEM = "show q 0x177 ";
prog_char s_WT_STATUS_TEMP[] PROGMEM = "show q t ";
prog_char s_WT_STATUS_RSSI[] PROGMEM = "show rssi ";
prog_char s_WT_STATUS_BATT[] PROGMEM = "show battery ";
prog_char s_WT_MSG_JOIN[] PROGMEM = "Credentials Set, Joining ";
prog_char s_WT_MSG_START_WEBCLIENT[] PROGMEM = "Starting WebClientGetPut - Please wait. ";
prog_char s_WT_MSG_RAM[] PROGMEM = "RAM :";
prog_char s_WT_MSG_START_WIFLY[] PROGMEM = "Started WiFly, RAM :";
prog_char s_WT_MSG_WIFI[] PROGMEM = "Initial WiFi Settings :";
prog_char s_WT_MSG_APP_SETTINGS[] PROGMEM = "Configure WebClientGetPost Settings...";
prog_char s_WT_MSG_WIRE_RX[] PROGMEM = "Arduino Rx Pin (connect to WiFly Tx):";
prog_char s_WT_MSG_WIRE_TX[] PROGMEM = "Arduino Tx Pin (connect to WiFly Rx):";
prog_char s_WT_MSG_FAIL_OPEN[] PROGMEM = "Failed on opening connection to:";
// prog_char s_WT_HTML_HEAD_01[] PROGMEM = "HTTP/1.1 200 OK \r ";
// prog_char s_WT_HTML_HEAD_02[] PROGMEM = "Content-Type: text/html;charset=UTF-8\r ";
// prog_char s_WT_HTML_HEAD_03[] PROGMEM = " Content-Length: ";
// prog_char s_WT_HTML_HEAD_04[] PROGMEM = "Connection: close \r\n\r\n";
// prog_char s_WT_POST_HEAD_01[] PROGMEM = "HTTP/1.1\n";
// prog_char s_WT_POST_HEAD_02[] PROGMEM = "Content-Type: application/x-www-form-urlencoded\n";
// prog_char s_WT_POST_HEAD_03[] PROGMEM = "Content-Length: ";
// prog_char s_WT_POST_HEAD_04[] PROGMEM = "Connection: close\n\n";

#define IDX_WT_SETUP_00 0
#define IDX_WT_SETUP_01 IDX_WT_SETUP_00
#define IDX_WT_SETUP_02 IDX_WT_SETUP_01 +1
#define IDX_WT_SETUP_03 IDX_WT_SETUP_02 +1
#define IDX_WT_SETUP_04 IDX_WT_SETUP_03 +1
#define IDX_WT_SETUP_05 IDX_WT_SETUP_04 +1
#define IDX_WT_SETUP_06 IDX_WT_SETUP_05 +1
#define IDX_WT_SETUP_07 IDX_WT_SETUP_06 +1

#define IDX_WT_STATUS_SENSORS    IDX_WT_SETUP_07 +1
#define IDX_WT_STATUS_TEMP       IDX_WT_STATUS_SENSORS +1
#define IDX_WT_STATUS_RSSI       IDX_WT_STATUS_TEMP +1
#define IDX_WT_STATUS_BATT       IDX_WT_STATUS_RSSI +1

#define IDX_WT_MSG_JOIN          IDX_WT_STATUS_BATT +1
#define IDX_WT_MSG_START_WEBCLIENT IDX_WT_MSG_JOIN +1
#define IDX_WT_MSG_RAM           IDX_WT_MSG_START_WEBCLIENT +1
#define IDX_WT_MSG_START_WIFLY   IDX_WT_MSG_RAM +1
#define IDX_WT_MSG_WIFI          IDX_WT_MSG_START_WIFLY +1
#define IDX_WT_MSG_APP_SETTINGS  IDX_WT_MSG_WIFI +1
#define IDX_WT_MSG_WIRE_RX       IDX_WT_MSG_APP_SETTINGS +1
#define IDX_WT_MSG_WIRE_TX       IDX_WT_MSG_WIRE_RX +1
#define IDX_WT_MSG_FAIL_OPEN     IDX_WT_MSG_WIRE_TX +1

#define IDX_WT_HTML_HEAD_01      IDX_WT_MSG_FAIL_OPEN + 1
#define IDX_WT_HTML_HEAD_02      IDX_WT_HTML_HEAD_01 + 1
#define IDX_WT_HTML_HEAD_03      IDX_WT_HTML_HEAD_02 + 1
#define IDX_WT_HTML_HEAD_04      IDX_WT_HTML_HEAD_03 + 1

#define IDX_WT_POST_HEAD_01      IDX_WT_HTML_HEAD_04 + 1
#define IDX_WT_POST_HEAD_02      IDX_WT_POST_HEAD_01 + 1
#define IDX_WT_POST_HEAD_03      IDX_WT_POST_HEAD_02 + 1
#define IDX_WT_POST_HEAD_04      IDX_WT_POST_HEAD_03 + 1


PROGMEM const char *WT_string_table[] =
{
//  s_WT_SETUP_00,
  s_WT_SETUP_01,
  s_WT_SETUP_02,
  s_WT_SETUP_03,
  s_WT_SETUP_04,
  s_WT_SETUP_05,
  s_WT_SETUP_06,
  s_WT_SETUP_07,
  s_WT_STATUS_SENSORS,
  s_WT_STATUS_TEMP,
  s_WT_STATUS_RSSI,
  s_WT_STATUS_BATT,
  s_WT_MSG_JOIN,
  s_WT_MSG_START_WEBCLIENT,
  s_WT_MSG_RAM,
  s_WT_MSG_START_WIFLY,
  s_WT_MSG_WIFI,
  s_WT_MSG_APP_SETTINGS,
  s_WT_MSG_WIRE_RX,
  s_WT_MSG_WIRE_TX,
  s_WT_MSG_FAIL_OPEN,
  // s_WT_HTML_HEAD_01,
  // s_WT_HTML_HEAD_02,
  // s_WT_HTML_HEAD_03,
  // s_WT_HTML_HEAD_04,
  // s_WT_POST_HEAD_01,
  // s_WT_POST_HEAD_02,
  // s_WT_POST_HEAD_03,
  // s_WT_POST_HEAD_04
};

char* GetBuffer_P(const int StringIndex, char* pBuffer, int bufSize) {
  strncpy_P(pBuffer, (char*)pgm_read_word(&(WT_string_table[StringIndex])), bufSize);
  return pBuffer;
}


