//
//  skeletons.c
//  IL2232
//
//  Created by gaogao on 2022-10-12.
//
#include <stdio.h>
//print function
void print_array(int *array, int length)
{
  for(int i=0;i<length;i++)
  {
    printf("%d  ", *(array+i));
  }
}
//concate two arrays
//implementation of <++>
void concate(int *array1, int *array2,int *result, const int len1,const int len2)
{
  for(int i=0;i<len1;i++)
  {
    *(result+i)=*(array1+i);
  }
  for(int i=0;i<len2;i++)
  {
    *(result+len1+i)=*(array2+i);
  }
}
//take n elements from an input array
void take(int *input_array, int *result, int take_n)
{
  for(int i=0;i<take_n;i++)
  {
    *(result+i)=*(input_array+i);
  }
}
//drop n elements from an input array
void drop(int *input_array, int *result, int array_len, int drop_n)
{
  for(int i=drop_n;i<array_len;i++)
  {
    *(result+i-drop_n)=*(input_array+i);
  }
}
//repeat a value n times and store in an array
void fanoutn(int input_value, int *result, int n_times)
{
  for(int i=0;i<n_times;i++)
  {
    *(result+i)=input_value;
  }
}
//farm11
void farm11(int (*operation)(int), int *result, int *input_array, int array_len)
{
  for(int i=0;i<array_len;i++)
  {
    *(result+i)=operation(*(input_array+i));
  }
}
//farm21
void farm21(int (*operation)(int,int), int *result, int *input_array1, int *input_array2, int array_len)
{
  for(int i=0;i<array_len;i++)
  {
    *(result+i)=operation(*(input_array1+i),*(input_array2+i));
  }
}

void reduce(int (*operation)(int, int), int *result, int *input_array, int array_len)
{
  *result=operation(*input_array,*(input_array+1));
  for(int i=2;i<array_len;i++)
  {
    *result=operation(*result,*(input_array+i));
  }
}

//simple example for farm
//description
//functions below are the concrete compute operations can be passed to farm
int add(int input1, int input2)
{
  return input1+input2;
}

int add_one(int input)
{
  return input+1;
}
