#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include <stdlib.h>

#define MAX_SIZE	8000
#define TAG_SIZE	80

char xmlStr[MAX_SIZE];
char tagStr[TAG_SIZE];
int foundStartTag = false;

main()
{
	readTextFile();
	getHeadLine();
}
int readTextFile()
{
	FILE *fptr;
	if ((fptr = fopen("d:\\temp\\bangkokpost.xml", "r")) == NULL) {
		printf("Error! opening file\n");
		return false;
	}
	printf("Opening file OK\n");
	fscanf(fptr, "%[^\n]", xmlStr);
	fclose(fptr);
	return true;
}
getHeadLine()
{
	int i;
	for (i = 0; i < MAX_SIZE-1; i++)
	{
		if (xmlStr[i] == '>')
		{
			addChar(xmlStr[i]);
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
				getTitle(text, i+1);
				if(!findWord(text, "Bangkokpost.com") && !findWord(text, "bangkokpost.com"))
					printf("%s\n", text);
				i += strlen(text);
			}
		}
		if (foundStartTag)
		{
			addChar(xmlStr[i]);
		}
	}
}
clearStr(char* str) {
	int len = strlen(str);
	for (int c = 0; c < len; c++) {
		str[c] = 0;
	}
}
addChar(char* c)
{
	char str2[2];
	str2[0] = c;
	str2[1] = '\0';
	strcat(tagStr, str2);
}
int findWord(char* searchText, char* searchKey)
{
	if (strstr(searchText, searchKey) == NULL)
		return false;
	else
		return true;
}
int foundEndTag(char* str)
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
getTitle(char *text, int pos)
{
	int i,k, count;
	for (i = pos; i < (pos + TAG_SIZE); i++)	// this loop for skipping <tag>
	{
		if (xmlStr[i] == '>')
		{
			break;
		}
	}
	count = 0;
	for (k = i+1; k < 8000; k++)
	{
		text[count++] = xmlStr[k];
		if (xmlStr[k] == '<')
		{
			text[--count] = '\0';
			break;
		}
	}
}
int findTag(char *text, int pos)
{
	char s[TAG_SIZE] = {0};
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
		return 1;
	else
		return 0;
}