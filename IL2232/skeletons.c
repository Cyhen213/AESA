/**
 * @file skeletons.c
 * @author Yuchen
 * @brief 
 * @version 0.1
 * @date 2022-11-16
 * 
 * @copyright Copyright (c) 2022
 * REMIND: ALL THE SKELETONS FUNCTION AUTOMATICALLY ALLOCATES DYNAMIC SPACE.
 */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define NoFFT 256
/**
 * @brief 
 * - Allocate_cube allocates (d1,d2,d3) space for elements
 * @param d1 
 * @param d2 
 * @param d3 
 * @return double*** 
 */
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
/**
 * @brief 
 * - Deep copy operation for input data cube.
 * @param d1 
 * @param d2 
 * @param d3 
 * @param cube 
 * @return double*** 
 */
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
/**
 * @brief 
 * - free a matrix
 * 
 * @param d1 
 * @param d2 
 * @param matrix 
 */
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
/**
 * @brief 
 * - free a cube
 * 
 * @param d1 
 * @param d2 
 * @param d3 
 * @param cube 
 */
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

/**
 * @brief 
 * - Concate 2 arrays with the same length and return an array with 2*length.
 * @param array1 
 * @param array2 
 * @param array_len 
 * @return double* 
 */
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
/**
 * @brief
 * - Concate 2 matrix with first dimenson is equal to d1_mat1 and d1_mat2. 
 * - Generate a matrix with size of (d1_mat1+d1_mat2, d2)
 * @param d1_mat1 
 * @param d1_mat2 
 * @param d2 
 * @param input_matrix1 
 * @param input_matrix2 
 * @return double** 
 */
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
/**
 * @brief 
 * - Concate 2 cubes with the same dimensionality (d1,d2,d3)
 * @param d1 
 * @param d2 
 * @param d3 
 * @param array1 
 * @param array2 
 * @return double*** 
 */
