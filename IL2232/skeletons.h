//
//  skeletons.h
//  IL2232
//
//  Created by gaogao on 2022-10-12.
//
#include <stdio.h>

#ifndef skeletons_h
#define skeletons_h
int ***allocate_cube(int d1,int d2,int d3,int cube[d1][d2][d3]);
void free_cube(int d1,int d2,int d3,int ***cube);

void print_array(int *array, int length);
void print_cube(int d1,int d2,int d3,int ***cube);
//implementation of <++> operation
int **concate1d(int *array1, int *array2, const int array_len);
int ***concate3d_cube(int d1,int d2,int d3,int ***array1, int ***array2);

int *take1d(int *input_array, int take_n);
int ***take3d(int d1,int d2,int d3,int ***input_cube, int take_n);

int *drop1d(int *input_array, int array_len, int drop_n);
int ***drop3d(int d1,int d2,int d3,int ***input_cube, int drop_n);

int *fanoutn1d(int input_value, int n);

int *farm111d(int (*operation)(int), int *input_array, int array_len);
int *farm211d(int (*operation)(int,int), int *input_array1, int *input_array2, int array_len);

int *reduce1d(int (*operation)(int, int), int *input_array, int array_len);
int *** stencil2d(int in_d1, int in_d2, int a [in_d1][in_d2], int stencil_length);

int add(int input1, int input2);
int add_one(int input);
#endif /* skeletons_h */
