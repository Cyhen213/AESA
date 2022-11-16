/**
 * @file AESA.c
 * @author Yuchen
 * @brief 
 * @version 0.1
 * @date 2022-11-16
 * 
 * @copyright Copyright (c) 2022
 * @brief In AESA computation blocks, the assigned useless dynamic spaces need to be released.
 * REMIND: ALL THE SKELETONS FUNCTION AUTOMATICALLY ALLOCATES DYNAMIC SPACE MUST BE RELEASED.
 */
#include <math.h>
#include "AESA.h"
#include "skeletons.h"
#include <stdio.h>
#include <stdlib.h>
#define NoFFT 256//window
#define Nob 1024 //range
#define NoB 1//beam
#define No2Channel 32
#define NoChannel 16
/**
 * @brief 
 * - Overlap function execute the 'mealy machine' pattern.
 * - It delays the input data cube for one state and concate the current state with first half of data cube, storing the last half data cube as next state.
 * @param d1 The dimension of input cube (d1,d2,d3)
 * @param d2 
 * @param d3 
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
 * @param d1 
 * @param d2 
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
 * @param d1 
 * @param d2 
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
 * - Md function computes the smallest value for each position in a vector over the input matrix.
 * @param d1 
 * @param d2 
 * @param input_matrix (d1,d2)
 * @return double* (an array)
 */
double *md(int d1,int d2,double **input_matrix)
{
  double *result=reduceV2d(d1,d2, minimumVec, input_matrix);
  return result;
}
/**
 * @brief
 * - normCfa function is used in the Cfar.
 * - Find the max value between minimum value bin, early arrived bin, late arrived bin.
 * - Do the operation @code pow(2,(5+log2(a-find_max))); @endcode
 * @param m 
 * @param a 
 * @param l 
 * @param e 
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
  double result=pow(2,(5+log2(a-find_max)));
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
 * @param d1 
 * @param d2 
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
  double *minimum_result=md(d1, d2, input_matrix);
  double **repeated_minimum=fanoutn2d(minimum_result, d2, d1);
  double **dummy_emv=fanoutn2d(fanoutn1d(-100, d2), d2, NoFFT-1);
  double **dummy_lmv=fanoutn2d(fanoutn1d(-100, d2), d2, NoFFT-1+2);
  double **droped_mat=drop2d(d1-NoFFT+1, d2, arithm, 2);
  double **lmv=concate2d_mat(d1-NoFFT+1-2,NoFFT-1+2, d2,droped_mat, dummy_lmv);
 
  double **emv=concate2d_mat(NoFFT-1,d1-NoFFT+1, d2, dummy_emv, arithm);
  double **result=farm41_2d(normCfa, d1, d2, repeated_minimum, input_matrix, lmv, emv);

  free_cube(d1-NoFFT+1, NoFFT,d2, neighbors);
  free_matrix(d1-NoFFT+1, d2, arithm);
  free_matrix(d1-NoFFT+1-2, d2, droped_mat);
  free_matrix(d1, d2, repeated_minimum);
  free_matrix(NoFFT-1, d2, dummy_emv);
  free_matrix(NoFFT-1+2, d2, dummy_lmv);

  free_matrix(d1, d2, lmv);
  free_matrix(d1, d2, emv);
  return result;
}
//为什么在aesa里面free操作？
//首先，如果要在主函数中分配储存结果的内存，必须要知道内部函数所用的空间是什么样的。
//会损失延展性，比如在主函数调用result空间分配
//然后传入fcfar，cfar函数中无法得知neighbors的维度
//因此必须在cfar中调用动态内存，再往下追溯一级就是stencil函数的操作应该分配动态内存。
//但是必须要知道，在high level model 中调用了skeletons函数后返回的指针都是动态内存，需要释放。
//在主函数中只需要分配输入矩阵和输出结果的内存并且销毁
//还有一个好处，用户只需要关心输入输出内存空间的分配
//每一个skeleton函数都会分配一块内存空间，在应用层直接初始化指向这些分配空间的指针再进行运算
//运算结束后释放每个skeleton函数分配的空间
