// 1-2.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NoFFT 256//window
#define Nob 1024 //range
#define NoB 2//beam
#define No2Channel 32
#define NoChannel 16
int main()
{
  FILE *fp = fopen("processed_Cfar.csv", "r");
  if (fp == NULL) {
      fprintf(stderr, "fopen() failed.\n");
      exit(EXIT_FAILURE);
  }
  char row[4820];
  char *tok;
  int k=0;
  double testnum;
  double ***data_cube=(double ***) malloc (NoB*sizeof(double **));
  for(int i=0;i<NoB;i++)
  {
    data_cube[i]=(double **) malloc (Nob*sizeof(double *));
  }
  for(int i=0;i<NoB;i++)
  {
    for(int j=0;j<Nob;j++)
    {
      data_cube[i][j]=(double *) malloc (NoFFT*sizeof(double));
    }
  }
//   for (int i = 0; i < NoB; i++){
//       for (int j = 0; j < Nob; j++){
//           for (int k = 0; k < NoFFT; k++){
//              printf("%f ", data_cube[i][j][k]);
//           }
//        printf("cube index: %d, pulse index :%d \n",i,j);

//         printf("\n");
//         }
//     printf("\n");
//    }
double *long_array=(double *) malloc (NoB*Nob*NoFFT*sizeof(double));
// for(int i=0;i<NoB*Nob*NoFFT;i++)
// {    
//     printf("Index is: %d ",i);
// }
for(int j=0;j<NoB*Nob;j++)
{
    fgets(row, 4820, fp);
    tok = strtok(row, ",");
    testnum=atof(tok);
    printf("%f\n",testnum);
    while(tok!=NULL)
    {
        testnum=atof(tok);
        printf("%f\n",testnum);
        tok=strtok(NULL,",");
        // printf("Index is: %d ",j*NoFFT+k);
        long_array[j*NoFFT+k]=testnum;
        k+=1;
    }
}
// for(int i=0;i<NoB*Nob*NoFFT;i++)
// {
//     printf(" %f ",long_array[i]);
// }
fclose(fp);
//  for (int i = 0; i < NoB; i++){
//       for (int j = 0; j < Nob; j++){
//           for (int k = 0; k < NoFFT; k++){
//               printf("%f ", data_cube[i][j][k]);
//           }
//         printf("\n");
//         }
//     printf("\n");
//    }
  return 0;

}

