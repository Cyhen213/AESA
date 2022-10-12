//
//  main.c
//  IL2232
//
//  Created by gaogao on 2022-10-11.
//

#include <stdio.h>
#include "skeletons.h"
#define nFFt 8
#define nb 8
#define NB 8

int main(int argc, const char * argv[]) {
  const int len_a=8;
  const int len_b=8;
  int b[]={5,6,0,3,5,6,7,8};
  int a[]={4,5,6,7,8,4,3,2};
  int c[16]={0};
  int res_take[8]={0};
  int res_drop[8]={0};
  int *array1=b;
  int *array2=a;
  int *res=c;
  int *res1=res_take;
  int *res2=res_drop;
  res=concate(array1,array2,res,len_b,len_a);
  res1=take(res, res1, 8);
  res2=drop(res, res2, 16, 8);
  print_array(res2, sizeof(res_drop)/sizeof(c[0]));

  int fanout_length=8;
  int fanout_value=6;
  int fanout_array[8]={0};
  int *fanout_res=fanout_array;
  fanout_res=fanoutn(fanout_value, fanout_res, fanout_length);
  print_array(fanout_res, fanout_length);
  return 0;
}
