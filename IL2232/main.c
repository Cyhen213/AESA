/**
 * @file main.c
 * @author YuchenGao (yuchenga@kth.se)
 * @brief This file imports the data cubes 
 * that are passed to the AESA radar model 
 * and run some tests over the model in AESA.c file.
 * @version 0.1
 * @date 2022-11-16
 * 
 * @copyright Copyright (c) 2022
 * @section Description
 * Please include the "skeletons.h" and "AESA.h" .
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "skeletons.h"
#include "AESA.h"
/**
 * @def NoFFT 
 * The number of Windows.
 * @def Nob 
 * The number of range bins.
 * @def NoB
 * The number of beams.
 * @def No2Channel
 * The number of data channel for real and imagine part in signal.
 * @def NoChannel 
 * The number of data channel.
 */
#define NoFFT 256//window
#define Nob 1024 //range
#define NoB 2//beam
#define No2Channel 32
#define NoChannel 16
/**
 * @brief The main function read in the .csv file that has already been generated. Apply corresponding AESA computation methods and generate result.
 * @return int 
*/
int main()
{
/**
 * @brief Firstly read from data/.. file.
 * In the data file, each row contains 256*18<4820 character position.
 */
  FILE *fp = fopen("data/processed_Cfar.csv", "r");
  if (fp == NULL) {
      fprintf(stderr, "fopen() failed.\n");
      exit(EXIT_FAILURE);
  }
  char row[4820];
  char *tok;
  int k=0;
  double ***data_cube=allocate_cube(NoB, Nob, NoFFT);
  
  int cube_idx;
  int pulse_idx;
  
  for(int j=0;j<NoB*Nob;j++)
  {
    fgets(row, 4820, fp);
    tok = strtok(row, ",");
    /**
     * @brief Perform how to store the cube: 
     * @code     
     * cube_idx=j/Nob;
       pulse_idx=j%Nob; @endcode
     * Each cube is 1024 lines and each line has 256 double precision varible.
     * The current index/Nob is the cube index, and the remainder of index divides Nob is the index for pulse.
     * @code strtok() @endcode 
     * This function strips the "," inside data cube and atof turns each string into float.
     */
    cube_idx=j/Nob;
    pulse_idx=j%Nob;
    while(tok!=NULL)
    {
      if(k<NoFFT){data_cube[cube_idx][pulse_idx][k]=atof(tok);}
      k+=1;
      tok=strtok(NULL,",");
    }k=0;
  }
  fclose(fp);
  print_cube(NoB, Nob, NoFFT, data_cube);
//
//  double ***result_cube=allocate_cube(NoB, Nob, NoFFT);
//
//  for(int i=0;i<NoB;i++)
//  {
//    result_cube[i]=fCFAR(Nob,NoFFT,data_cube[i]);
//  }
//  print_cube(NoB, Nob, NoFFT, result_cube);
//  free_cube(NoB, Nob, NoFFT, data_cube);
//  free_cube(NoB, Nob, NoFFT, result_cube);
  return 0;
}

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
