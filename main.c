#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "histogram.h"
#include "directoryParse.h"

int main(int argc, char *argv[]){
    bikeNodeT *raizBikes;

    int opt;
    while((opt = getopt(argc, argv, "d:")) != -1) {
        switch (opt) {
        case 'd':
            raizBikes = parseDirectory(optarg);

            printBikeTree(raizBikes);
            printActivityTreeDate(raizBikes->raizDate);
            break;
        default:
            perror("Usage: [-d] [Directory...]\n");
            return 1;
        }
    }


    return 0;
}