double ***concate3d_cube(int d1,int d2,int d3,double ***array1, double ***array2)
{
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

/**
 * @brief 
 * - Take first n elements from the input array and return them.
 * @param input_array 
 * @param take_n 
 * @return double* 
 */
double *take1d(double *input_array, int take_n)
{
  double *result=(double *) malloc (take_n*sizeof(double));
  for(int i=0;i<take_n;i++)
  {
    result[i]=input_array[i];
  }
  return result;
}
/**
 * @brief 
 * - Take the first n matrix from cube and return them as a new cube.
 * @param d1 
 * @param d2 
 * @param d3 
 * @param input_cube 
 * @param take_n 
 * @return double*** 
 */
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
/**
 * @brief 
 * - Drop the first n elements in an array and return the rest.
 * @param input_array 
 * @param array_len 
 * @param drop_n 
 * @return double* 
 */
double *drop1d(double *input_array, int array_len, int drop_n)
{
  double *result=(double *) malloc ((array_len-drop_n)*sizeof(double));

  for(int i=0;i<array_len-drop_n;i++)
  {
    result[i]=input_array[array_len-drop_n+i];
  }
  return result;
}
/**
 * @brief 
 * - Drop the first vectors in a matrix and return the rest vectors as a new matrix.
 * @param d1 
 * @param d2 
 * @param input_matrix 
 * @param drop_n 
 * @return double** 
 */
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
/**
 * @brief 
 * - Drop the first n matrix in a cube and return the rest as a new cube.
 * @param d1 
 * @param d2 
 * @param d3 
 * @param input_cube 
 * @param drop_n 
 * @return double*** 
 */
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
/**
 * @brief 
 * - Repeat a value n times and store in an array
 * @param input_value 
 * @param n_times 
 * @return double* 
 */
double *fanoutn1d(int input_value, int n_times)
{
  double *result=(double *) malloc ((n_times)*sizeof(double));

  for(int i=0;i<n_times;i++)
  {
    result[i]=input_value;
  }
  return result;
}
/**
 * @brief 
 * - repeat a vector n times and store in a matrix
 * @param input_array 
 * @param array_length 
 * @param n_times 
 * @return double** 
 */
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
/**
 * @brief 
 * - Repeat a matrix n times and store it in a cube.
 * @param input_matrix 
 * @param d1 
 * @param d2 
 * @param n_times 
 * @return double*** 
 */
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
/**
 * @brief
 * - Apply the operation function on a given array.
 * - The function takes 1 input value at a time. 
 * @param operation 
 * @param input_array 
 * @param array_len 
 * @return double* 
 */
double *farm11_1d(double (*operation)(double), double *input_array, int array_len)
{
  double *result=(double *) malloc ((array_len)*sizeof(double));

  for(int i=0;i<array_len;i++)
  {
    result[i]=operation(*(input_array+i));
  }
  return result;
}
/**
 * @brief 
 * - Apply the operation function on a given matrix.
 * - The function takes 1 input value at a time. 
 * @param operation 
 * @param d1 
 * @param d2 
 * @param input_matrix 
 * @return double** 
 */
double **farm11_2d(double (*operation)(double), int d1,int d2,double **input_matrix)
{
  double **result=(double **) malloc (d1*sizeof(double));
  for(int i=0;i<d1;i++)
  {
    result[i]=(double *) malloc (d2*sizeof(double));
  }
  for(int i=0;i<d1;i++)
  {
    for(int j=0;j<d2;j++)
    {
      result[i][j]=operation(input_matrix[i][j]);
    }
  }
  return result;
}
/**
 * @brief  
 * - Apply the operation function between two given array.
 * - The function takes 2 input values at a time.
 * - In order to construct a vector computing function you can farm21 the operation
 * - you would like to use over numbers. 
 * @param operation 
 * @param input_array1 
 * @param input_array2 
 * @param array_len 
 * @return double* 
 */
double *farm21_1d(double (*operation)(double,double), double *input_array1, double *input_array2, int array_len)
{
  double *result=(double *) malloc ((array_len)*sizeof(double));
  for(int i=0;i<array_len;i++)
  {
    result[i]=operation(*(input_array1+i),*(input_array2+i));
  }
  return result;
}
/**
 * @brief 
 * - Apply the operation function between 4 given matrix.
 * - The function takes 4 input values at a time. 
 * @param operation 
 * @param d1 
 * @param d2 
 * @param input_matrix1 
 * @param input_matrix2 
 * @param input_matrix3 
 * @param input_matrix4 
 * @return double** 
 */
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
/**
 * @brief 
 * - Group the input matrix into nums of vectors.
 * @param d1 
 * @param d2 
 * @param input_matrix 
 * @param num 
 * @return double*** 
 */
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
/**
 * @brief
 * - Reduce an array to a value.
 * - Apply the operation between elements inside of the input array.
 * - Return a value.
 * @param operation 
 * @param array_len 
 * @param input_array 
 * @return double* 
 */
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
/**
 * @brief 
 * - Reduce a matrix to a vector.
 * - Apply the function between vectors regarding to the same position.
 * - Return a vector.
 * @param d1 
 * @param d2 
 * @param operation 
 * @param input_matrix 
 * @return double* 
 */
double *reduceV2d( int d1,int d2,double *(*operation)(double*, double*,int d2),double **input_matrix)
{
  double *result=(double *) malloc (d2*sizeof(double));
  result=operation(input_matrix[0],input_matrix[1],d2);
  for(int i=2;i<d1;i++){
      result=operation(result,input_matrix[i],d2);
  }
  return result;
}
/**
 * @brief 
 * - Reduce a cube to a matrix.
 * - Apply the function between matrix regarding to the same position.
 * - Return a matrix.
 * @param d1 
 * @param d2 
 * @param d3 
 * @param operation 
 * @param input_cube 
 * @return double** 
 */
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
/**
 * @brief 
 * - Stencil a matrix.
 * - Collect the nearest stencil_length vectors and store as a new matrix.
 * - The dimension of returned matrix is determined by 
 * @code      
    int d1 = in_d1 - stencil_length + 1;
    int d2 = stencil_length;
    int d3 = in_d2;
    @endcode 
 * @param in_d1 
 * @param in_d2 
 * @param a 
 * @param stencil_length 
 * @return double*** (in_d1-stencil_length+1, stencil_length, in_d2)
 */
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
/**
 * @brief 
 * - Add two numbers.
 * @param input1 
 * @param input2 
 * @return double 
 */
double add(double input1, double input2)
{
  return input1+input2;
}
/**
 * @brief 
 * - Add two vectors.
 * @param inputVector1 
 * @param inputVector2 
 * @param len_array 
 * @return double* 
 */
double *addV(double *inputVector1,double *inputVector2,int len_array)
{
  double *result=farm21_1d(add, inputVector1, inputVector2, len_array);
  return result;
}
/**
 * @brief 
 * - Find minimum between 2 numbers.
 * @param num1 
 * @param num2 
 * @return double 
 */
double minimum(double num1,double num2)
{
  if(num1<num2) {return num1;}
  else return num2;
}
/**
 * @brief 
 * - find minimum number between two vectors.
 * @param inputV1 
 * @param inputV2 
 * @param d2 
 * @return double* 
 */
double *minimumVec(double *inputV1,double *inputV2 ,int d2)
{
  double *result=farm21_1d(minimum,inputV1,inputV2, d2);
  return result;
}
/**
 * @brief 
 * - Compute the log2(input/4).
 * @param input 
 * @return double 
 */
double logBase2_div4(double input)
{
  return log2(input/4);
}
/**
 * @brief 
 * - Divide NoFFT by input.
 * @param input 
 * @return double 
 */
double div_N(double input)
{
  return input/NoFFT;
}

