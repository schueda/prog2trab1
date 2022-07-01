#ifndef __DIRECTORY_PARSE__
#define __DIRECTORY_PARSE__

typedef struct {
    struct bike *raiz;
    int count;
} bikeTree;

typedef struct {
    char gear[128];
    struct bike *filhoEsq;
    struct bike *filhoDir;
    struct bike *pai;

    struct activity *raizDate;
    struct activity *raizDist;
    struct activity *raizSubAcum;

} bikeNode;

typedef struct {
    char date[10];
    float dist;
    float veloMed;
    float veloMax;
    float hrMed;
    float hrMax;
    float cadMed;
    float subAcum;

    struct activity *dateFilhoDir;
    struct activity *dateFilhoEsq;
    struct activity *datePai;

    struct activity *distFilhoDir;
    struct activity *distFilhoEsq;
    struct activity *distPai;

    struct activity *subAcumFilhoDir;
    struct activity *subAcumFilhoEsq;
    struct activity *subAcumPai;

} activityNode;

bikeTree* parseDirectory(char* directoryPath);

#endif