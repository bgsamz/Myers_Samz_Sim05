CC = gcc
DEBUG = -g
CFLAGS = -Wall -std=c99 -c $(DEBUG)
LFLAGS = -Wall -std=c99 -pthread $(DEBUG)

sim04 : main.o configReader.o programReader.o programRunner.o outputWriter.o helperFunctions.o timer.o errors.o structures.h
	$(CC) $(LFLAGS) main.o configReader.o programReader.o programRunner.o outputWriter.o helperFunctions.o timer.o errors.o -o sim04
	rm *.o

main.o : main.c configReader.h programReader.h helperFunctions.h structures.h
	$(CC) $(CFLAGS) main.c

configReader.o : configReader.c helperFunctions.h structures.h
	$(CC) $(CFLAGS) configReader.c

programReader.o : programReader.c helperFunctions.h structures.h
	$(CC) $(CFLAGS) programReader.c

programRunner.o : programRunner.c helperFunctions.h timer.h structures.h
	$(CC) $(CFLAGS) programRunner.c

outputWriter.o : outputWriter.c timer.h structures.h
	$(CC) $(CFLAGS) outputWriter.c

helperFunctions.o : helperFunctions.c structures.h
	$(CC) $(CFLAGS) helperFunctions.c

timer.o : timer.c structures.h
	$(CC) $(CFLAGS) timer.c

errors.o : errors.c
	$(CC) $(CFLAGS) errors.c

clean:
	rm sim04
