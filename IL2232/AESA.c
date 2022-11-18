/**
 * @file AESA.c
 * @author Yuchen
 * @brief 
 * @version 0.1
 * @date 2022-11-16
 * 
 * @copyright Copyright (c) 2022
 * @brief The AESA radar use case.
 * Composed of CFAR and CT.
 * Also their sub systems.
 */
/**
 * @def NoFFT
 * The number of Windows.
 * @def Nob
 * The number of range bins.
 * @def NoB
 * The number of beams.
 * @def No2Channel
 * The number of data channel for real and imagine part in signal.
 * @def NoChannel
 * The number of data channel.
 */
#include <math.h>
#include "AESA.h"
#include "skeletons.h"
#include <stdio.h>
#include <stdlib.h>
#define NoFFT 256
#define Nob 1024
#define NoB 8
#define No2Channel 32
#define NoChannel 16
/**
 * @brief 
 * - Overlap function execute the 'mealy machine' pattern.
 * - It delays the input data cube for one state and concate the current state with first half of data cube, storing the last half data cube as next state.
 * @param d1 The dimension of input cube (d1,d2,d3).
 * @param d2 The second dimension of input cube.
 * @param d3 The third dimension of input cube.
 * @param inputCube (d1,d2,d3)
 * @param nextState (d1/2,d2,d3)
 * @return double*** 
 */
double ***overlap(int d1,int d2,int d3,double ***inputCube,double ***nextState)
{
  double ***delayCube=take3d(d1,d2,d3,inputCube,d1/2);
  double ***newCube=concate3d_cube(d1/2,d2,d3,nextState,delayCube);
  double ***temp_result=drop3d(d1,d2,d3,inputCube,d1/2);
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
  free_cube(d1/2, d2, d3, delayCube);
  free_cube(d1/2,d2,d3,temp_result);
  return newCube;
}
/**
 * @brief 
 * - The Geomean function is used in the Cfar operation.
 * - It computes the vector sum of input matrix, divide the result by 4 and compute the base 2 logarithm of the result.
 * @param d1 first dimension of input matrix.
 * @param d2 second dimension of input matrix.
 * @param input_matrix (d1,d2)
 * @return double* (an array)
 */
double *geomean(int d1,int d2,double **input_matrix)
{
  double *reduced_vector=reduceV2d(d1, d2, addV, input_matrix);
  double *result=farm11_1d(logBase2_div4, reduced_vector, d2);
  free(reduced_vector);
  return result;
}
/**
 * @brief 
 * - Arithmean is a function used in the Cfar.
 * - It firstly group the nearest 4 elements in the matrix.
 * - Next it applies the geomean function on each grouped result generated last step and generate a matrix.
 * - The vector sum of the last step remaining matrix is computed.
 * - Divide the vector sum result by NoFFT generates result of the function.
 * @param d1 first dimension of input matrix.
 * @param d2 second dimension of input matrix.
 * @param input_matrix (d1,d2)
 * @return double* (an array)
 */
double *arithmean(int d1,int d2,double **input_matrix)
{
  double ***grouped_result=group2d(d1, d2, input_matrix, 4);
  double **temp_result_1=(double **) malloc (d1/4*sizeof(double *));
  
  for(int i=0;i<d1/4;i++)
  {
    temp_result_1[i]=geomean(4, d2, grouped_result[i]);
  }
  
  double *temp_result_2=reduceV2d(d1/4,d2,addV,temp_result_1);
  double *result=farm11_1d(div_N,temp_result_2,d2);
  free_cube(d1/4,4,d2, grouped_result);
  free_matrix(d1/4, d2, temp_result_1);
  free(temp_result_2);
  return result;
}
/**
 * @brief 
 * - Md function computes the smallest value in every rangebin over the input matrix.
 * @param d1 first dimension of input matrix.
 * @param d2 second dimension of input matrix.
 * @param input_matrix (d1,d2)
 * @return double** (md matrix)
 */
double **md(int d1,int d2,double **input_matrix)
{
  double **result=(double **) malloc (d1*sizeof(double *));
  for(int i=0;i<d1;i++)
  {
    result[i]=reduce1d(minimum, d2, input_matrix[i]);
  }
  for(int i=0;i<d1;i++)
  {
    result[i]=fanoutn1d(result[i][0], d2);
  }
  double **result_mat=farm11_2d(logBase2, d1, d2, result);
  free_matrix(d1, d2, result);
  return result_mat;
}
/**
 * @brief
 * - normCfa function is used in the Cfar.
 * - Find the max value between minimum value bin, early arrived bin, late arrived bin.
 * - Do the operation @code pow(2,(5+log2(a-find_max))); @endcode
 * @param m Md matrix corresponding position value .
 * @param a The original input matrix corresponding value.
 * @param l The late arriving bin matrix corresponding value.
 * @param e The early arriving bin matrix corresponding value.
 * @return double 
 */
double normCfa(double m,double a,double l,double e)
{
  double find_max=m;
  if(find_max<l)
  {
    find_max=l;
  }
  else if(find_max<e)
  {
    find_max=e;
  }
  double result=pow(2,(5+log2(a)-find_max));
  return result;
}
/**
 * @brief
 * - fCFAR is applied on each matrix inside of data cube.
 * - This operation can be sequential, or paralleled.
 * - Firstly, the input matrix is stenciled so that the nearest NoFFT elements is repeated.
 * - Secondly, the aritmean of each stenciled matrix is computed.
 * - Next, the minimum bin(repeated to (d1,d2)), late bin(d1,d2) and early bin(d1,d2) are computed.
 * - Then apply the normCfa and return the result matrix.
 * @param d1 The first dimension of input matrix for Cfar.
 * @param d2 The second dimension of input matrix for Cfar.
 * @param input_matrix (d1,d2)
 * @return double** (d1,d2)
 */
double **fCFAR(int d1,int d2,double **input_matrix)
{
  double ***neighbors=stencil2d(d1, d2, input_matrix, NoFFT);
  double **arithm=(double **) malloc ((d1-NoFFT+1)*sizeof(double *));
  for(int i=0;i<d1-NoFFT+1;i++)
  {
    arithm[i]=arithmean(NoFFT, d2, neighbors[i]);
  }
  double **md_result=md(d1, d2, input_matrix);
  double **dummy_emv=fanoutn2d(fanoutn1d(-1000, d2), d2, NoFFT-1);
  double **dummy_lmv=fanoutn2d(fanoutn1d(-1000, d2), d2, NoFFT-1+2);
  double **droped_mat=drop2d(d1-NoFFT+1, d2, arithm, 2);
  double **lmv=concate2d_mat(d1-NoFFT+1-2,NoFFT-1+2, d2,droped_mat, dummy_lmv);
  double **emv=concate2d_mat(NoFFT-1,d1-NoFFT+1, d2, dummy_emv, arithm);
  double **result=farm41_2d(normCfa, d1, d2, md_result, input_matrix, lmv, emv);
  free_cube(d1-NoFFT+1, NoFFT,d2, neighbors);
  free_matrix(d1-NoFFT+1, d2, arithm);
  free_matrix(d1-NoFFT+1-2, d2, droped_mat);
  free_matrix(NoFFT-1, d2, dummy_emv);
  free_matrix(NoFFT-1+2, d2, dummy_lmv);
  free_matrix(d1, d2, md_result);
  free_matrix(d1, d2, lmv);
  free_matrix(d1, d2, emv);
  return result;
}
