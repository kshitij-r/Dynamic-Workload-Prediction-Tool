#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <vector>
#include <cstdio>
#include <bits/stdc++.h>
#include<cuda_profiler_api.h>
#include<time.h>
#define BLOCK_SIZE 1024
#include "e2r.h"
using namespace std;

__global__ void RankArray_kernel(int*, int*, int, int);


__global__ void RankArray_kernel(int* arr, int* rank_arr, int lc, int max)
{
int index= (blockIdx.y * blockDim.y) + threadIdx.y;
int rank; 
for(int i=0;i<max;i++) {
     if(i==0)
       rank = arr[index*max];
    else if(i!=0 && arr[index*max+i]!=0)
    {
	   if(arr[index*max+i]==lc-1)
       rank_arr[0]=rank;
    else 
        rank_arr[arr[index*max+i]]=rank;
    }
}
}

void hash_table(elementToprocessor &obj)
    {
        char filename[50];
        int rank;
        int element;

        ifstream input("65536r2e.csv");
        ifstream input1("65536r2e.csv");
        int col_count = 0;
        int line_count = 0;
        int x = 0;
        int i = 0;
        int max_el = 0;
        int max = 0;
        int z = 0;
        int flag = 0;
        for (string line; getline(input, line);)
        {
            //cout << line.size() << endl;            //Count the number of lines in input file => Rows
            line_count++;
            for (int i = 0; i < line.size(); i++)
            {
                //cout<< line[i];
                if (line[i] == ',')
                    col_count++; //Count the number of commas in one row of input file => Columns
            }

            col_count++;
            if (col_count > max)
            {
                max = col_count;
            }
            col_count = 0;
        }

        int arr[line_count][max];
		int arr1[line_count*max];
        string str;
        int row = 0;
        int column = 0;
		int index;
        for (string line; getline(input1, line);)
        {
            for (int z = 0; z < line.size(); z++)
            {
                if (line[z] == ',')
                {
                    flag = 1;
                }
                if (flag == 1)
                {
                    //cout<<str<<"  ";
                    arr[row][column] = stoi(str);
                    if (stoi(str) > max_el)
                    {
                        max_el = stoi(str);
                    }
                    flag = 0;
                    str = "";
                    column++;
                }
                else
                {
                    str = str + line[z];
                }
            }

            arr[row][column] = stoi(str);
            if (stoi(str) > max_el)
            {
                max_el = stoi(str);
            }

            for (int j = column + 1; j < max; j++)
            {
                arr[row][j] = stoi("0");
            }

            str = "";
            row++;
            column = 0;
        }
        //cout<<"Max "<<max_el<<endl;
        for(i=0;i<line_count;i++) {
			for(int j=0;j<max;j++){
			index= i*max+j;
			arr1[index]=arr[i][j];
			}
		}
   
		int counter = 0;
        int RowRank = 0;
        int RankArray[max_el + 1], RankArrayarr[max_el + 1];
		int size= line_count*max;
		cout<<line_count<<endl;
   cout<<max<<endl;
    float size_f= (float)size;
    cout<<"Size"<<size_f;
		cudaProfilerStart();
		int* RankArray_d; //Device RankArray;
		cudaError_t err = cudaMalloc((void**)&RankArray_d, 4*(max_el+1));
		printf("CUDA malloc RankArray_d: %s\n",cudaGetErrorString(err));
		int *arr_d;  // Device input array;
		err = cudaMalloc((void**)&arr_d, 4*size);
		printf("CUDA malloc arr_d: %s\n",cudaGetErrorString(err));
		
		clock_t starttimer = clock();
		err = cudaMemcpy(arr_d, &arr1, 4*size, cudaMemcpyHostToDevice);
		printf("CUDA Memcpy arr_d->arr: %s\n",cudaGetErrorString(err));
		
		clock_t end = clock()-starttimer;
		float mseconds = (end*1000)/CLOCKS_PER_SEC;
		printf("Time of the MEMCPY of %d bytes: %2.3f ms\n",size,mseconds);
		// Compute the execution configuration assuming
// the matrix dimensions are multiples of BLOCK_SIZE
	int N=(int)ceil(sqrt(size));
   //cout<<"Normalized size"<<line_count<<max;
 int Grid= (int)((line_count-max)/BLOCK_SIZE);
   //cout<<"Grid Size"<<Grid;
	dim3 dimBlock(1, BLOCK_SIZE);
	dim3 dimGrid(1,Grid);
		clock_t startk = clock();
	RankArray_kernel<<<dimGrid, dimBlock>>>(arr_d,RankArray_d,max_el+1,max);
cudaError_t errk = cudaDeviceSynchronize();
clock_t diffk = clock()-startk;
float mksec = (diffk*1000)/CLOCKS_PER_SEC;
printf("Time to complete CUDA %d size: %2.3f ms\n",size,mksec);
printf("CUDA kernel launch: %s\n",cudaGetErrorString(errk));
clock_t start=clock(),diff;
err = cudaMemcpy(&RankArrayarr, RankArray_d, 4*max_el+1, cudaMemcpyDeviceToHost);
diff = clock()-start;
printf("CUDA Memcpy d_C->C: %s\n",cudaGetErrorString(err));
float msec = (diff*1000)/CLOCKS_PER_SEC;
printf("Time of the MEMCPY of %d bytes : %2.3f ms\n",size,msec);
cudaFree(arr_d);
cudaFree(RankArray_d);

cudaProfilerStop();
		RankArrayarr[max_el]=RankArrayarr[0];
        obj.mem_allocate(max_el + 1);
        obj.hashArray(RankArrayarr);

    }