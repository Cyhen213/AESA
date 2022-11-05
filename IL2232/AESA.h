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
int **fCFAR(int d1,int d2,int **input_matrix);
int *geomean(int d1,int d2,int **input_matrix);
int *arithmean(int d1,int d2,int **input_matrix);
int *md(int d1,int d2,int **input_matrix);

int normCfa(int m,int a,int l,int e);
int **fCFAR(int d1,int d2,int **input_matrix);


#endif /* AESA_h */
