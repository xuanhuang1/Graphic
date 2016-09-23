all:
	gcc -g -Wall -I/opt/ports/include  -L/opt/ports/lib -framework OpenGL -lglfw -lGLEW -lm  objects.c main.c  -o project

clean:
	rm -f *.o project 
	rm -r project.dSYM
