//
//  main.c
//  IL2232
//
//  Created by gaogao on 2022-10-11.
//

#include <stdio.h>
#include "skeletons.h"

int *overlap(int *inputCube, int *nextState, int *output, int *restCube, int cubesize);

int main(int argc, const char * argv[]) {
//######test for take ,drop ,<++>#######
//  const int len_a=8;
//  const int len_b=8;
//  int b[]={5,6,0,3,5,6,7,8};
//  int a[]={4,5,6,7,8,4,3,2};
//  int c[16]={0};
//  int res_take[8]={0};
//  int res_drop[8]={0};
//  int *array1=b;
//  int *array2=a;
//  int *res=c;
//  int *res1=res_take;
//  int *res2=res_drop;
//  concate(array1,array2,res,len_b,len_a);
//  take(res, res1, 8);
//  drop(res, res2, 16, 8);
//  print_array(res2, sizeof(res_drop)/sizeof(c[0]));

//######test for fanout#######
//  int fanout_length=8;
//  int fanout_value=6;
//  int fanout_array[8]={0};
//  int *fanout_res=fanout_array;
//  fanout_res=fanoutn(fanout_value, fanout_res, fanout_length);
//  print_array(fanout_res, fanout_length);
//######teste for mealy#####
  const int cubenum=3;
  const int cubesize=8;
  int initState[cubesize/2]={0};
  int nextState[cubesize/2]={0};
  int cubes[cubenum][cubesize]={{1,2,3,4,5,6,7,8},{9,8,7,6,5,4,3,2},{2,4,6,8,6,4,2,1}};
  int output[cubesize]={0};
  int restCube[cubesize/2]={0};

  int *initStatePtr=initState;
  int *nextStatePtr=nextState;
  int *outputPtr=output;
  int *restCubePtr=restCube;
  int (*cubePtr)[cubesize]=cubes;

  for(int i=0;i<cubenum;i++)
  {
    if (i==0) {
      nextStatePtr=overlap(*(cubePtr), initStatePtr, outputPtr, restCubePtr,cubesize);
    }
    else{
      nextStatePtr=overlap(*(cubePtr+i), nextStatePtr, outputPtr, restCubePtr,cubesize);
    }
    printf("output is going to be: ");
    print_array(outputPtr, cubesize);
    printf("\n");
    printf("current state is set to be: ");
    print_array(nextStatePtr, cubesize/2);
    printf("\n");
  }
  return 0;
}
