

all: snake

snake: snake.c
	gcc snake.c -lallegro -lallegro_primitives -lm -pthread -o snake

clean:
	rm -f snake *.o
