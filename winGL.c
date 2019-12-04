#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <GL/glut.h>

#include "winGL.h"
#include "vetoriza.h"
#include "SOIL/SOIL.h"

extern int 	iHeight, 
			iWidth,
			iChannels;
		
						
/// ***********************************************************************
/// ** 
/// ***********************************************************************

void revertImage(unsigned char* img, int w, int h) {

	unsigned char 	aux;
	int 			i,
					j;
	
	if (img == NULL)
		return;

	for (j = 0 ; j < h / 2 ; j++) 
		for (i = 0 ; i < w ; i++) {
			aux 			 	= img[j*w+i]; 
			img[j*w+i] 		 	= img[(h-j-1)*w+i];
			img[(h-j-1)*w+i] 	= aux;
			}				
}

/// ***********************************************************************
/// ** 
/// ***********************************************************************

unsigned char* leImagem(char* filename) {
	
	unsigned char 	*image 	= NULL;
	
	image = SOIL_load_image (filename, &iWidth, &iHeight, &iChannels, SOIL_LOAD_L);
	
    if (image == NULL) {
    	printf("Erro carregando imagem %s\n", filename);
    	exit(0);
    	}
    
	printf("Imagem 		=> %s\n", filename);
	printf("Resolucao 	=> %d x %d\n", iHeight, iWidth);
	printf("Channels 	=> %d\n", iChannels);

	revertImage(image, iWidth, iHeight);

    return image;	
}
						
/// ***********************************************************************
/// ** 
/// ***********************************************************************

void desenhaQuadrante(tPonto p0, tPonto p1, unsigned char c) {
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	glColor3ub(c,c,c);
    glBegin(GL_QUADS);
		glVertex2f(p0.x, p0.y);
		glVertex2f(p1.x, p0.y);
		glVertex2f(p1.x, p1.y);
		glVertex2f(p0.x, p1.y);
    glEnd(); 

}

/// ***********************************************************************
/// ** 
/// ***********************************************************************

void initOpenGL (void) {
	glClearColor(0.0, 0.0, 0.0, 0.0); 
	glShadeModel(GL_FLAT);
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1);
}

/// ***********************************************************************
/// ** 
/// ***********************************************************************

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0.0, w, 0.0, h);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

/// ***********************************************************************
/// ** 
/// ***********************************************************************

void criaJanela(int argc, char** argv) {
	
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (iWidth, iHeight);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Quadtree - Estrutura de Dados");
}


/// ***********************************************************************
/// ** 
/// ***********************************************************************

void initEventos() {
	
    glutDisplayFunc(desenho);
    glutKeyboardFunc(teclado);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	
	glutMainLoop();
}


