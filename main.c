#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "histogram.h"
#include "directoryParse.h"

int main(int argc, char *argv[]){
    bikeTree *bikes;

    int opt;
    while((opt = getopt(argc, argv, "d:")) != -1) {
        switch (opt) {
        case 'd':
            bikes = parseDirectory(optarg);
            break;
        default:
            fprintf(stderr, "Usage: %s [-d] [Directory...]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    

    return 0;
}

