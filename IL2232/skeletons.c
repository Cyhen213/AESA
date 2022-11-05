//
//  skeletons.c
//  IL2232
//
//  Created by gaogao on 2022-10-12.
//
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define N 1
//print function
//allocate dynamic space for a input cube
int ***allocate_cube(int d1,int d2,int d3)
{
  int ***result=(int ***) malloc (d1*sizeof(int **));
  for(int i=0;i<d1;i++)
  {
    result[i]=(int **) malloc (d2*sizeof(int *));
  }
  for(int i=0;i<d1;i++)
  {
    for(int j=0;j<d2;j++)
    {
      result[i][j]=(int *) malloc (d3*sizeof(int));
    }
  }
  return result;
}

int ***allocate_cube_from_cube(int d1,int d2,int d3,int cube[d1][d2][d3])
{
  int ***result=(int ***) malloc (d1*sizeof(int **));
  for(int i=0;i<d1;i++)
  {
    result[i]=(int **) malloc (d2*sizeof(int *));
  }
  for(int i=0;i<d1;i++)
  {
    for(int j=0;j<d2;j++)
    {
      result[i][j]=(int *) malloc (d3*sizeof(int));
    }
  }
  for(int i=0;i<d1;i++)
  {
    for(int j=0;j<d2;j++)
    {
      for(int k=0;k<d3;k++)
      {
        result[i][j][k]=cube[i][j][k];
      }
    }
  }
  return result;
}
void free_cube(int d1,int d2,int d3,int ***cube)
{
  for (int i = 0; i < d1; i++){
      for (int j = 0; j < d2; j++){
          free(cube[i][j]);
      }
      free(cube[i]);
  }
  free(cube);
}
void print_array(int *array, int length)
{
  for(int i=0;i<length;i++)
  {
    printf("%d  ", *(array+i));
  }
}
void print_cube(int d1,int d2,int d3,int ***cube)
{
  for (int i = 0; i < d1; i++){
      for (int j = 0; j < d2; j++){
          for (int k = 0; k < d3; k++){
              printf("%d ", cube[i][j][k]);
          }
          printf("\n");
      }
      printf("\n");
  }
}

//concate two arrays
//implementation of <++>
int *concate1d(int *array1, int *array2, int array_len)
{
  int *result=(int *) malloc ((array_len)*sizeof(int));

  for(int j=0;j<array_len;j++)
  {
    if(j<array_len) {result[j]=array1[j];}
    else {result[j]=array2[j-array_len];}
  }
  return result;
}
int **concate2d_mat(int d1_mat1, int d1_mat2, int d2, int **input_matrix1, int **input_matrix2)
{
  int **result=(int **) malloc ((d1_mat1+d1_mat2)*sizeof(int *));
  for(int i=0;i<(d1_mat1+d1_mat2);i++)
  {
    result[i]=(int *) malloc (d2*sizeof(int));
  }
  for(int i=0;i<(d1_mat1+d1_mat2);i++)
  {
    for(int j=0;j<d2;j++)
    {
      if(i<d1_mat1){
        result[i][j]=input_matrix1[i][j];
      }
      else result[i][j]=input_matrix2[i-d1_mat1][j];
    }
  }
  return result;
}
int ***concate3d_cube(int d1,int d2,int d3,int ***array1, int ***array2)
{
//  description: In this case, the d1,d2,d3 for array2 and array1 are the same
//  d1 in the "cut" cube is half of the input cube
  int ***result=(int ***) malloc (2*d1*sizeof(int **));
  for(int i=0;i<2*d1;i++)
  {
    result[i]=(int **) malloc (d2*sizeof(int *));
  }
  for(int i=0;i<2*d1;i++)
  {
    for(int j=0;j<d2;j++)
    {
      result[i][j]=(int *) malloc (d3*sizeof(int));
    }
  }
  for(int i=0;i<2*d1;i++)
  {
    for(int j=0;j<d2;j++)
    {
      for(int k=0;k<d3;k++)
      {
        if(i<d1){result[i][j][k]=array1[i][j][k];}
        else{result[i][j][k]=array2[i-d1][j][k];}
      }
    }
  }
  return result;
}


//take n elements from an input array
int *take1d(int *input_array, int take_n)
{
  int *result=(int *) malloc (take_n*sizeof(int));
  for(int i=0;i<take_n;i++)
  {
    result[i]=input_array[i];
  }
  return result;
}

