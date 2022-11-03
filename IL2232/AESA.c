//
//  AESA.c
//  IL2232
//
//  Created by gaogao on 2022-10-13.
//

#include "AESA.h"
#include "skeletons.h"
#include <stdio.h>
#include <stdlib.h>
//Used atom functions:
//take(int *input_array, int *result, int take_n);
//concate(int *array1, int *array2, int *result, const int len1, const int len2)
//drop(int *input_array, int *result, int array_len, int drop_n)

int ***overlap(int d1,int d2,int d3,int ***inputCube,int ***nextState)
{
  int ***delayCube=(int ***) malloc (d1/2*sizeof(int **));
  for(int i=0;i<d1/2;i++)
  {
    delayCube[i]=(int **) malloc (d2*sizeof(int *));
  }
  for(int i=0;i<d1/2;i++)
  {
    for(int j=0;j<d2;j++)
    {
      delayCube[i][j]=(int *) malloc (d3*sizeof(int));
    }
  }
  
  int ***newCube=(int ***) malloc (d1*sizeof(int **));
  for(int i=0;i<d1;i++)
  {
    newCube[i]=(int **) malloc (d2*sizeof(int *));
  }
  for(int i=0;i<d1;i++)
  {
    for(int j=0;j<d2;j++)
    {
      newCube[i][j]=(int *) malloc (d3*sizeof(int));
    }
  }
  delayCube=take3d(d1,d2,d3,inputCube,d1/2);
  newCube=concate3d_cube(d1/2,d2,d3,nextState,delayCube);
  int ***temp_result=drop3d(d1,d2,d3,inputCube,d1/2);
  for(int i=0;i<d1/2;i++)
  {
    for(int j=0;j<d2;j++)
    {
      for(int k=0;k<d3;k++)
      {
        nextState[i][j][k]=temp_result[i][j][k];
      }
    }
  }
  return newCube;
}
