//
//  skeletons.h
//  IL2232
//
//  Created by gaogao on 2022-10-12.
//
#include <stdio.h>

#ifndef skeletons_h
#define skeletons_h
void print_array(int *array, int length);

int *concate(int *array1, int *array2, int *result, const int len1, const int len2);
//implementation of <++> operation

int *take(int *input_array, int *result, int take_n);

int *drop(int *input_array, int *result, int array_len, int drop_n);
//void fanout();
//void mealy();


#endif /* skeletons_h */
