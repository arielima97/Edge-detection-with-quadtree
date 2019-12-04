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

double getAreaAverage(unsigned char* img, tPonto BottomLeft, tPonto TopRight)
{
	double total = 0;
	unsigned long count = 0;
	for(int j = BottomLeft.y; j<= TopRight.y; j++)
	{
		for (int i = BottomLeft.x; i <= TopRight.x; i++)
		{
			count++;
			total += getPixel(img, i, j);  
		}		
	}
	printf("Av: %lf\n", total / count);
	return total / count;
}

void drawBorder(unsigned char* img, tPonto BottomLeft, tPonto TopRight)
{
	for(int k = BottomLeft.y; k <= TopRight.y; k++)
	{
		setPixel(img, BottomLeft.x, k, 127);
		setPixel(img, TopRight.x, k, 127);
	}
	for(int k = BottomLeft.x; k <= TopRight.x; k++)
	{
		setPixel(img, k, BottomLeft.y, 127);
		setPixel(img, k, TopRight.y, 127);
	}
}
void getBorderQuadtree(quadtree* root, unsigned char* img)
{
	if(root)
	{
		drawBorder(img, root->BottomLeft, root->TopRight);
		printf("level = %d\n", root->Depth);
		getBorderQuadtree(root->BL, img);
		getBorderQuadtree(root->BR, img);
		getBorderQuadtree(root->TL, img);
		getBorderQuadtree(root->TR, img);
	}
}

void SearchEdges(quadtree* root)
{	
	double avr = getAreaAverage(image, root->BottomLeft, root->TopRight);
	double q_size = size_quadtree(root);
	printf("Size: %d\n", q_size);
	if(q_size > 15 & (avr > 2.0 & avr < 253.0))
	{
		split_quadtree(root);
		SearchEdges(root->BL);
		SearchEdges(root->BR);
		SearchEdges(root->TL);
		SearchEdges(root->TR);
	}
}

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
	quadtree Q;
	tPonto p0, p1;
	p0.x = 0;
	p0.y = 0;
	p1.x = iWidth - 1;
	p1.y = iHeight - 1;
	init_quadtree(&Q, p0, p1);
	
	SearchEdges(&Q);

	getBorderQuadtree(&Q, image);
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
	char* filename = "images/Twitter.png";

    if (argc > 1)
		filename = argv[1];

	image = leImagem(filename);
			
	criaJanela(argc, argv);

    initOpenGL();
    
    initEventos();
    
    return 0;   
}