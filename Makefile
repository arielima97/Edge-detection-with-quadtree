.c.o:   $*.h
	gcc -c $*.c -I./external/SOIL/inc

.cpp.o:	$*.h
	g++	-c $*.cpp -I./external/SOIL/inc

all:	vetoriza

vetoriza:  vetoriza.o winGL.o 
	g++ -o $@ $^ -L./external/SOIL/lib -lglut -lGL -lGLU -lsoil

clean:
	rm *.o *.*~ *~ vetoriza