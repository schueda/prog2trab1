#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "directoryParse.h"
#include "stringUtils.h"
#define LINE_SIZE 256

bikeNode* parseFile(char* filePath);

bikeTree* parseDirectory(char* directoryPath) {
    DIR *dirStream;
    struct dirent *dirEntry;
    
    char filePath[LINE_SIZE+1];

    dirStream = opendir(directoryPath);
    if(!dirStream) {
        return NULL;
    }

    while((dirEntry = readdir(dirStream)) != NULL) {
        if(dirEntry->d_type == DT_REG && checkFileExtension(dirEntry->d_name, ".log")) {
            strcpy(filePath, directoryPath);
            strcat(filePath, "/");
            strcat(filePath, dirEntry->d_name);

            parseFile(filePath);
        }
    }

    closedir(dirStream);
    return NULL;
}

bikeNode* parseFile(char* filePath) {
    FILE* file;
    char line[LINE_SIZE+1];

    file = fopen(filePath, "r");

    if(checkLineStart(fgets(line, LINE_SIZE, file), "Gear:")) {
        printf("%s", &line[6]);
    }

    fclose(file);
    return NULL;
}

