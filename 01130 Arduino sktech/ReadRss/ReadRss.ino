#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#define USE_SERIAL Serial

// Max string length may have to be adjusted depending on data to be extracted
#define MAX_STRING_LEN  200

// Setup vars
char tagStr[MAX_STRING_LEN] = "";
char dataStr[MAX_STRING_LEN] = "";
char tmpStr[MAX_STRING_LEN] = "";
char endTag[3] = {'<', '/', '\0'};
int len;

// Flags to differentiate XML tags from document elements (ie. data)
boolean tagFlag = false;
boolean dataFlag = false;

ESP8266WiFiMulti WiFiMulti;
const char* ssid = "XXX";
const char* password = "XXX";

void setup() {
    USE_SERIAL.begin(115200);
    USE_SERIAL.printf("\n");
    USE_SERIAL.printf("Connecting to %s\n", ssid);
    WiFiMulti.addAP(ssid, password);
    while (WiFiMulti.run() != WL_CONNECTED) 
    {
        delay(100);
        USE_SERIAL.printf(".");
    }
    USE_SERIAL.printf("\n");
    USE_SERIAL.printf("WiFi connected");
}

void loop() {
    HTTPClient http;
    USE_SERIAL.print("[HTTP] begin...\n");
    http.begin("http://www.newslookup.com/rss/wires/newslookup-wires.rss"); 
    USE_SERIAL.print("[HTTP] GET...\n");
    int httpCode = http.GET();
    if(httpCode > 0) {
        USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);
        if(httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            USE_SERIAL.println(payload.length());
            Show(payload);
            }
        } 
        else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }
        http.end();
    while(true){
        yield();
        delay(500);
    }
}

void Show(String s)
{
    int len = s.length();
    int count = 0;
    while(count < len)
    {
        ProcessChar(s[count]);
        count++;
    }
}

// Process each char from web
void ProcessChar(char c) {

  // Read a char
     char inChar = c;
  //Serial.print(".");
 
  if (inChar == '<') {
     addChar(inChar, tmpStr);
     tagFlag = true;
     dataFlag = false;

  } else if (inChar == '>') {
     addChar(inChar, tmpStr);

     if (tagFlag) {      
        strncpy(tagStr, tmpStr, strlen(tmpStr)+1);
     }

     // Clear tmp
     clearStr(tmpStr);

     tagFlag = false;
     dataFlag = true;      
     
  } else if (inChar != 10) {
     if (tagFlag) {
        // Add tag char to string
        addChar(inChar, tmpStr);

        // Check for </XML> end tag, ignore it
        if ( tagFlag && strcmp(tmpStr, endTag) == 0 ) {
           clearStr(tmpStr);
           tagFlag = false;
           dataFlag = false;
        }
     }
     
     if (dataFlag) {
        // Add data char to string
        addChar(inChar, dataStr);
     }
  }  
 
  // If a LF, process the line
  if (inChar == 10 ) {

/*
     Serial.print("tagStr: ");
     Serial.println(tagStr);
     Serial.print("dataStr: ");
     Serial.println(dataStr);
*/

     // Find specific tags and print data
     if (matchTag("<title>")) {
           Serial.print("title: ");
        Serial.print(dataStr);
        Serial.println("");
     }
     if (matchTag("<relative_humidity>")) {
           Serial.print(", Humidity: ");
        Serial.print(dataStr);
     }
     if (matchTag("<pressure_in>")) {
           Serial.print(", Pressure: ");
        Serial.print(dataStr);
        Serial.println("");
     }

     // Clear all strings
     clearStr(tmpStr);
     clearStr(tagStr);
     clearStr(dataStr);

     // Clear Flags
     tagFlag = false;
     dataFlag = false;
  }
}
/////////////////////
// Other Functions //
/////////////////////

// Function to clear a string
void clearStr (char* str) {
  int len = strlen(str);
  for (int c = 0; c < len; c++) {
     str[c] = 0;
  }
}

//Function to add a char to a string and check its length
void addChar (char ch, char* str) {
  char *tagMsg  = "<TRUNCATED_TAG>";
  char *dataMsg = "-TRUNCATED_DATA-";

  // Check the max size of the string to make sure it doesn't grow too
  // big.  If string is beyond MAX_STRING_LEN assume it is unimportant
  // and replace it with a warning message.
  if (strlen(str) > MAX_STRING_LEN - 2) {
     if (tagFlag) {
        clearStr(tagStr);
        strcpy(tagStr,tagMsg);
     }
     if (dataFlag) {
        clearStr(dataStr);
        strcpy(dataStr,dataMsg);
     }

     // Clear the temp buffer and flags to stop current processing 
     clearStr(tmpStr);
     tagFlag = false;
     dataFlag = false;

  } else {
     // Add char to string
     str[strlen(str)] = ch;
  }
}

// Function to check the current tag for a specific string
boolean matchTag (char* searchTag) {
  if ( strcmp(tagStr, searchTag) == 0 ) {
     return true;
  } else {
     return false;
  }
}

