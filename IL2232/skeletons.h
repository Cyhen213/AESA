//
//  skeletons.h
//  IL2232
//
//  Created by gaogao on 2022-10-12.
//
#include <stdio.h>
#include <math.h>

#ifndef skeletons_h
#define skeletons_h
int ***allocate_cube(int d1,int d2,int d3);
int ***allocate_cube_from_cube(int d1,int d2,int d3,int cube[d1][d2][d3]);
void free_cube(int d1,int d2,int d3,int ***cube);

void print_array(int *array, int length);
void print_cube(int d1,int d2,int d3,int ***cube);
//implementation of <++> operation
int **concate1d(int *array1, int *array2, const int array_len);
int **concate2d_mat(int d1_mat1, int d1_mat2, int d2, int **input_matrix1, int **input_matrix2);
int ***concate3d_cube(int d1,int d2,int d3,int ***array1, int ***array2);

int *take1d(int *input_array, int take_n);
int ***take3d(int d1,int d2,int d3,int ***input_cube, int take_n);

int *drop1d(int *input_array, int array_len, int drop_n);
int **drop2d(int d1,int d2,int **input_matrix,int drop_n);
int ***drop3d(int d1,int d2,int d3,int ***input_cube, int drop_n);

int *fanoutn1d(int input_value, int n);
int **fanoutn2d(int *input_array, int array_length, int n_times);
int ***fanoutn3d(int **input_matrix, int d1, int d2, int n_times);

int *farm11_1d(int (*operation)(int), int *input_array, int array_len);
int **farm11_2d(int *(*operation)(int,int,int **), int d1,int d2,int **input_matrix);
int *farm11_2dto1d(int *(*operation)(int,int,int **), int d1,int d2,int **input_matrix);
int *farm21_1d(int (*operation)(int,int), int *input_array1, int *input_array2, int array_len);
int **farm41_2d(int (*operation)(int,int,int,int),int d1,int d2,int **input_matrix1,int **input_matrix2,int **input_matrix3,int **input_matrix4);

int ***group2d(int d1,int d2,int **input_matrix,int num);

int *reduce1d(int (*operation)(int, int), int array_len, int *input_array);
int *reduceV2d( int d1,int d2,int *(*operation)(int*, int*,int d2),int **input_matrix);
int **reduceV3d(int *(*operation)(int*, int*), int d1,int d2,int d3,int ***input_cube);


int ***stencil2d(int in_d1, int in_d2, int **a, int stencil_length);

int add(int input1, int input2);
int add_one(int input);
int *addV(int *inputVector1,int *inputVector2,int len_array);

int minimum(int num1,int num2);
int *minimumVec(int *inputV1,int *inputV2 ,int d2);


int logBase2_div4(int input);
int div_N(int input);

#endif /* skeletons_h */
