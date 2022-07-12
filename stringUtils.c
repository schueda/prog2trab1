#include <string.h>
#include <stdlib.h>
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

char *getDate(char *line) {
    char lineCopy[strlen(line)];
    strcpy(lineCopy, line);

    char *date = malloc(sizeof(char)*10);
    *(strrchr(lineCopy, ' ')) = '\0';
    strcpy(date, strchr(lineCopy, ' ')+1);
    return date;
}

float getDistance(char *line) {
    *(strrchr(line, ' ')) = '\0';
    return atof(strchr(line, ' ')+1);
}

float getSpeed(char *line) {
    *(strrchr(line, ' ')) = '\0';
    return atof(strchr(line, ' ')+1);
}

int getHr(char *line) {
    *(strrchr(line, ' ')) = '\0';
    return atoi(strchr(line, ' ')+1);
}

int getCadence(char *line) {
    *(strrchr(line, ' ')) = '\0';
    return atoi(strchr(line, ' ')+1);
}

float getAltitude(char *line) {
    char lineCopy[strlen(line)];
    strcpy(lineCopy, line);

    *(strrchr(lineCopy, ' ')) = '\0';
    return atof(strchr(lineCopy, ' ')+1);
}

int getTime(char *line) {
    char lineCopy[strlen(line)];
    strcpy(lineCopy, line);

    lineCopy[strlen(lineCopy)] = '\0';
    char *arg = strrchr(lineCopy, ' ') + 1;
    int hours = atoi(arg);
    int minutes = atoi(strchr(arg, ':')+1);
    int seconds = atoi(strrchr(lineCopy, ':')+1);
    return 3600 * hours + 60 * minutes + seconds;
    return 0;
}

char *formatDate(char *date) {
    char *formattedDate = malloc(sizeof(char)*11);

    formattedDate[0] = date[8];
    formattedDate[1] = date[9];
    formattedDate[2] = '/';
    formattedDate[3] = date[5];
    formattedDate[4] = date[6];
    formattedDate[5] = '/';
    formattedDate[6] = date[0];
    formattedDate[7] = date[1];
    formattedDate[8] = date[2];
    formattedDate[9] = date[3];
    formattedDate[10] = '\0';

    return formattedDate;
}