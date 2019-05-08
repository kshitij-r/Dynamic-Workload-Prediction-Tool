#include<iostream>
#include<cstdlib>
#include<cstring>
#include<fstream>
#include <vector>
#include<cstdio>
#include<bits/stdc++.h>
//#include<boost/algorithm/string.hpp>
#include "e2r.h"
using namespace std;


void hash_table(elementToprocessor& obj) {
    char filename[50];
    int rank;
    int element;

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
            //cout<< line[i];
            if (line[i]==',')
                col_count++;                     //Count the number of commas in one row of input file => Columns
            }
            
            col_count++;
            if(col_count>max){
                max=col_count;                  
            }
            col_count=0;
             
     }

     int arr[line_count][max];
     string str;
     int row=0;
     int column=0; 
     for(string line; getline(input1, line);){
          for(int z=0;z<line.size();z++){
              if(line[z]==','){
                  flag=1;
              }
              if(flag==1)
              {
                  //cout<<str<<"  ";
                  arr[row][column]= stoi(str);
                  if (stoi(str)>max_el)
                  {
                      max_el = stoi(str);
                  }
                  flag=0;
                  str="";
                  column++;
              }
              else{
                str=str + line[z];
                  }
          }
          
          arr[row][column]= stoi(str);
          if (stoi(str)>max_el)
          {
              max_el = stoi(str);
          }
          
          for(int j=column+1;j<max;j++){
              arr[row][j]=stoi("0");
          }

          str = "";
          row++;
          column=0;
     }

    int counter=0;
    int RowRank=0;
    int RankArray[max_el + 1];
   
    for (string line; getline(input2, line);)
    {
        counter = 1;
        for (int z = 0; z < line.size(); z++)
        {
            if (line[z] == ',')
            {
                flag = 1;
            }
            if (flag == 1)
            {
                if (counter == 1)
                {
                    RowRank = stoi(str);
                }
            
                if ((counter == 0) && (stoi(str) != 0))
                {
                    RankArray[stoi(str)] = RowRank;
                }
               
                flag = 0;
                str = "";
                column++;
                counter=0;
            }
            else
            {
                str = str + line[z];
            }
        }

        if ((counter == 0) && (stoi(str) != 0))
        {
            RankArray[stoi(str)] = RowRank;
        }

        str = "";
        row++;
        column = 0;
    }

obj.mem_allocate(max_el+1);
obj.hashArray(RankArray);

}