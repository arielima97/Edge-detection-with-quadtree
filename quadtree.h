#ifndef __quadtree__
#define __quadtree__ 1
#include "Ponto.h"

typedef struct  tQuadtree{	
    tPonto TopLeft; // Coordenadas do ponto superior esquerdo do quadrante
    tPonto BottomRight; // Coordenadas do ponto inferior direito do quadrante
    int Depth; // Profundidade
    struct quadtree* TL; // Quadrante superior esquerdo
    struct quadtree* TR; // Quadrante superior direito
    struct quadtree* BL; // Quadrante inferior esquerdo
    struct quadtree* BR; // Quadrante inferior direito
} quadtree;					
								
#endif		// ____quadtree____

void init_quadtree(quadtree* root, tPonto _TopLeft, tPonto _BottomRight);
quadtree* allocate_quadtree(tPonto _TopLeft, tPonto _BottomRight, int _Depth);
void info_quadtree(quadtree* x);