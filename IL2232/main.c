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
  int cube[2][2][2]={{{1,2},{3,4}},{{5,6},{7,8}}};
  //用一个allocate函数为每一个输入的cube分配三维指针动态内存。
  int ***cube1=allocate_cube(2, 2, 2, cube);
 
//  print_cube(2, 2, 2, cube1);

//  int ***result=take3d(2, 2, 2, cube1, 1);
//  print_cube(1, 2, 2, result);
//  free_cube(1, 2, 2, result);
  int ***result=overlap(2,2,2,cube1);
  print_cube(2, 2, 2, result);

  
//  free_cube(2, 2, 2, cube1);

  return 0;
}