int ***take3d(int d1,int d2,int d3,int ***input_cube, int take_n)
{
  int ***result=(int ***) malloc (take_n*sizeof(int **));
  for(int i=0;i<take_n;i++)
  {
    result[i]=(int **) malloc (d2*sizeof(int *));
  }
  for(int i=0;i<take_n;i++)
  {
    for(int j=0;j<d2;j++)
    {
      result[i][j]=(int *) malloc (d3*sizeof(int));
    }
  }
  for(int i=0;i<take_n;i++)
  {
    for(int j=0;j<d2;j++)
    {
      for(int k=0;k<d3;k++)
      {
        result[i][j][k]=input_cube[i][j][k];
      }
    }
  }
  return result;
}
//drop n elements from an input array
int *drop1d(int *input_array, int array_len, int drop_n)
{
  int *result=(int *) malloc ((array_len-drop_n)*sizeof(int));

  for(int i=0;i<array_len-drop_n;i++)
  {
    result[i]=input_array[array_len-drop_n+i];
  }
  return result;
}
int **drop2d(int d1,int d2,int **input_matrix,int drop_n)
{
  int **result=(int **) malloc ((d1-drop_n)*sizeof(int *));
  for(int i=0;i<d1-drop_n;i++)
  {
    result[i]=(int *) malloc (d2*sizeof(int));
  }
  for(int i=drop_n;i<d1;i++)
  {
    for(int j=0;j<d2;j++)
    {
      result[i-drop_n][j]=input_matrix[i][j];
    }
  }
  return result;
}

int ***drop3d(int d1,int d2,int d3,int ***input_cube, int drop_n)
{
  int ***result=(int ***) malloc ((d1-drop_n)*sizeof(int **));
  for(int i=0;i<(d1-drop_n);i++)
  {
    result[i]=(int **) malloc (d2*sizeof(int *));
  }
  for(int i=0;i<(d1-drop_n);i++)
  {
    for(int j=0;j<d2;j++)
    {
      result[i][j]=(int *) malloc (d3*sizeof(int));
    }
  }
  for(int i=drop_n;i<d1;i++)
  {
    for(int j=0;j<d2;j++)
    {
      for(int k=0;k<d3;k++)
      {
        result[i-drop_n][j][k]=input_cube[i][j][k];
      }
    }
  }
  return result;
}
//repeat a value n times and store in an array
int *fanoutn1d(int input_value, int n_times)
{
  int *result=(int *) malloc ((n_times)*sizeof(int));

  for(int i=0;i<n_times;i++)
  {
    result[i]=input_value;
  }
  return result;
}
int **fanoutn2d(int *input_array, int array_length, int n_times)
{
  int **result=(int **) malloc (n_times*sizeof(int *));
  for(int i=0;i<n_times;i++)
  {
    result[i]=(int *) malloc (array_length*sizeof(int));
  }
  for(int i=0;i<n_times;i++)
  {
    for(int j=0;j<array_length;j++)
    {
      result[i][j]=input_array[j];
    }
  }
  return result;
}
int ***fanoutn3d(int **input_matrix, int d1, int d2, int n_times)
{
  int ***result=(int ***) malloc (n_times*sizeof(int **));
  for(int i=0;i<d1;i++)
  {
    result[i]=(int **) malloc (d1*sizeof(int *));
  }
  for(int i=0;i<n_times;i++)
  {
    for(int j=0;j<d1;j++)
    {
      result[i][j]=(int *) malloc (d2*sizeof(int));
    }
  }
  for(int i=0;i<n_times;i++)
  {
    for(int j=0;j<d1;j++)
    {
      for(int k=0;k<d2;k++)
      {
        result[i][j][k]=input_matrix[i][j];
      }
    }
  }
  return result;
}
//farm11
int *farm11_1d(int (*operation)(int), int *input_array, int array_len)
{
  int *result=(int *) malloc ((array_len)*sizeof(int));

  for(int i=0;i<array_len;i++)
  {
    result[i]=operation(*(input_array+i));
  }
  return result;
}

int **farm11_2d(int **(*operation)(int,int,int **), int d1,int d2,int **input_matrix)
{
  int **result=(int **) malloc (d1*sizeof(int));
  for(int i=0;i<d1;i++)
  {
    result[i]=(int *) malloc (d2*sizeof(int));
  }

  result=operation(d1,d2,input_matrix);
  return result;
}

