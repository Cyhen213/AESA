//
//  skeletons.c
//  IL2232
//
//  Created by gaogao on 2022-10-12.
//
#include <stdio.h>

void print_array(int *array, int length)
{
  for(int i=0;i<length;i++)
  {
    printf("%d  ", *(array+i));
  }
}

int *concate(int *array1, int *array2,int *result, const int len1,const int len2)//implementation of <++> operation
{
  for(int i=0;i<len1;i++)
  {
    *(result+i)=*(array1+i);
  }
  for(int i=0;i<len2;i++)
  {
    *(result+len1+i)=*(array2+i);
  }
  return result;
}

int *take(int *input_array, int *result, int take_n)
{
  for(int i=0;i<take_n;i++)
  {
    *(result+i)=*(input_array+i);
  }
  return result;
}

int *drop(int *input_array, int *result, int array_len, int drop_n)
{
  for(int i=drop_n;i<array_len;i++)
  {
    *(result+i-drop_n)=*(input_array+i);
  }
  return result;
}

int *fanoutn(int input_value, int *result, int n_times)
{
  for(int i=0;i<n_times;i++)
  {
    *(result+i)=input_value;
  }
  return result;
}

