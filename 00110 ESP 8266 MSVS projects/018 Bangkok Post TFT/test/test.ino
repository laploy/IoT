/// <remarks>
/// Laploy V.Angkul
/// laploy@gmail.com
/// July ,2017
/// </remarks>

#include <Arduino.h>
#include <SPI.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <Adafruit_ILI9341.h>
#include <gfxfont.h>
#include <Adafruit_GFX.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

#define USE_SERIAL Serial
#define TFT_DC D1
#define TFT_CS D2

#define MAX_SIZE	8000
#define TAG_SIZE	80
#define MAX_HEAD	10

char xmlStr[MAX_SIZE];
char tagStr[TAG_SIZE];
int foundStartTag = false;

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
ESP8266WiFiMulti WiFiMulti;
String news[MAX_HEAD];
int newsCount = 0;
const char* ssid = "xxx";
const char* password = "xxx";
const char* rssUrl = "http://www.bangkokpost.com/rss/data/most-recent.xml";

void setup()
{
	Serial.begin(115200);
	delay(500);
	Serial.println("Start");
	tft.begin();
	tft.setRotation(3);
	tft.setTextColor(ILI9341_YELLOW); 
	tft.setTextSize(3);
}
void loop()
{
	String s = getNewsFeed();
	if (s.length() > 500)
	{
		putXmlToArray(s);
		getHeadLine();
		for (int i = 0; i < MAX_HEAD - 1; i++)
		{
			Serial.println(news[i]);
			String s = news[i];
			tft.fillScreen(ILI9341_BLACK);
			tft.setCursor(0, 0);
			for (int k = 0; k < s.length(); k++)
			{
				tft.print(s[k]);
				delay(300);
			}
			for (int j = 0; j < 35; j++) { tft.print(". "); delay(800); }
		}
	}
	Serial.print("- - - - End - - - -");
	Serial.println(" ");
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
				{
					//USE_SERIAL.printf("%s\n", text);
					putHeadLineToArray(text);
				}
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
void putHeadLineToArray(String s)
{
	news[newsCount++] = s;
	if (newsCount > MAX_HEAD - 1)
		newsCount = 0;
}