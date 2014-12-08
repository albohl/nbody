# Make animate to show a nice window
# Make starsim to only benchmark
CC = gcc -ggdb -std=c99
INCDIR = /usr/local/include
LIBDIR = /usr/local/lib
TESTLIBS = -lcunit

star.o:
	$(CC) -c star.c
starsim: star.o
	$(CC) main.c star.o -o main  -lm -pg
animate: star.o
	$(CC) -DANIMATE main.c star.o -o main -lm -lX11
test: star.o
	$(CC) -Wall -DTESTING -I$(INCDIR) -L$(LIBDIR) -o test unittests.c star.o main.c $(TESTLIBS) -lm
	./test
run:
	./main
clean:
	rm star.o
