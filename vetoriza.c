#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "quadtree.h"
#include <GL/glut.h>

#include "Ponto.h"
#include "winGL.h"
		
unsigned char* 	image = NULL;	// image file
int 			iHeight, 
				iWidth,
				iChannels;

bool 			desenha = false;

/// ***********************************************************************
/// ** 
/// ***********************************************************************

unsigned char getPixel(unsigned char* img, int x, int y)
{
	if(y >= iHeight || y < 0 || x >= iWidth || x < 0)
	{
		printf("Out of range.\n");
		return 0;	
	}
	return img[y*iHeight+x];
}

void setPixel(unsigned char* img, int x, int y, unsigned char value)
{
	if(y >= iHeight || y < 0 || x >= iWidth || x < 0)
	{
		printf("Out of range.\n");
		return 0;	
	}
	img[y*iHeight+x] = value;
}

double getAreaAverage(unsigned char* img, tPonto TopLeft, tPonto BottomRight)
{
	double total = 0;
	unsigned long count = 0;
	for(int j = TopLeft.y; j<= BottomRight.y; j++)
	{
		for (int i = TopLeft.x; i <= BottomRight.x; i++)
		{
			count++;
			total += getPixel(img, i, j);  
			printf("(%d, %d)\n", i, j);
		}		
	}
	return total / count;
}

void draw

void negativaImage(unsigned char* img, int w, int h) {

	unsigned char 	aux;
	int 			i,
					j;
	
	if (img == NULL)
		return;

	for (j = 0 ; j < h ; j++) 
		for (i = 0 ; i < w ; i++) 
			setPixel(img, i, j, 255 - getPixel(img, i, j)); 
}



// ***********************************************
// ******                                   ******
// ***********************************************

void desenhaVetorizacao() {

	printf("Aqui eu vou desenhar o resultado da vetorizacao\n");
	
	// rotina que deve ser implementada para visualizacao da arvore
	// utilize a rotina desenhaQuadrante(p0, p1, cor)
	// fornecendo os pontos inicial e final do quadrante e a sua cor
	// funcao do valor do pixel ou da regiao que voce quer desenhar
	
	tPonto p0, p1;
	 
	p0.x = p0.y = 0;

	p1.x = iWidth/2;
	p1.y = iHeight/2;	
	desenhaQuadrante(p0, p1, 64);

	p0.x = iWidth;
	p0.y = iHeight;
	desenhaQuadrante(p0, p1, 222);

}
	
/// ***********************************************************************
/// ** 
/// ***********************************************************************

void vetorizaImagem() {
	
	printf("Aqui eu vou construir a estrutura base para a vetorizacao\n");
	
	// codifique aqui a sua rotina de montagem da estrutura de dados para suporte a
	// vetorizacao 
	
}
	
/// ***********************************************************************
/// ** 
/// ***********************************************************************

void teclado(unsigned char key, int x, int y) {

	switch (key) {
		case 27		: 	exit(0);
						break;				
		case 'v'	:
		case 'V'	: 	vetorizaImagem();
						break;				
		case 'q'	:
		case 'Q'	: 	desenha = !desenha;
						break;	

		case 'r'	: 	
		case 'R'	: 	negativaImage(image, iHeight, iWidth);
						break;			
		}
	glutPostRedisplay();
}
		
/// ***********************************************************************
/// **
/// ***********************************************************************

void mouse(int button, int button_state, int x, int y ) {

	if 	(button_state == GLUT_DOWN ) {
		switch (button) {
			
			case GLUT_LEFT_BUTTON	: 	
				printf("botao esquerdo?\n");
				tPonto y1, y2;
				y1.x = y1.y = 30;
				y2.x = y2.y = 35;
				printf("%lf\n", getAreaAverage(image,y1, y2));				
				break;
	
			case GLUT_RIGHT_BUTTON	:	
				printf("botao direito?\n");
				break;
			}
		glutPostRedisplay();
		}
}

/// ***********************************************************************
/// ** 
/// ***********************************************************************

void desenho(void) {

    glClear (GL_COLOR_BUFFER_BIT); 
    
    glColor3f (1.0, 1.0, 1.0);
    
    if (desenha)
    	desenhaVetorizacao();
    else
    	glDrawPixels( iWidth, iHeight, GL_LUMINANCE, GL_UNSIGNED_BYTE, image );
   	
    glutSwapBuffers ();
}

/// ***********************************************************************
/// ** 
/// ***********************************************************************

int main(int argc, char** argv) {
	/*
	quadtree x;
	tPonto y1, y2;
	y1.x = y1.y = 0;
	y2.x = y2.y = 511;
	
	init_quadtree(&x,y1, y2);

	y1.x = y1.y = 200;
	y2.x = y2.y = 300;

	x.TR = allocate_quadtree(y1,y2,1);

	info_quadtree(&x);

	info_quadtree(x.TR);
	*/
	char* filename = "images/Twitter.png";

    if (argc > 1)
		filename = argv[1];

	image = leImagem(filename);
			
	criaJanela(argc, argv);

    initOpenGL();
    
    initEventos();
    
    return 0;   
}