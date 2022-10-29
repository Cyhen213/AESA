//
//  AESA.c
//  IL2232
//
//  Created by gaogao on 2022-10-13.
//

#include "AESA.h"
#include "skeletons.h"
//Used atom functions:
//take(int *input_array, int *result, int take_n);
//concate(int *array1, int *array2, int *result, const int len1, const int len2)
//drop(int *input_array, int *result, int array_len, int drop_n)

void overlap(int *inputCube, int *nextState, int *currentState, int *output, int *restCube ,int cubesize)
{
  take(inputCube, restCube, cubesize/2);
  concate(currentState, restCube, output, cubesize/2, cubesize/2);
  drop(inputCube, nextState, cubesize, cubesize/2);
  for(int i=0; i<cubesize/2; i++)
  {
    *(currentState+i)=*(nextState+i);
  }
}
