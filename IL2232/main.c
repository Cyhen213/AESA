//
//  main.c
//  IL2232
//
//  Created by gaogao on 2022-10-11.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "skeletons.h"
#include "AESA.h"
#define Nfft 3//for illustration purpose, actual is 256
#define Nb 4 //same as above
//test for overlap


//int main(int argc, const char *argv[])
//{
////Description :test for the concate3d function
////  int cube1[1][2][2]={{{1,2},{3,4}}};
////  int cube2[1][2][2]={{{0,0},{0,0}}};
////  int ***result=concate3d_cube(1,2,2,cube1,cube2);
////  for(int i=0;i<2;i++){for(int j=0;j<2;j++){for(int k=0;k<2;k++){printf("%d ",result[i][j][k]);}}}
//
////  Description :test for the take3d&drop3d
//////
////  int cube1[2][2][2]={{{1,2},{3,4}},{{5,6},{7,8}}};
////  int ***result=take3d(2, 2, 2, cube1, 1);
////  print_cube(1, 2, 2, result);
//  int cube1[2][2][2]={{{1,2},{3,4}},{{5,6},{7,8}}};
//  int cube2[2][2][2]={{{4,5},{1,8}},{{3,9},{0,4}}};
//  //用一个allocate函数为每一个输入的cube分配三维指针动态内存。
//  int ***cube1ptr=allocate_cube_from_cube(2,2,2,cube1);
//  int ***cube2ptr=allocate_cube_from_cube(2,2,2,cube2);
//  int initial[1][2][2]={0};
//  int ***nextState=allocate_cube_from_cube(1,2,2,initial);
////  print_cube(2, 2, 2, cube1);
//
//
//  //  int ***result=take3d(2, 2, 2, cube1, 1);
////  print_cube(1, 2, 2, result);
////  free_cube(1, 2, 2, result);
//  int ***result1=overlap(2,2,2,cube1ptr,nextState);
//  printf("output cube:\n ");
//  print_cube(2, 2, 2, result1);
//  printf("nextState is set to be: \n");
//  print_cube(1, 2, 2, nextState);
//
//  int ***result2=overlap(2,2,2,cube2ptr,nextState);
//
//  printf("output cube:\n ");
//  print_cube(2, 2, 2, result2);
//  printf("nextState is set to be: \n");
//  print_cube(1, 2, 2, nextState);
//
//  free_cube(2, 2, 2, cube1ptr);
//  free_cube(2, 2, 2, cube2ptr);
//  free_cube(2, 2, 2, result1);
//  free_cube(2, 2, 2, result2);
//  free_cube(1, 2, 2, nextState);
//
//
//  return 0;
//}
//
//Test for the sequential cubes
//int main(int argc, const char *argv[])
//{
//  int d1=2;
//  int d2=2;
//  int d3=2;
//  int a[32]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
////Description : allocate 4 cubes
//  int ****cubes=(int ****) malloc (4*sizeof(int ***));
//  for(int i=0;i<4;i++)
//  {
//    cubes[i]=allocate_cube(2, 2, 2);
//  }
////Description : assign value for the allocated cubes from the read array.
//  for(int i=0;i<4;i++)
//  {
//    for(int j=0;j<d1;j++)
//    {
//      for(int k=0;k<d2;k++)
//      {
//        for(int l=0;l<d3;l++)
//        {
//          cubes[i][j][k][l]=a[8*i+j*4+k*2+l];
//        }
//      }
//    }
//  }
//
//  int initial[1][2][2]={0};
//  int ***nextState=allocate_cube_from_cube(1,2,2,initial);
//  for(int i=0;i<4;i++)
//  {
//    int ***newCube=overlap(2, 2, 2, cubes[i], nextState);
//    printf("output cube:\n ");
//    print_cube(2, 2, 2, newCube);
//    printf("nextState is set to be: \n");
//    print_cube(1, 2, 2, nextState);
//  }
////  release 4 cubes
//  for(int i=0;i<4;i++)
//  {
//    free_cube(2, 2, 2, cubes[i]);
//  }
//  free(cubes);
//  free_cube(1, 2, 2, nextState);
//  return 0;
//}
int main(int argc, const char *argv[])
{
  int **input_matrix=(int **) malloc (8*sizeof(int *));
  for(int i=0;i<8;i++)
  {
    input_matrix[i]=(int *) malloc (4*sizeof(int));
  }
  int mat[8][4]={{64,128,64,128},{256,128,64,128},{128,128,128,128},{512,128,64,128},{64,128,64,128},{256,128,64,128},{128,128,128,128},{512,128,64,128}};
  for(int i=0;i<8;i++)
  {
    for(int j=0;j<4;j++)
    {
      input_matrix[i][j]=mat[i][j];
    }
  }
//  test for arithmean
//  int *result=arithmean(4,4,input_matrix);
//  print_array(result,4);
//  int **arithm=(int **) malloc (3*sizeof(int *));
//  for(int i=0;i<5;i++)
//  {
//    arithm[i]=(int *) malloc (4*sizeof(int));
//  }
//  int ***neighbors=stencil2d(8, 4, input_matrix, 4);
//  for(int i=0;i<5;i++)
//  {
//    arithm[i]=arithmean(4, 4, neighbors[i]);
//    print_array(arithm[i], 4);
//    printf("\n ");
//  }
//
  int **result=fCFAR(8, 4, input_matrix);
  for(int i=0;i<8;i++)
  {
    print_array(result[i], 4);
    printf("\n ");
  }
  return 0;
}
