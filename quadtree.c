#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "quadtree.h"

quadtree* allocate_quadtree(tPonto _BottomLeft, tPonto _TopRight, int _Depth)
{
    quadtree* new_item = (quadtree*) malloc(sizeof(quadtree));
    new_item->BottomLeft = _BottomLeft;
    new_item->TopRight = _TopRight;
    new_item->Depth = _Depth;
    new_item->TL = NULL;
    new_item->TR = NULL;
    new_item->BL = NULL;
    new_item->BR = NULL;    
    return new_item;
}

void init_quadtree(quadtree* root, tPonto _BottomLeft, tPonto _TopRight)
{
    quadtree* new_item = allocate_quadtree(_BottomLeft, _TopRight, 0);
    *root = *new_item;
}

void info_quadtree(quadtree* r)
{
    printf("_BottomLeft = (%d, %d) | TopRight = (%d, %d) | Depth = %d\n", r->BottomLeft.x, r->BottomLeft.y, r->TopRight.x, r->TopRight.y, r->Depth);
}

void split_quadtree(quadtree* r)
{   
    tPonto BL0, BL1;
    BL0 = r->BottomLeft;
    BL1.x = (r->TopRight.x + r->BottomLeft.x) / 2;
    BL1.y = (r->TopRight.y + r->BottomLeft.y) / 2;
    r->BL = allocate_quadtree(BL0, BL1, r->Depth + 1);

    tPonto TR0, TR1;
    TR0 = BL1;
    TR1 = r->TopRight;
    r->TR = allocate_quadtree(TR0, TR1, r->Depth + 1);

    tPonto BR0, BR1;
    BR0.x = BL1.x;
    BR0.y = BL0.y;
    BR1.x = TR1.x;
    BR1.y = TR0.y;
    r->BR = allocate_quadtree(BR0, BR1, r->Depth + 1);

    tPonto TL0, TL1;
    TL0.x = BL0.x;
    TL0.y = BL1.y;
    TL1.x = BL1.x;
    TL1.y = TR1.y;
    r->TL = allocate_quadtree(TL0, TL1, r->Depth + 1);
}

int size_quadtree(quadtree* r)
{
    return (r->TopRight.x - r->BottomLeft.x) * (r->TopRight.y - r->BottomLeft.y);
}