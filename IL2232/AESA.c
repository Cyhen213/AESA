//
//  AESA.c
//  IL2232
//
//  Created by gaogao on 2022-10-13.
//
#include <math.h>
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
//geomean 对矩阵操作，要用farm11_2d扩展   但是不需要。因为这里再geomean中包含了一个reduce操作，直接写geomean会更简单
//arithmean 和上面同理。
int *geomean(int d1,int d2,int **input_matrix)
{
  int *reduced_vector=reduceV2d(d1, d2, addV, input_matrix);
  int *result=farm11_1d(logBase2_div4, reduced_vector, d2);
  return result;
}
int *arithmean(int d1,int d2,int **input_matrix)
{
  int ***grouped_result=group2d(d1, d2, input_matrix, 2);//(actual is 4 2 for demostration purpose)
  int **temp_result_1=(int **) malloc (d1/2*sizeof(int *));
  //(actual is 4 2 for demostration purpose)
  for(int i=0;i<d1/2;i++)
  {
    temp_result_1[i]=(int *) malloc (d2*sizeof(int));
  }
  for(int i=0;i<d1/2;i++)
  {
    temp_result_1[i]=geomean(d1/2, d2, grouped_result[i]);
    //(actual is 4 2 for demostration purpose)
  }//every grouped vector is translated
  //into a local sum
  int *temp_result_2=reduceV2d(d1/2,d2,addV,temp_result_1);
  //a dimension reduction
  int *result=farm11_1d(div_N,temp_result_2,d2);
  //div a param N for the vecs
  return result;
}
int *md(int d1,int d2,int **input_matrix)
{
  int *result=(int *) malloc (d2*sizeof(int));
  result=reduceV2d(d1, d2, minimumVec, input_matrix);
  return result;
}
//对md需要做一个升维才能一起运算。
int normCfa(int m,int a,int l,int e)
{
  int find_max=m;
  if(find_max<l)
  {
    find_max=l;
  }
  else if(find_max<e)
  {
    find_max=e;
  }
  int result=pow(2,(5+log2(a-find_max)));
  return result;
}

int **fCFAR(int d1,int d2,int **input_matrix)
{
  int **result=(int **) malloc (d1*sizeof(int *));
  for(int i=0;i<d1;i++)
  {
    result[i]=(int *) malloc (d2*sizeof(int));
  }
  int **find_max=(int **) malloc (d1*sizeof(int *));
  for(int i=0;i<d1;i++)
  {
    find_max[i]=(int *) malloc (d2*sizeof(int));
  }
  
  int ***neighbors=stencil2d(d1, d2, input_matrix, 4);//stencil parameter, in model is set to be 4
  int **arithm=(int **) malloc ((d1-4+1)*sizeof(int *));
  for(int i=0;i<(d1-4+1);i++)
  {
    arithm[i]=(int *) malloc (d2*sizeof(int));
  }
  for(int i=0;i<(d1-4+1);i++)
  {
    arithm[i]=arithmean(4, d2, neighbors[i]);
  }
  int *minimum_result=md(d1, d2, input_matrix);
  int **repeated_minimum=fanoutn2d(minimum_result, d2, d1);
  int **dummy_emv=fanoutn2d(fanoutn1d(-100, d2), d2, 3);//3=d1-(d1-4+1)
  int **dummy_lmv=fanoutn2d(fanoutn1d(-100, d2), d2, 3+2);//3=d1-(d1-4+1)+(drop 2)
  int **lmv=concate2d_mat((d1-4+1-2),5, d2, drop2d((d1-4+1), d2, arithm, 2), dummy_lmv);
  int **emv=concate2d_mat(3, (d1-4+1), d2, dummy_emv, arithm);
  result=farm41_2d(normCfa, d1, d2, repeated_minimum, input_matrix, lmv, emv);
  
  return result;
}
