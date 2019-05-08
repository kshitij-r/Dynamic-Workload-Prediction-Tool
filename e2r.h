// #include "stdafx.h"
#include<iostream>
#ifndef e2r
#define e2r
#endif
using namespace std;

class elementToprocessor
{

public:
  int max;

public:
  int *r2e_hash;

public:
  void mem_allocate(int size)
  {
    max = size;
    r2e_hash = new int[max];
  }

  void hashArray(int arr[])
  {
    for (int i = 0; i < max; i++)
      r2e_hash[i] = arr[i];
  }

  void printval()
  {
    for (int i = 0; i < max; i++)
      cout <<"Element"<<i<<"Rank "<< r2e_hash[i] << " "<<endl;
  }
};