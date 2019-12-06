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
char* 			filename; 
int show_mode = 0;
double precision = 1;
/// ***********************************************************************
/// ** FUNÇÕES AUXILIARES
/// ***********************************************************************


// **********************************
// ****** Coleta a cor do pixel
// **********************************
unsigned char getPixel(unsigned char* img, int x, int y)
{
	if(y >= iHeight || y < 0 || x >= iWidth || x < 0)
	{
		printf("Out of range.\n");
		return 0;	
	}
	return img[y*iHeight+x];
}

// **********************************
// ****** Determina a cor do pixel
// **********************************
void setPixel(unsigned char* img, int x, int y, unsigned char value)
{
	if(y >= iHeight || y < 0 || x >= iWidth || x < 0)
	{
		printf("Out of range.\n");
		return 0;	
	}
	img[y*iHeight+x] = value;
}

// **********************************************************************************************************
// ****** Calcula média das cores do quadrante delimitado pelos pontos inferior esquerdo e superior direito
// **********************************************************************************************************
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
	return total / count;
}

// ************************************************************************************************
// ****** Desenha borda do quadrante delimitado pelos pontos inferior esquerdo e superior direito
// ************************************************************************************************
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

// **********************************************************************************
// ****** Desenha quadrantes da quadtree - algoritmo de pré-ordem
// **********************************************************************************
void drawBorderQuadtree(quadtree* root, unsigned char* img)
{
	if(root)
	{
		drawBorder(img, root->BottomLeft, root->TopRight);
		drawBorderQuadtree(root->BL, img);
		drawBorderQuadtree(root->BR, img);
		drawBorderQuadtree(root->TL, img);
		drawBorderQuadtree(root->TR, img);
	}
}

// **********************************************************************************
// ****** Preenche uma região entre os pontos inferior esquerdo e superior direito
// **********************************************************************************
void drawRegion(unsigned char* img, tPonto BottomLeft, tPonto TopRight, unsigned char color)
{
	for(int j = BottomLeft.y; j<= TopRight.y; j++)
		for (int i = BottomLeft.x; i <= TopRight.x; i++)
			setPixel(img, i, j, color); 
}

// *************************************************************
// ****** Desenha os pixels das bordas baseado na quadtree
// *************************************************************
void drawEdges(quadtree* root, unsigned char* img, char color, int resolution)
{
	if(root)
	{
		if(size_quadtree(root) <= resolution)
			drawRegion(img, root->BottomLeft, root->TopRight, color);
		else
		{
			drawEdges(root->BL, img, color, resolution);
			drawEdges(root->BR, img, color, resolution);
			drawEdges(root->TL, img, color, resolution);
			drawEdges(root->TR, img, color, resolution);
		}			
	}
}

// ********************************************************************************************************
// ****** Procura quadrantes em que a média seja diferente de preto ou branco e cria mais 4 sub quadrantes
// ********************************************************************************************************
void SearchEdges(unsigned char* img, quadtree* root, int resolution)
{	
	double avr = getAreaAverage(img, root->BottomLeft, root->TopRight);
	double q_size = size_quadtree(root);
	if(q_size > resolution & (avr > 0.0 & avr < 255.0))
	{
		split_quadtree(root);
		SearchEdges(img, root->BL, resolution);
		SearchEdges(img, root->BR, resolution);
		SearchEdges(img, root->TL, resolution);
		SearchEdges(img, root->TR, resolution);
	}
}

// **********************************
// ****** Imagem em negativo
// **********************************
void negativaImage(unsigned char* img, int w, int h) 
{
	int 			i,
					j;
	
	if (img == NULL)
		return;

	for (j = 0 ; j < h ; j++) 
		for (i = 0 ; i < w ; i++) 
			setPixel(img, i, j, 255 - getPixel(img, i, j)); 
}

// ********************************************************************
// ****** DESENHA VETORIZAÇÃO BASEADO NO MODO ESCOLHIDO PELO USUÁRIO
// ********************************************************************

