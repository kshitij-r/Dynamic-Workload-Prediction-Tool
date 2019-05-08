#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <vector>
#include <cstdio>
#include<omp.h>
#include <bits/stdc++.h>
#include "e2r.h"
using namespace std;

void hash_table(elementToprocessor &obj)
    {   omp_set_num_threads(8);
        char filename[50];
        int rank;
        int element;
        int count1=0;
        ifstream input("65536r2e.csv");
        ifstream input1("65536r2e.csv");
        ifstream input2("65536r2e.csv");

        vector<string> result;
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
        string str;
        int row = 0;
        int column = 0;
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
        int counter = 0;
        int RowRank = 0;
        int RankArray[max_el + 1], RankArrayarr[max_el + 1];
        
 #pragma omp parallel for
        for (int i = 0; i < line_count; i++)
        {
        if(omp_get_thread_num() == 1)
        {
          count1++;
        }
         
            for (int j = 0; j < max; j++)
            {
                if (j == 0)
                {
                    RowRank = arr[i][j];
                }
                else if (j != 0 && arr[i][j] != 0)
                {
                    RankArrayarr[arr[i][j]] = RowRank;
                }
            }
        }
        
cout<<"Thread 1 in my rank"<<" "<<count1<<endl;
        obj.mem_allocate(max_el + 1);
        obj.hashArray(RankArrayarr);

    }