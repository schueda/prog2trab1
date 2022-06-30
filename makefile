CFLAGS = -Wall -std=c99
EXEC_NAME = gps
OBJS = directoryParse.o histogram.o

all: clean $(EXEC_NAME) 

$(EXEC_NAME): $(OBJS)
	gcc $(OBJS) $(CFLAGS) main.c -o $(EXEC_NAME)


directoryParse.o: directoryParse.c directoryParse.h

histogram.o: histogram.h histogram.c

clean:
	-rm -f $(OBJS) *~

purge: clean
	-rm -f $(EXEC_NAME)