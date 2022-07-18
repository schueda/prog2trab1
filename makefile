CFLAGS = -Wall -std=c99 -D_DEFAULT_SOURCE
EXEC_NAME = gps
OBJS = main.o directoryParse.o activityTrees.o bikeTree.o histogram.o stringUtils.o

all: clean $(EXEC_NAME) 

$(EXEC_NAME): $(OBJS)
	gcc $(OBJS) $(CFLAGS) -o $(EXEC_NAME)


main.o: main.c

directoryParse.o: directoryParse.c directoryParse.h

bikeTree.o: bikeTree.c bikeTree.h

activityTrees.o: activityTrees.c activityTrees.h

histogram.o: histogram.h histogram.c

stringUtils.o: stringUtils.c stringUtils.h

clean:
	rm -f $(OBJS) *~

purge: clean
	rm -f $(EXEC_NAME)