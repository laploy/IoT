#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

#define USE_SERIAL Serial

// Max string length may have to be adjusted depending on data to be extracted
#define MAX_STRING_LEN  2000

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
    if(httpCode > 0) 
    {
        USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);
        if(httpCode == HTTP_CODE_OK) 
        {
            String payload = http.getString();
            USE_SERIAL.println(payload.length());
            Show(payload);
        }
    } 
    else 
    {
        USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
    for(int i =0; i < 20; i++)
    {
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
        yield();
        count++;
    }
}

// Process each char from web
void ProcessChar(char inChar) {
  if (inChar == '<') {
     addChar(inChar, tmpStr);
     tagFlag = true;
     dataFlag = false;
  } else if (inChar == '>') {
     addChar(inChar, tmpStr);
     if (tagFlag) {      
        strncpy(tagStr, tmpStr, strlen(tmpStr)+1);
     }
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
     // Find specific tags and print data
     if (matchTag("<title>")) {
        //Serial.print("title: ");
        //dataStr.replace("&apos;", "......");
        //if (findString(dataStr, "Newslookup.com"))
        //{
            Serial.print(dataStr);
            Serial.println("");
        //}
     }
//     if (matchTag("<description>")) {
//        Serial.print("Des: ");
//        Serial.print(dataStr);
//     }
//     if (matchTag("<pubDate>")) {
//        Serial.print("Date: ");
//        Serial.print(dataStr);
//        Serial.println("");
//     }

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

bool findString(char* searchText, char* searchKey)
{
    char c_to_search[20];
    strcpy(c_to_search, searchKey); /* BANG!!! */
    c_to_search[19] = '\0';

    char text[20];
    strcpy(text, searchText); /* BANG!!! */
    text[19] = '\0';

    int pos_search = 0;
    int pos_text = 0;
    int len_search = 4;
    int len_text = 67;
    for (pos_text = 0; pos_text < len_text - len_search;++pos_text)
    {
        if(text[pos_text] == c_to_search[pos_search])
        {
            ++pos_search;
            if(pos_search == len_search)
            {
                // match
                //printf("match from %d to %d\n",pos_text-len_search,pos_text);
                return true;
            }
        }
        else
        {
           pos_text -=pos_search;
           pos_search = 0;
        }
    }
    // no match
    //printf("no match\n");
   return false;
}
