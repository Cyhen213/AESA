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
double ***overlap(int d1,int d2,int d3,double ***Cube,double ***nextState);
double **fCFAR(int d1,int d2,double **input_matrix);
double *geomean(int d1,int d2,double **input_matrix);
double *arithmean(int d1,int d2,double **input_matrix);
double *md(int d1,int d2,double **input_matrix);

double normCfa(double m,double a,double l,double e);
double **fCFAR(int d1,int d2,double **input_matrix);


#endif /* AESA_h */
