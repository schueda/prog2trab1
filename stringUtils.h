#ifndef __STRING_UTILS__
#define __STRING_UTILS__

int isSubstring(char string[], char subString[]);

int checkLineStart(char line[], char start[]);
int checkFileExtension(char fileName[], char extension[]);

char *getDate(char *line);
float getDistance(char *line);
float getSpeed(char *line);
int getHr(char *line);
int getCadence(char *line);
float getAltitude(char *line);
int getTime(char *line);

char *formatDate(char *date);

#endif