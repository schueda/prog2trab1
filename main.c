#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "histogram.h"
#include "directoryParse.h"

int main(int argc, char *argv[]){
    bikeNodeT *bikeRoot;

    int opt;
    while((opt = getopt(argc, argv, "d:")) != -1) {
        switch (opt) {
        case 'd':
            bikeRoot = parseDirectory(optarg);

            printBikeTree(bikeRoot);
            printActivityTreeDate(bikeRoot->activityByDateRoot);
            break;
        default:
            perror("Usage: [-d] [Directory...]\n");
            return 1;
        }
    }


    return 0;
}

