#ifndef __STRING_UTILS__
#define __STRING_UTILS__

int checkLineStart(char line[], char start[]); // Verifica se o nome de um arquivo possui a extensão de arquivo especificada.
int checkFileExtension(char fileName[], char extension[]); // Verifica se a linha inicia da forma especificada.

char *getDate(char *line); // Extrai a data de uma linha.
float getDistance(char *line); // Extrai a distância de uma linha.
float getSpeed(char *line); // Extrai a velocidade de uma linha.
int getHr(char *line); // Extrai o heart rate de uma linha.
int getCadence(char *line); // Extrai a cadência de uma linha.
float getAltitude(char *line); // Extrai a altitude de uma linha.
int getTime(char *line); // Extrai o tempo de uma linha.

char *formatDate(char *date); // Formata a data para uma forma habitual.

#endif