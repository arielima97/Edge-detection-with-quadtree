.c.o:   $*.h
	gcc -c -w $*.c -I./external/SOIL/inc

.cpp.o:	$*.h
	g++	-c -w $*.cpp -I./external/SOIL/inc

all:	vetoriza

vetoriza:  vetoriza.o winGL.o quadtree.o
	g++ -o $@ $^ -L./external/SOIL/lib -lglut -lGL -lGLU -lsoil

clean:
	rm *.o *.*~ *~ vetoriza