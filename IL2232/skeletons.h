/**
 * @file skeletons.h
 * @brief
 * REMIND: ALL THE SKELETONS FUNCTION AUTOMATICALLY ALLOCATES DYNAMIC SPACE MUST BE RELEASED.
 * @version 0.1
 * @date 2022-11-18
 * @copyright Copyright (c) 2022
 */
#include <stdio.h>
#include <math.h>

#ifndef skeletons_h
#define skeletons_h
double ***allocate_cube(int d1,int d2,int d3);
double ***allocate_cube_from_cube(int d1,int d2,int d3,double cube[d1][d2][d3]);
double **allocate_mat(int d1,int d2);

void free_matrix(int d1,int d2,double **matrix);
void free_cube(int d1,int d2,int d3,double ***cube);

void print_array(double *array, int length);
void print_matrix(int d1,int d2,double **matrix);
void print_cube(int d1,int d2,int d3,double ***cube);
double **concate1d(double *array1, double *array2, int array_len);
double **concate2d_mat(int d1_mat1, int d1_mat2, int d2, double **input_matrix1, double **input_matrix2);
double ***concate3d_cube(int d1,int d2,int d3,double ***array1, double ***array2);

double *take1d(double *input_array, int take_n);
double ***take3d(int d1,int d2,int d3,double ***input_cube, int take_n);

double *drop1d(double *input_array, int array_len, int drop_n);
double **drop2d(int d1,int d2,double **input_matrix,int drop_n);
double ***drop3d(int d1,int d2,int d3,double ***input_cube, int drop_n);

double *fanoutn1d(double input_value, int n);
double **fanoutn2d(double *input_array, int array_length, int n_times);
double ***fanoutn3d(double **input_matrix, int d1, int d2, int n_times);

double *farm11_1d(double (*operation)(double), double *input_array, int array_len);
double **farm11_2d(double (*operation)(double), int d1,int d2,double **input_matrix);
double *farm21_1d(double (*operation)(double,double), double *input_array1, double *input_array2, int array_len);
double **farm41_2d(double (*operation)(double,double,double,double),int d1,int d2,double **input_matrix1,double **input_matrix2,double **input_matrix3,double **input_matrix4);

double ***group2d(int d1,int d2,double **input_matrix,int num);

double *reduce1d(double (*operation)(double, double), int array_len, double *input_array);
double *reduceV2d( int d1,int d2,double *(*operation)(double*, double*,int d2),double **input_matrix);
double **reduceV3d(double *(*operation)(double*, double*), int d1,int d2,int d3,double ***input_cube);


double ***stencil2d(int in_d1, int in_d2, double **a, int stencil_length);

double add(double input1, double input2);
double add_one(double input);
double *addV(double *inputVector1,double *inputVector2,int len_array);

double minimum(double num1,double num2);
double *minimumVec(double *inputV1,double *inputV2 ,int d2);


double logBase2_div4(double input);
double div_N(double input);
double logBase2(double input);
#endif /* skeletons_h */
