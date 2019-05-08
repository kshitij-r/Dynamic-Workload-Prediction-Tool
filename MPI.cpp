#include "header.h"
#include "hash.h"
#include<map>
#include<unordered_map>
#include <mpi.h>
#include <time.h>
#include<iterator>
#include<string.h>
#include <sstream>
typedef std::unordered_multimap<string, int> mp;
typedef std::unordered_multimap<string, pair<int, int>> mvmnt;
typedef mp::iterator It_buf;
typedef mvmnt::iterator it_buf1;

/*   ttype: type to use for representing time */
typedef double ttype;
ttype tdiff(struct timespec a, struct timespec b)/* Find the time difference. */{
  ttype dt = (( b.tv_sec - a.tv_sec ) + ( b.tv_nsec - a.tv_nsec ) / 1E9);
  return dt;
  }

struct timespec now()/* Return the current time. */{
  struct timespec t;
  clock_gettime(CLOCK_REALTIME, &t);
  return t;
}

using namespace std;

int main(int argc, char **argv)
{
    int myrank, p;
    struct timespec begin, end;
    
    //fp = fopen("mpitime.txt","w");
    double time_spent;
    MPI_Status status;
    ofstream op1;
    string time = "thread8-50";
    //cout<<"File created"<<endl;
    op1.open(time);
    begin = now();
    ofstream final;
    final.open("finaloutput.txt");
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    //cout<<"Rank "<<p<<endl;
    int N= atof(argv[1]);
    int a,element,flag,x,fifcounter;
    int xx = 0;
    int yy = 1;
    string time_array[p]={};
    string file_array[N] = {};
    string strY = "";
    for (int z = 0; z < N; z++)
    {
        strY = "timestep" + to_string(xx) + "-" + to_string(yy) + "updated.csv";
        file_array[z] = strY;
        xx++;
        yy++;
    }

    if(myrank==0){
    int offset=0;
    long long int average=N/p;
    int extra = N%p;

    for(int k=0;k<p;k++){
        long long int num=(k<extra) ? average + 1 : average;
        MPI_Send(&num,1,MPI_LONG_LONG_INT, k , 0, MPI_COMM_WORLD);
        MPI_Send(&offset, 1, MPI_INT, k, 1, MPI_COMM_WORLD);
        offset=offset+num;
        
    }
    }
    
    long long int num1;
    int offset1;
    
    MPI_Recv(&num1,1,MPI_LONG_LONG_INT,0,0,MPI_COMM_WORLD,&status);
    MPI_Recv(&offset1, 1, MPI_INT,0, 1, MPI_COMM_WORLD, &status);
    
    for(int kk=offset1; kk<offset1+num1; kk++){
        
        
        string strZ ="Timestep" + to_string(kk); 
        ifstream input(file_array[kk]);
        ofstream input1;
        input1.open("abcd.txt");
        ifstream input2("abcd.txt");
        ofstream input3;
        input3.open("efgh.txt");
        ofstream op;
        op.open(strZ);
        elementToprocessor obj;
        hash_table(obj);
        mp mp1;
        mvmnt mvmnt1;
        It_buf iter;
        it_buf1 mvmntiter;
        string str, str1, gpid, oldnewrank;
        int Scounter = 0, ifflag = 0;
        int flag1 = 0, flag1sec = 0, ct = 0, abcdcounter = 0, l = 0, lsec = 0, index1 = 0, index2 = 1, thcounter = 0, focounter = 0, counter = 0, max = 0;
        for (int i = 1; i < obj.max; i++)
        {
            if (obj.r2e_hash[i] > max)
            {
                max = obj.r2e_hash[i];
            }
    }

    //cout<<"This is the max rank "<<max<<"it ends here"<<endl;
    long int Rankcounter[max + 1][2] = {};

    for (string line; getline(input, line);)
    {
        counter = 0;
        l++;
        thcounter=0;
        gpid ="";

        for (int z = 0; z < line.size(); z++)
        {
            if (line[z] == ',')
            {
                flag = 1;
                thcounter++;
                counter++;
            }
            if (flag == 1)
            {
                if (counter == 8)
                {
                    element = stoi(str);
                    // cout<<"This is the rank "<<obj.r2e_hash[element]<<"for the element"<<element;
                }
                if(thcounter <5)
                {
                    gpid = gpid + str+".";
                }

                flag = 0;
                str = "";
            }
            else
            {
                str = str + line[z];
            }
        }
        
        if (l == 1 && flag1 == 0)
        {
            flag1 = 1;
            x = stoi(str);
        }
    
        if (stoi(str) == x)
        {   
            Rankcounter[obj.r2e_hash[element]][0]++;
            mp1.insert(make_pair(gpid,obj.r2e_hash[element]));
            input1 << gpid << "," << obj.r2e_hash[element] << "\n";
            if(ifflag==0){
                Scounter++;
            }
           // cout<< gpid << "," << obj.r2e_hash[element] <<endl;
        }
        else
        {
            ifflag = 1;
            input1.close();
            iter  = (mp1.find(gpid));
                if (obj.r2e_hash[element] != (iter->second))
                {
                    oldnewrank =to_string(iter->second)+","+ to_string(obj.r2e_hash[element]) ;
                    if(mvmnt1.empty())
                    {
                        counter = 1;
                        mvmnt1.insert({oldnewrank, make_pair(counter, kk)});
                    }
                    else
                    {
                    if(mvmnt1.count(oldnewrank) == 0)
                    {
                        counter = 1;
                        mvmnt1.insert({oldnewrank, make_pair(counter,kk)});
                    }
                    else
                    {
                        mvmntiter = mvmnt1.find(oldnewrank);
                        mvmntiter->second.first++;                        
                    }
                    }                 
                }        
            Rankcounter[obj.r2e_hash[element]][1]++;    
        }
        str="";
    }
    for(auto itr=mvmnt1.begin();itr!=mvmnt1.end();itr++){
      cout <<itr->first<<","<<itr->second.first<<","<<itr->second.second<<endl;
    }
   
    for(int i=0;i<max;i++){
        op<< i <<","<< Rankcounter[i][0]<<","<< to_string(kk)<<endl;
    }
    for(int i=0;i<max;i++){
        op<< i <<","<< Rankcounter[i][1]<<","<< to_string(kk+1)<<endl;
    }
    op.close();
   
}
final.close();
 MPI_Finalize();
 
end = now();
time_spent = tdiff(begin, end);
op1 <<"Time spent "<<time_spent<<endl;
op1.close();
    
    return 0;
}