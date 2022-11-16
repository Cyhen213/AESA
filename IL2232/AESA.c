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
#define NoFFT 256//window
#define Nob 1024 //range
#define NoB 1//beam
#define No2Channel 32
#define NoChannel 16
//Used atom functions:
//take(int *input_array, int *result, int take_n);
//concate(int *array1, int *array2, int *result, const int len1, const int len2)
//drop(int *input_array, int *result, int array_len, int drop_n)

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
//geomean 对矩阵操作，要用farm11_2d扩展   但是不需要。因为这里再geomean中包含了一个reduce操作，直接写geomean会更简单
//arithmean 和上面同理。
double *geomean(int d1,int d2,double **input_matrix)
{
  double *reduced_vector=reduceV2d(d1, d2, addV, input_matrix);
  double *result=farm11_1d(logBase2_div4, reduced_vector, d2);
  //print_array(result, d2);
  free(reduced_vector);
  return result;
}
double *arithmean(int d1,int d2,double **input_matrix)
{
  double ***grouped_result=group2d(d1, d2, input_matrix, 4);//(actual is 4 2 for demostration purpose)
 // print_cube(d1/4, 4, d2, grouped_result);
  double **temp_result_1=(double **) malloc (d1/4*sizeof(double *));
  for(int i=0;i<d1/4;i++)
  {
    temp_result_1[i]=geomean(4, d2, grouped_result[i]);
  }//every grouped vector is translated
  //into a local sum
  double *temp_result_2=reduceV2d(d1/4,d2,addV,temp_result_1);
  //a dimension reduction
  double *result=farm11_1d(div_N,temp_result_2,d2);
  //div a param N for the vecs
  free_cube(d1/4,4,d2, grouped_result);
  free_matrix(d1/4, d2, temp_result_1);
  free(temp_result_2);
  return result;
}
double *md(int d1,int d2,double **input_matrix)
{
  double *result=reduceV2d(d1,d2, minimumVec, input_matrix);
//  print_matrix(d1, d2, input_matrix);
  return result;
}
//对md需要做一个升维才能一起运算。
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

double **fCFAR(int d1,int d2,double **input_matrix)
{
  double ***neighbors=stencil2d(d1, d2, input_matrix, NoFFT);
 // print_cube(9, 8, d2, neighbors);
 // neighbors dimension(d1-NoFFT+1,NoFFT,d2)
  double **arithm=(double **) malloc ((d1-NoFFT+1)*sizeof(double *));
  for(int i=0;i<d1-NoFFT+1;i++)
  {
    arithm[i]=arithmean(NoFFT, d2, neighbors[i]);
  }
  double *minimum_result=md(d1, d2, input_matrix);
  //print_array(minimum_result, d2);
  double **repeated_minimum=fanoutn2d(minimum_result, d2, d1);
  double **dummy_emv=fanoutn2d(fanoutn1d(-100, d2), d2, NoFFT-1);
  double **dummy_lmv=fanoutn2d(fanoutn1d(-100, d2), d2, NoFFT-1+2);
//  print_matrix(d1-NoFFT+1, d2, arithm);
  double **droped_mat=drop2d(d1-NoFFT+1, d2, arithm, 2);
  double **lmv=concate2d_mat(d1-NoFFT+1-2,NoFFT-1+2, d2,droped_mat, dummy_lmv);
 
  double **emv=concate2d_mat(NoFFT-1,d1-NoFFT+1, d2, dummy_emv, arithm);
  double **result=farm41_2d(normCfa, d1, d2, repeated_minimum, input_matrix, lmv, emv);

//  print_matrix(d1, d2, result);
  free_cube(d1-NoFFT+1, NoFFT,d2, neighbors);
  free_matrix(d1-NoFFT+1, d2, arithm);
  free_matrix(d1-NoFFT+1-2, d2, droped_mat);
  free_matrix(d1, d2, repeated_minimum);
  free_matrix(NoFFT-1, d2, dummy_emv);
  free_matrix(NoFFT-1+2, d2, dummy_lmv);

  free_matrix(d1, d2, lmv);
  free_matrix(d1, d2, emv);

//释放内存有问题
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
