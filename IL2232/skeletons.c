//
//  skeletons.c
//  IL2232
//
//  Created by gaogao on 2022-10-12.
//
#include <stdlib.h>
#include <stdio.h>
//print function
//allocate dynamic space for a input cube
int ***allocate_cube(int d1,int d2,int d3,int cube[d1][d2][d3])
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
//有个关于concate的问题，concate升不升维度？  不升吧。 目前在用不升的方法。
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
//farm11
int *farm111d(int (*operation)(int), int *input_array, int array_len)
{
  int *result=(int *) malloc ((array_len)*sizeof(int));

  for(int i=0;i<array_len;i++)
  {
    result[i]=operation(*(input_array+i));
  }
  return result;
}
//farm21
int *farm211d(int (*operation)(int,int), int *input_array1, int *input_array2, int array_len)
{
  int *result=(int *) malloc ((array_len)*sizeof(int));
  for(int i=0;i<array_len;i++)
  {
    result[i]=operation(*(input_array1+i),*(input_array2+i));
  }
  return result;
}

int *reduce1d(int (*operation)(int, int), int *input_array, int array_len)
{
  int *result=(int *) malloc ((1)*sizeof(int));

  *result=operation(*input_array,*(input_array+1));
  for(int i=2;i<array_len;i++)
  {
    *result=operation(*result,*(input_array+i));
  }
  return result;
}

int *** stencil2d(int in_d1, int in_d2, int a [in_d1][in_d2], int stencil_length){
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
