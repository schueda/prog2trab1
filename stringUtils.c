#include <string.h>
#include "stringUtils.h"

int checkFileExtension(char fileName[], char extension[]) {
    int i, j=0;
    int nameSize = strlen(fileName);
    int extensionSize = strlen(extension);

    if((nameSize == 0) || (extensionSize == 0) || (extensionSize > nameSize)) {
        return 0;
    }

    for(i=nameSize-extensionSize; i<nameSize; i++) {
        if(fileName[i] != extension[j]) {
            return 0;
        }
        j++;
    }

    return 1;
}

int checkLineStart(char line[], char start[]) {
    int i, j=0;
    int lineSize = strlen(line);
    int startSize = strlen(start);

    if((lineSize == 0) || (startSize == 0) || (startSize > lineSize)) {
        return 0;
    }

    for(i=0; i<startSize; i++) {
        if(line[i] != start[j]) {
            return 0;
        }
        j++;
    }

    return 1;
}

int isSubstring(char string[], char subString[]) {
    int i, j;
    int valid = 1;
    int stringSize = strlen(string);
    int subStringSize = strlen(subString);

    if((stringSize == 0) || (subStringSize == 0)) {
        return -2;
    }

    for(i=0; i<=(stringSize-subStringSize); i++) {
        if(string[i] == string[0]) {
            for (j=1; j<subStringSize && valid; j++) {
                if (string[i+j] != subString[j]) {
                    valid = 0;
                }
            }
            if (valid) {
                return i;
            }
            valid = 1;
        }
    }

    return -1;
}