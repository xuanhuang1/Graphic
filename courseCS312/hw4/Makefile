ifeq ($(shell uname -s), Darwin)
LDFLAGS=-L/opt/ports/lib -framework OpenGL -lglfw -lGLEW -lm
else
LDFLAGS=-lX11 -lGL -lGLU -lglut -lGLEW -lglfw -lm
endif

CC = g++
CFLAGS=-g -I/opt/ports/include 

INIT_SHADER = initshader.o

all:
	$(CC) $(CFLAGS) -c example1.c -o example1.o

	$(CC) $(CFLAGS) -c initshader.c -o initshader.o

	$(CC) $(CFLAGS) initshader.o example1.o  $(LDFLAGS) -o test


clean: 
	-rm -r test *.o core *.dSYM