void desenhaVetorizacao(int mode) {
	quadtree Q;
	tPonto p0, p1;
	p0.x = 0;
	p0.y = 0;
	p1.x = iWidth - 1;
	p1.y = iHeight - 1;
	unsigned char* x = leImagem(filename, false);
	switch (mode)
	{
	case 1:
		printf("Visualizando os quadrantes da quadtree. Tamanho da borda: %d.\n", (int)precision);
		unsigned char* img_squares;
		img_squares = leImagem(filename, false);
		init_quadtree(&Q, p0, p1);
		SearchEdges(img_squares, &Q, (int) precision);
		drawBorderQuadtree(&Q, img_squares);
		glDrawPixels( iWidth, iHeight, GL_LUMINANCE, GL_UNSIGNED_BYTE, img_squares );
		break;
	case 2:
		printf("Visualiza vetorização com fundo preto. Tamanho da borda: %d.\n", (int)precision);
		init_quadtree(&Q, p0, p1);
		SearchEdges(x, &Q, (int) precision);
		for (int j = 0; j < iHeight; j++)
			for (int i = 0; i < iWidth; i++)
				setPixel(x, i, j, 0);
		drawEdges(&Q, x, 255, (int) precision);
		glDrawPixels( iWidth, iHeight, GL_LUMINANCE, GL_UNSIGNED_BYTE, x );
		break;
	case 3:
		printf("Visualiza vetorização com fundo branco. Tamanho da borda: %d.\n", (int)precision);
		init_quadtree(&Q, p0, p1);
		SearchEdges(x, &Q, (int) precision);
		drawEdges(&Q, x, 127, (int) precision);
		glDrawPixels( iWidth, iHeight, GL_LUMINANCE, GL_UNSIGNED_BYTE, x );
		break;
	default:
		break;
	}
	
}
	
/// ***********************************************************************
/// ** SELECIONA FUNÇÃO
/// ***********************************************************************

void teclado(unsigned char key, int x, int y) {

	switch (key) {
		case 27		: 	exit(0);
						break;
		case '1'	:	// Visualiza quadrantes da quadtree.
						show_mode = 1;
						desenha = 1;
						break;				
		case '2'	:	// Vetoriza a imagem e exibe as bordas - fundo preto.
					 	show_mode = 2;
						desenha = 1;
						break;				
		case '3'	:	// Vetoriza a imagem e exibe as bordas - fundo branco borda cinza.
						show_mode = 3;
						desenha = 1;
						break;
		case '+'	:	// Aumenta o tamanho da borda.
						precision *= 1.5;
						if(precision > 10000)
							precision = 10000;
						desenha = 1;
						break;
		case '-'	:	// Diminui o tamanho da borda.
						precision /= 1.5;
						if(precision < 1)
							precision = 1;
						desenha = 1;
						break;									
		case 'q'	:	// Visualiza imagem original.
		case 'Q'	: 	desenha = !desenha;
						break;		
		}
	glutPostRedisplay();
}

void mouse(int button, int button_state, int x, int y ) {

	if 	(button_state == GLUT_DOWN ) {
		glutPostRedisplay();
		}
}

void desenho(void) {

    glClear (GL_COLOR_BUFFER_BIT); 
    
    glColor3f (1.0, 1.0, 1.0);
    
    if (desenha)
    	desenhaVetorizacao(show_mode);
    else
    	glDrawPixels( iWidth, iHeight, GL_LUMINANCE, GL_UNSIGNED_BYTE, image );
   	
    glutSwapBuffers ();
}

int main(int argc, char** argv) {
	filename = "images/Twitter.png";
	
    if (argc > 1)
		filename = argv[1];

	image = leImagem(filename, true);

	// Instruções
	printf("\n- Pressione 1 para visualizar a estrutura quadtree na imagem.\n");
	printf("\n- Pressione 2 para visualizar as bordas com o fundo preto.\n");
	printf("\n- Pressione 3 para visualizar as bordas com o fundo branco.\n");
	printf("\n- Pressione Q para visualizar as bordas com o fundo branco.\n");
	printf("\n- Pressione + para aumentar tamanho da borda.\n");
	printf("\n- Pressione - para aumentar tamanho da borda.\n");		
	criaJanela(argc, argv, "Quadtree - Estrutura de dados");

    initOpenGL();
    
    initEventos();
    
    return 0;   
}