//farm21
int *farm21_1d(int (*operation)(int,int), int *input_array1, int *input_array2, int array_len)
{
  int *result=(int *) malloc ((array_len)*sizeof(int));
  for(int i=0;i<array_len;i++)
  {
    result[i]=operation(*(input_array1+i),*(input_array2+i));
  }
  return result;
}

int **farm41_2d(int (*operation)(int,int,int,int),int d1,int d2,int **input_matrix1,int **input_matrix2,int **input_matrix3,int **input_matrix4)
{
  int **result=(int **) malloc (d1*sizeof(int*));
  for(int i=0;i<d1;i++)
  {
    result[i]=(int *) malloc (d2*sizeof(int));
  }
  for(int i=0;i<d1;i++)
  {
    for(int j=0;j<d2;j++)
    {
      result[i][j]=operation(input_matrix1[i][j],input_matrix2[i][j],input_matrix3[i][j],input_matrix4[i][j]);
    }
  }
  return result;
}

int ***group2d(int d1,int d2,int **input_matrix,int num)
{
  int ***result=allocate_cube(d1/num,num,d2);
  for(int i=0;i<d1/num;i++)
  {
    for(int j=0;j<num;j++)
    {
      for(int k=0;k<d2;k++)
      {
        result[i][j][k]=input_matrix[i*num+j][k];
      }
    }
  }
  return result;
}

int *reduce1d(int (*operation)(int, int), int array_len, int *input_array)
{
  int *result=(int *) malloc ((1)*sizeof(int));

  *result=operation(*input_array,*(input_array+1));
  for(int i=2;i<array_len;i++)
  {
    *result=operation(*result,*(input_array+i));
  }
  return result;
}
int *reduceV2d( int d1,int d2,int *(*operation)(int*, int*,int d2),int **input_matrix)
{
  int *result=(int *) malloc (d2*sizeof(int));
  for(int i=0;i<d1;i++){
    result=operation(input_matrix[0],input_matrix[1],d2);
  }
  for(int i=2;i<d1;i++){
      result=operation(result,input_matrix[i],d2);
  }
  return result;
}
//reduceVector 3d （对于三维数据cube储存的每一个一维向量操作得到二维矩阵）
int **reduceV3d(int d1,int d2,int d3, int *(*operation)(int*, int*,int d3),int ***input_cube)
{
  int **result=(int **) malloc (d1*sizeof(int *));
  for(int i=0;i<d1;i++){
    result[i]=operation(input_cube[i][0],input_cube[i][1],d3);
  }
  for(int i=0;i<d1;i++){
    for(int j=2;j<d2;j++){
      result[i]=operation(result[i],input_cube[i][j],d3);
    }
  }
  return result;
}

int ***stencil2d(int in_d1, int in_d2, int **a, int stencil_length)
{
    int d1 = in_d1 - stencil_length + 1;
    int d2 = stencil_length;
    int d3 = in_d2;
    int *** result = (int ***) malloc (d1 * sizeof(int **));
    for (int i = 0; i < d1; i++){
      result[i] = (int **) malloc (d2 * sizeof(int*));
    }
    for (int i = 0; i < d1; i++){
        for (int j = 0; j < d2; j++){
          result[i][j] = (int *) malloc (d3 * sizeof(int));
        }
    }
    for (int i = 0; i < d1; i++){
        for (int j = 0; j < d2; j++){
            for (int k = 0; k < d3; k++){
              result[i][j][k] = a[i + j][k];
            }
        }
    }
    return result;
}
//void stencil(int (*input_matrix)[], int matrix_row, int matrix_col, int *result)
//{
//  //description:  input a 2D array, and calculate how many elements expected to be given out. Then iterate to assign the values
//  
//}


//simple example for farm
//description
//functions below are the concrete compute operations can be passed to farm
int add(int input1, int input2)
{
  return input1+input2;
}

int add_one(int input)
{
  return input+1;
}
int *addV(int *inputVector1,int *inputVector2,int len_array)
{
  int *result=farm21_1d(add, inputVector1, inputVector2, len_array);
  return result;
}
int minimum(int num1,int num2)
{
  if(num1<num2) {return num1;}
  else return num2;
}

int *minimumVec(int *inputV1,int *inputV2 ,int d2)
{
  int *result=farm21_1d(minimum,inputV1,inputV2, d2);
  return result;
}

int logBase2_div4(int input)
{
//  printf("%f   ",log2(input/4));
  return log2(input/4);
}
int div_N(int input)
{
  return input/N;
}
