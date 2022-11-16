//
//  skeletons.c
//  IL2232
//
//  Created by gaogao on 2022-10-12.
//
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define NoFFT 256
//print function
//allocate dynamic space for a input cube
double ***allocate_cube(int d1,int d2,int d3)
{
  double ***result=(double ***) malloc (d1*sizeof(double **));
  for(int i=0;i<d1;i++)
  {
    result[i]=(double **) malloc (d2*sizeof(double *));
  }
  for(int i=0;i<d1;i++)
  {
    for(int j=0;j<d2;j++)
    {
      result[i][j]=(double *) malloc (d3*sizeof(double));
    }
  }
  return result;
}

double ***allocate_cube_from_cube(int d1,int d2,int d3,double cube[d1][d2][d3])
{
  double ***result=(double ***) malloc (d1*sizeof(double **));
  for(int i=0;i<d1;i++)
  {
    result[i]=(double **) malloc (d2*sizeof(double *));
  }
  for(int i=0;i<d1;i++)
  {
    for(int j=0;j<d2;j++)
    {
      result[i][j]=(double *) malloc (d3*sizeof(double));
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
void free_matrix(int d1,int d2,double **matrix)
{
  for(int i=0;i<d1;i++)
  {
    free(matrix[i]);
    matrix[i]=NULL;
  }
  free(matrix);
  matrix=NULL;
  printf("释放一个矩阵\n");

}

void free_cube(int d1,int d2,int d3,double ***cube)
{
  for (int i = 0; i < d1; i++){
      for (int j = 0; j < d2; j++){
          free(cube[i][j]);
        cube[i][j]=NULL;
      }
      free(cube[i]);
    cube[i]=NULL;
  }
  free(cube);
  cube=NULL;
  printf("释放一个数据块\n");

}
void print_array(double *array, int length)
{
  for(int i=0;i<length;i++)
  {
    printf("%f ", array[i]);
  }
  printf("\n");
}
void print_matrix(int d1,int d2,double **matrix)
{
  for (int i = 0; i < d1; i++){
      for (int j = 0; j < d2; j++){
              printf("%f ", matrix[i][j]);
      }
    printf("\n");
  }
}
void print_cube(int d1,int d2,int d3,double ***cube)
{
  for (int i = 0; i < d1; i++){
      for (int j = 0; j < d2; j++){
          for (int k = 0; k < d3; k++){
              printf("%f ", cube[i][j][k]);
          }
        printf("\n");
      }
    printf("\n");
  }
}

//concate two arrays
//implementation of <++>
double *concate1d(double *array1, double *array2, int array_len)
{
  double *result=(double *) malloc ((array_len)*sizeof(double));

  for(int j=0;j<array_len;j++)
  {
    if(j<array_len) {result[j]=array1[j];}
    else {result[j]=array2[j-array_len];}
  }
  return result;
}
double **concate2d_mat(int d1_mat1, int d1_mat2, int d2, double **input_matrix1, double **input_matrix2)
{
  double **result=(double **) malloc ((d1_mat1+d1_mat2)*sizeof(double *));
  for(int i=0;i<(d1_mat1+d1_mat2);i++)
  {
    result[i]=(double *) malloc (d2*sizeof(double));
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
double ***concate3d_cube(int d1,int d2,int d3,double ***array1, double ***array2)
{
//  description: In this case, the d1,d2,d3 for array2 and array1 are the same
//  d1 in the "cut" cube is half of the input cube
  double ***result=(double ***) malloc (2*d1*sizeof(double **));
  for(int i=0;i<2*d1;i++)
  {
    result[i]=(double **) malloc (d2*sizeof(double *));
  }
  for(int i=0;i<2*d1;i++)
  {
    for(int j=0;j<d2;j++)
    {
      result[i][j]=(double *) malloc (d3*sizeof(double));
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
double *take1d(double *input_array, int take_n)
{
  double *result=(double *) malloc (take_n*sizeof(double));
  for(int i=0;i<take_n;i++)
  {
    result[i]=input_array[i];
  }
  return result;
}

double ***take3d(int d1,int d2,int d3,double ***input_cube, int take_n)
{
  double ***result=(double ***) malloc (take_n*sizeof(double **));
  for(int i=0;i<take_n;i++)
  {
    result[i]=(double **) malloc (d2*sizeof(double *));
  }
  for(int i=0;i<take_n;i++)
  {
    for(int j=0;j<d2;j++)
    {
      result[i][j]=(double *) malloc (d3*sizeof(double));
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
double *drop1d(double *input_array, int array_len, int drop_n)
{
  double *result=(double *) malloc ((array_len-drop_n)*sizeof(double));

  for(int i=0;i<array_len-drop_n;i++)
  {
    result[i]=input_array[array_len-drop_n+i];
  }
  return result;
}
double **drop2d(int d1,int d2,double **input_matrix,int drop_n)
{
  double **result=(double **) malloc ((d1-drop_n)*sizeof(double *));
  for(int i=0;i<d1-drop_n;i++)
  {
    result[i]=(double *) malloc (d2*sizeof(double));
  }
  for(int i=0;i<d1-drop_n;i++)
  {
    for(int j=0;j<d2;j++)
    {
//      printf("%f ",input_matrix[i][j]);
      result[i][j]=input_matrix[i+drop_n][j];
      printf("%f  ",result[i][j]);
    }
  }
  return result;
}

double ***drop3d(int d1,int d2,int d3,double ***input_cube, int drop_n)
{
  double ***result=(double ***) malloc ((d1-drop_n)*sizeof(double **));
  for(int i=0;i<(d1-drop_n);i++)
  {
    result[i]=(double **) malloc (d2*sizeof(double *));
  }
  for(int i=0;i<(d1-drop_n);i++)
  {
    for(int j=0;j<d2;j++)
    {
      result[i][j]=(double *) malloc (d3*sizeof(double));
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
double *fanoutn1d(int input_value, int n_times)
{
  double *result=(double *) malloc ((n_times)*sizeof(double));

  for(int i=0;i<n_times;i++)
  {
    result[i]=input_value;
  }
  return result;
}
double **fanoutn2d(double *input_array, int array_length, int n_times)
{
  double **result=(double **) malloc (n_times*sizeof(double *));
  for(int i=0;i<n_times;i++)
  {
    result[i]=(double *) malloc (array_length*sizeof(double));
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
double ***fanoutn3d(double **input_matrix, int d1, int d2, int n_times)
{
  double ***result=(double ***) malloc (n_times*sizeof(double **));
  for(int i=0;i<d1;i++)
  {
    result[i]=(double **) malloc (d1*sizeof(double *));
  }
  for(int i=0;i<n_times;i++)
  {
    for(int j=0;j<d1;j++)
    {
      result[i][j]=(double *) malloc (d2*sizeof(double));
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
double *farm11_1d(double (*operation)(double), double *input_array, int array_len)
{
  double *result=(double *) malloc ((array_len)*sizeof(double));

  for(int i=0;i<array_len;i++)
  {
    result[i]=operation(*(input_array+i));
  }
  return result;
}

double **farm11_2d(double **(*operation)(int,int,double **), int d1,int d2,double **input_matrix)
{
  double **result=(double **) malloc (d1*sizeof(double));
  for(int i=0;i<d1;i++)
  {
    result[i]=(double *) malloc (d2*sizeof(double));
  }

  result=operation(d1,d2,input_matrix);
  return result;
}

//farm21
double *farm21_1d(double (*operation)(double,double), double *input_array1, double *input_array2, int array_len)
{
  double *result=(double *) malloc ((array_len)*sizeof(double));
  for(int i=0;i<array_len;i++)
  {
    result[i]=operation(*(input_array1+i),*(input_array2+i));
  }
  return result;
}

double **farm41_2d(double (*operation)(double,double,double,double),int d1,int d2,double **input_matrix1,double **input_matrix2,double **input_matrix3,double **input_matrix4)
{
  double **result=(double **) malloc (d1*sizeof(double*));
  for(int i=0;i<d1;i++)
  {
    result[i]=(double *) malloc (d2*sizeof(double));
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

double ***group2d(int d1,int d2,double **input_matrix,int num)
{
  double ***result=allocate_cube(d1/num,num,d2);
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

double *reduce1d(double (*operation)(double, double), int array_len, double *input_array)
{
  double *result=(double *) malloc ((1)*sizeof(double));

  *result=operation(*input_array,*(input_array+1));
  for(int i=2;i<array_len;i++)
  {
    *result=operation(*result,*(input_array+i));
  }
  return result;
}
double *reduceV2d( int d1,int d2,double *(*operation)(double*, double*,int d2),double **input_matrix)
{
  double *result=(double *) malloc (d2*sizeof(double));
  result=operation(input_matrix[0],input_matrix[1],d2);
  for(int i=2;i<d1;i++){
      result=operation(result,input_matrix[i],d2);
  }
  return result;
}
//reduceVector 3d （对于三维数据cube储存的每一个一维向量操作得到二维矩阵）
double **reduceV3d(int d1,int d2,int d3, double *(*operation)(double*, double*,int d3),double ***input_cube)
{
  double **result=(double **) malloc (d1*sizeof(double *));
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

double ***stencil2d(int in_d1, int in_d2, double **a, int stencil_length)
{
    int d1 = in_d1 - stencil_length + 1;
    int d2 = stencil_length;
    int d3 = in_d2;
    double *** result = (double ***) malloc (d1 * sizeof(double **));
    for (int i = 0; i < d1; i++){
      result[i] = (double **) malloc (d2 * sizeof(double*));
    }
    for (int i = 0; i < d1; i++){
        for (int j = 0; j < d2; j++){
          result[i][j] = (double *) malloc (d3 * sizeof(double));
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

//simple example for farm
//description
//functions below are the concrete compute operations can be passed to farm
double add(double input1, double input2)
{
  return input1+input2;
}

double add_one(double input)
{
  return input+1;
}
double *addV(double *inputVector1,double *inputVector2,int len_array)
{
  double *result=farm21_1d(add, inputVector1, inputVector2, len_array);
  return result;
}
double minimum(double num1,double num2)
{
  if(num1<num2) {return num1;}
  else return num2;
}

double *minimumVec(double *inputV1,double *inputV2 ,int d2)
{
  double *result=farm21_1d(minimum,inputV1,inputV2, d2);
  return result;
}

double logBase2_div4(double input)
{
//  printf("%f   ",log2(input/4));
  return log2(input/4);
}
double div_N(double input)
{
  return input/NoFFT;
}

//In order to construct a vector computing function you can farm21 the operation
//you would like to use over numbers.
