//
//  main.c
//  IL2232
//
//  Created by gaogao on 2022-10-11.
//

#include <stdio.h>
#include "skeletons.h"
#include "AESA.h"
#define Nfft 3//for illustration purpose, actual is 256
#define Nb 4 //same as above
#define resultMatrix_div_inputMatrix 2
//
//int main(int argc, const char * argv[]) {
//######test for take ,drop ,<++>#######
//  const int len_array1=8;
//  const int len_array2=8;
//  int array1[]={5,6,0,3,5,6,7,8};
//  int array2[]={4,5,6,7,8,4,3,2};
//  int result_concat[16]={0};
//  int result_take[8]={0};
//  int result_drop[8]={0};
//  int *array1Ptr=array1;
//  int *array2Ptr=array2;
//  int *concat_arrayPtr=result_concat;
//  int *result_takePtr=result_take;
//  int *result_takePtr=result_drop;
//  concate(array1,array2,result_concat,len_array1,len_array2);
//  take(result_concat, result_take, 8);
//  drop(result_concat, result_drop, 16, 8);
//  print_array(result_drop, sizeof(result_drop)/sizeof(result_drop[0]));

  
//######test for fanout#######
//  int fanout_length=8;
//  int fanout_value=6;
//  int fanout_array[8]={0};
//  int *result_fanout=fanout_array;
//  fanoutn(fanout_value, result_fanout, fanout_length);
//  print_array(result_fanout, fanout_length);
//  return 0;
//}
  
//######teste for overlap#####
//
//int main(int argc, const char * argv[])
//{
//  const int cubenum=4;
//  const int cubesize=8;
//  int nextState[cubesize/2]={0};
//  int currentState[cubesize/2]={0};
//  int cubes[cubenum][cubesize]={{1,2,3,4,5,6,7,8},
//                                {9,8,7,6,5,4,3,2},
//                                {2,4,6,8,6,4,2,1},
//                                {9,4,6,2,5,6,7,3}};
//  int output[cubesize]={0};
//  int restCube[cubesize/2]={0};
//
//  int *nextStatePtr=nextState;
//  int *currentStatePtr=currentState;
//
//  
//  int *outputPtr=output;
//  int *restCubePtr=restCube;
//  int (*cubePtr)[cubesize]=cubes;
//
//  for(int i=0;i<cubenum;i++)
//  {
//    overlap(*(cubePtr+i), nextStatePtr, currentStatePtr, outputPtr, restCubePtr, cubesize);
//    printf("output is going to be: ");
//    print_array(outputPtr, cubesize);
//    printf("\n");
//    printf("current state is set to be: ");
//    print_array(nextStatePtr, cubesize/2);
//    printf("\n");
//  }
//}


//######teste for farm11#####
//######teste for reduce#####

//int main(int argc, const char * argv[]) {
//  int array1[4]={1,2,3,4};
//  int array2[4]={2,3,6,7};
//  int result_array[4]={0};
////   these 2 lines below are for the reduce function
////  int result=0;
////  int *result_ptr=&result;
//  //
//  int *array1_ptr=array1;
//  int *array2_ptr=array2;
//
//  int *result_array_ptr=result_array;
////  farm11(add_one, result_array_ptr, array1_ptr, 4);
////  print_array(result_array_ptr, 4);
////  reduce(add, result_ptr, array1_ptr, 4);
////  printf(" %d \n", *result_ptr);
//  farm21(add, result_array_ptr, array1_ptr, array2_ptr, 4);
//  print_array(result_array_ptr, 4);
//  return 0;
//}
//
//test for 2d matrix
void stencil_for_one_dim(int (*input_matrix)[Nfft], int (*result_matrix)[Nfft])
{
  //description:  input a 2D array, and calculate how many elements expected to be given out. Then iterate to assign the values
  int i;
  for(i=0;i<(Nb-1)*resultMatrix_div_inputMatrix;i++)
  {
    for(int j=0;j<Nfft;j++)
    {
      *(*(result_matrix+i)+j)=*(*(input_matrix+i%Nb)+j);
    }
  }
}

int main(int argc, const char *argv[])
{

  int matrix[Nb][Nfft]={{2,3,4},
                        {5,6,7},
                        {8,9,3},
                        {3,6,9}};
  int (*matrix_ptr)[Nfft]=matrix;
  
  int result_matrix[(Nb-1)*resultMatrix_div_inputMatrix][Nfft]={0};
  int (*result_matrix_ptr)[Nfft]=result_matrix;
  stencil_for_one_dim(matrix_ptr, result_matrix_ptr);
  for(int i=0;i<6;i++)
  {
    print_array(*(result_matrix_ptr+i), Nfft);
    printf("\n");
  }
}
