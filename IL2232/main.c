//
//  main.c
//  IL2232
//
//  Created by gaogao on 2022-10-11.
//

#include <stdio.h>
#include <stdlib.h>

#include "skeletons.h"
#include "AESA.h"
#define Nfft 3//for illustration purpose, actual is 256
#define Nb 4 //same as above

int main(int argc, const char *argv[])
{
//Description :test for the concate3d function
//  int cube1[1][2][2]={{{1,2},{3,4}}};
//  int cube2[1][2][2]={{{0,0},{0,0}}};
//  int ***result=concate3d_cube(1,2,2,cube1,cube2);
//  for(int i=0;i<2;i++){for(int j=0;j<2;j++){for(int k=0;k<2;k++){printf("%d ",result[i][j][k]);}}}
  
//  Description :test for the take3d&drop3d
////
//  int cube1[2][2][2]={{{1,2},{3,4}},{{5,6},{7,8}}};
//  int ***result=take3d(2, 2, 2, cube1, 1);
//  print_cube(1, 2, 2, result);
  int cube1[2][2][2]={{{1,2},{3,4}},{{5,6},{7,8}}};
  int cube2[2][2][2]={{{4,5},{1,8}},{{3,9},{0,4}}};
  int initial[1][2][2]={0};
  //用一个allocate函数为每一个输入的cube分配三维指针动态内存。
  int ***cube1ptr=allocate_cube(2,2,2,cube1);
  int ***cube2ptr=allocate_cube(2,2,2,cube2);
  int ***initState=allocate_cube(2,2,2,initial);
//  print_cube(2, 2, 2, cube1);

//  int ***result=take3d(2, 2, 2, cube1, 1);
//  print_cube(1, 2, 2, result);
//  free_cube(1, 2, 2, result);
  int ***result1=overlap(2,2,2,cube1ptr,initState);
  int ***nextState=StateUpdate(2, 2, 2, cube1ptr);
  printf("output cube:\n ");
  print_cube(2, 2, 2, result1);
  printf("nextState is set to be: \n");
  print_cube(1, 2, 2, nextState);
  
  int ***result2=overlap(2,2,2,cube2ptr,nextState);
  nextState=StateUpdate(2, 2, 2, cube2ptr);

  printf("output cube:\n ");
  print_cube(2, 2, 2, result2);
  printf("nextState is set to be: \n");
  print_cube(1, 2, 2, nextState);
  
  free_cube(2, 2, 2, cube1ptr);
  free_cube(2, 2, 2, cube2ptr);
  free_cube(2, 2, 2, result1);
  free_cube(2, 2, 2, result2);
  free_cube(1, 2, 2, nextState);

  
  return 0;
}
