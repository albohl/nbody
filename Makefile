# Make animate to show a nice window
# Make starsim to only benchmark
CC = gcc -ggdb -std=c99

star.o: 
	$(CC) -c star.c
starsim: star.o
	$(CC) main.c star.o -o main  -lm -pg
animate: star.o
	$(CC) -DANIMATE main.c star.o -o main -lm -lX11
animate_rec: star.o
	$(CC) -DANIMATE main_rec.c star.o -o main -lm -lX11
run:
	./main
clean:
	rm star.o