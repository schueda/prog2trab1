#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "directoryParse.h"
#define LINE_SIZE 256

char* parseDirectory(char* directoryPath) {
    DIR *dirStream;
    struct dirent *dirEntry;
    FILE* file;
    char line[LINE_SIZE+1];
    char filePath[LINE_SIZE+1];

    dirStream = opendir(directoryPath);
    if(!dirStream) {
        return NULL;
    }

    while((dirEntry = readdir(dirStream)) != NULL) {
        if(dirEntry->d_type == DT_REG) {
            strcpy(filePath, directoryPath);
            strcat(filePath, "/");
            strcat(filePath, dirEntry->d_name);

            file = fopen(filePath, "r");

            printf("%s", fgets(line, LINE_SIZE, file));

            fclose(file);
        }
    }

    closedir(dirStream);
    return NULL;
}