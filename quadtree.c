#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "quadtree.h"

quadtree* allocate_quadtree(tPonto _TopLeft, tPonto _BottomRight, int _Depth)
{
    quadtree* new_item = (quadtree*) malloc(sizeof(quadtree));
    new_item->TopLeft = _TopLeft;
    new_item->BottomRight = _BottomRight;
    new_item->Depth = _Depth;
    new_item->TL = NULL;
    new_item->TR = NULL;
    new_item->BL = NULL;
    new_item->BR = NULL;    
    return new_item;
}

void init_quadtree(quadtree* root, tPonto _TopLeft, tPonto _BottomRight)
{
    quadtree* new_item = allocate_quadtree(_TopLeft, _BottomRight, 0);
    *root = *new_item;
}

void info_quadtree(quadtree* x)
{
    printf("TopLeft = (%d, %d) | BottomRight = (%d, %d) | Depth = %d\n", x->TopLeft.x, x->TopLeft.y, x->BottomRight.x, x->BottomRight.y, x->Depth);
}