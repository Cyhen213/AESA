//
//  AESA.h
//  IL2232
//
//  Created by gaogao on 2022-10-13.
//

#ifndef AESA_h
#define AESA_h

#include <stdio.h>
#include "skeletons.h"
int ***overlap(int d1,int d2,int d3,int ***Cube,int ***nextState);
int ***StateUpdate(int d1,int d2,int d3,int ***inputCube);

#endif /* AESA_h */
