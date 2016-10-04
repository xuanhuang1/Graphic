# basic Makefile 
# compile with "make <filename without .c>
# Note that if you installed your OpenGL libraries in a different place
# the paths that follow -L in LDFLAGS and -I in CFLAGS will have to change
# accordingly

ifeq ($(shell uname -s), Darwin)
LDFLAGS=-L/opt/ports/lib -framework OpenGL -lglfw -lGLEW -lm
else
LDFLAGS=-lX11 -lGL -lGLU lglfw -lGLEW -lm
endif
CC = gcc
CFLAGS=-g -Wall -I/opt/ports/include
all: 
	gcc $(CFLAGS)  $(LDFLAGS)  func.c main.c -o t
clean:
	rm t
	rm -r t.dSYM