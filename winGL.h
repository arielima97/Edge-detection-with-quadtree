#ifndef __WINGL__
#define __WINGL__ 1

#include "Ponto.h"
#include <stdbool.h>

void 			desenhaQuadrante(tPonto p0, tPonto p1, unsigned char c);

unsigned char* 	leImagem(char* filename, bool show_status);

void 			display(void);

void 			initOpenGL (void);

void 			reshape (int w, int h);

void 			keyboard (unsigned char key, int x, int y);

void 			criaJanela(int argc, char** argv, char* name);

void 			initEventos();

#endif // __WINGL__

