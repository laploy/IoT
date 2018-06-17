/// <remarks>
/// Laploy V.Angkul
/// laploy@gmail.com
/// July ,2017
/// </remarks>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

#define USE_SERIAL Serial
#define MAX_SIZE	8000
#define TAG_SIZE	80

char xmlStr[MAX_SIZE];
char tagStr[TAG_SIZE];
int foundStartTag = false;

ESP8266WiFiMulti WiFiMulti;
String news[10];
int newsCount = 0;
const char* ssid = "xxx";
const char* password = "xxx";
const char* rssUrl = "http://www.bangkokpost.com/rss/data/most-recent.xml";

void setup()
{
	Serial.begin(115200);
	delay(500);
	Serial.println("Start");
}
void loop()
{
	String s = getNewsFeed();
	if (s.length() > 500)
	{
		putXmlToArray(s);
		getHeadLine();
	}
	Serial.print(" End ");
	for(int i = 0; i < 20; i++) { USE_SERIAL.print("."); delay(500); }
}

String getNewsFeed()
{
	String retVal = " ";
	HTTPClient http;
	USE_SERIAL.print("[HTTP] begin...\n");
	http.begin(rssUrl);
	USE_SERIAL.print("[HTTP] GET...\n");
	int httpCode = http.GET();
	if (httpCode > 0)
	{
		USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);
		if (httpCode == HTTP_CODE_OK)
		{
			retVal = http.getString();
		}
	}
	else
	{
		USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
	}
	http.end();
	return retVal;
}
void getHeadLine()
{
	int i;
	for (i = 0; i < MAX_SIZE - 1; i++)
	{
		if (xmlStr[i] == '>')
		{
			char c[1];
			c[0] = xmlStr[i];
			addChar(c);
			foundStartTag = false;
			if (foundEndTag(tagStr)) break;
			clearStr(tagStr);
			continue;
		}
		if (xmlStr[i] == '<')
		{
			foundStartTag = true;
			if (findTag("<title>", i))
			{
				char text[100] = { 0 };
				getTitle(text, i + 1);
				if (!findWord(text, "Bangkokpost.com") && !findWord(text, "bangkokpost.com"))
					USE_SERIAL.printf("%s\n", text);
				i += strlen(text);
			}
		}
		if (foundStartTag)
		{
			char c[1];
			c[0] = xmlStr[i];
			addChar(c);
		}
	}
}
void clearStr(char* str) {
	int len = strlen(str);
	for (int c = 0; c < len; c++) {
		str[c] = 0;
	}
}
void addChar(char* c)
{
	char str2[2];
	str2[0] = c[0];
	str2[1] = '\0';
	strcat(tagStr, str2);
}
bool findWord(char* searchText, char* searchKey)
{
	if (strstr(searchText, searchKey) == NULL)
		return false;
	else
		return true;
}
bool foundEndTag(char* str)
{
	if (findWord(str, "</rss>"))
	{
		return true;
	}
	else
	{
		return false;
	}
}
void getTitle(char *text, int pos)
{
	int i, k, count;
	for (i = pos; i < (pos + TAG_SIZE); i++)	// this loop for skipping <tag>
	{
		if (xmlStr[i] == '>')
		{
			break;
		}
	}
	count = 0;
	for (k = i + 1; k < 8000; k++)
	{
		text[count++] = xmlStr[k];
		if (xmlStr[k] == '<')
		{
			text[--count] = '\0';
			break;
		}
	}
}
bool findTag(char *text, int pos)
{
	char s[TAG_SIZE] = { 0 };
	int i = 0;
	for (i = 0; i < TAG_SIZE - 1; i++)
	{
		if (xmlStr[pos] == '>')
		{
			s[i++] = xmlStr[pos];
			break;
		}
		s[i] = xmlStr[pos++];
	}
	s[i] = '\0';
	if (findWord(s, text))
		return true;
	else
		return false;
}
void putXmlToArray(String s)
{
	int i;
	for (i = 0; i < s.length() - 1; i++)
	{
		xmlStr[i] = s[i];
	}
}