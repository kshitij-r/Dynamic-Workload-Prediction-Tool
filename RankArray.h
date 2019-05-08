
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <vector>
#include <cstdio>
using namespace std;

int* master()
{

    ifstream input("65536r2e.csv");
    ifstream input1("65536r2e.csv");
    int rank;
    int element;
    int x = 0;
    int i = 0;
    int z = 0;
    int max = 0;
    int row = 0;
    int flag = 0;
    int column = 0;
    int max_el = 0;
    string str;

    for (string line; getline(input, line);)
    {
        for (int z = 0; z < line.size(); z++)
        {
            if (line[z] == ',')
            {
                flag = 1;
            }
            if (flag == 1)
            {
                if (stoi(str) > max_el)
                {
                    max_el = stoi(str);
                }
                flag = 0;
                str = "";
            }
            else
            {
                str = str + line[z];
            }
        }
        if (stoi(str) > max_el)
        {
            max_el = stoi(str);
        }
        str = "";
    }

    int counter = 0;
    int RowRank = 0;
    int RankArray[max_el + 1];
    for (string line; getline(input1, line);)
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
                counter = 0;
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
    }
    for (int z = 0; z < max_el + 1; z++)
    {
        cout << "Rank Array " << z << " " << RankArray[z] << endl;
    }
    //cout << "MAX " << max_el << endl;
    return RankArray;
}