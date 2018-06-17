//
//// Define Constants
//// Max string length may have to be adjusted depending on data to be extracted
//#define MAX_STRING_LEN  20
//
//// Setup vars
//char tagStr[MAX_STRING_LEN] = "";
//char dataStr[MAX_STRING_LEN] = "";
//char tmpStr[MAX_STRING_LEN] = "";
//char endTag[3] = { '<', '/', '\0' };
//int len;
//
//// DECLARED VARIABLES HERE FOR GLOBAL USE
//char name[MAX_STRING_LEN] = "\0";
//char flavor_name[MAX_STRING_LEN] = "\0";
//char mix_volume[MAX_STRING_LEN] = "\0";
//
//// Flags to differentiate XML tags from document elements (ie. data)
//boolean tagFlag = false;
//boolean dataFlag = false;
//
//
//
//
//void serialEvent() {
//	//Serial.println("serialEvent Started");
//	// Read a char
//	char inChar = 'a';
//	//Serial.print(".");
//
//	if (inChar == '<') {
//		addChar(inChar, tmpStr);
//		tagFlag = true;
//		dataFlag = false;
//
//	}
//	else if (inChar == '>') {
//		addChar(inChar, tmpStr);
//
//		if (tagFlag) {
//			strncpy(tagStr, tmpStr, strlen(tmpStr) + 1);
//		}
//
//		// Clear tmp
//		clearStr(tmpStr);
//
//		tagFlag = false;
//		dataFlag = true;
//
//	}
//	else if (inChar != 10) {
//		if (tagFlag) {
//			// Add tag char to string
//			addChar(inChar, tmpStr);
//
//			// Check for </XML> end tag, ignore it
//			if (tagFlag && strcmp(tmpStr, endTag) == 0) {
//				clearStr(tmpStr);
//				tagFlag = false;
//				dataFlag = false;
//			}
//		}
//
//		if (dataFlag) {
//			// Add data char to string
//			addChar(inChar, dataStr);
//		}
//	}
//
//	// If a LF, process the line
//	if (inChar == 10) {
//		// Find specific tags and print data
//		if (matchTag("<name>")) {
//			strncpy(name, dataStr, 20);
//			name[21] = '\0';
//		}
//		// Clear all strings
//		clearStr(tmpStr);
//		clearStr(tagStr);
//		clearStr(dataStr);
//
//		// Clear Flags
//		tagFlag = false;
//		dataFlag = false;
//	}
//}
//void clearStr(char* str) {
//	int len = strlen(str);
//	for (int c = 0; c < len; c++) {
//		str[c] = 0;
//	}
//}
//void addChar(char ch, char* str) {
//	char *tagMsg = "<TRUNCATED_TAG>";
//	char *dataMsg = "-TRUNCATED_DATA-";
//
//	// Check the max size of the string to make sure it doesn't grow too
//	// big.  If string is beyond MAX_STRING_LEN assume it is unimportant
//	// and replace it with a warning message.
//	if (strlen(str) > MAX_STRING_LEN - 2) {
//		if (tagFlag) {
//			clearStr(tagStr);
//			strcpy(tagStr, tagMsg);
//		}
//		if (dataFlag) {
//			clearStr(dataStr);
//			strcpy(dataStr, dataMsg);
//		}
//
//		// Clear the temp buffer and flags to stop current processing 
//		clearStr(tmpStr);
//		tagFlag = false;
//		dataFlag = false;
//
//	}
//	else {
//		// Add char to string
//		str[strlen(str)] = ch;
//	}
//}
//boolean matchTag(char* searchTag) {
//	if (strcmp(tagStr, searchTag) == 0) {
//		return true;
//	}
//	else {
//		return false;
//	}
//}