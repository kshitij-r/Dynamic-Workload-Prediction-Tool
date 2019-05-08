module load ufrc
module load gcc/7.3.0 openmpi
mpicxx -std=c++11 -O3 MPI.cpp -o mpi
srun -n 4 --mpi=pmix_v1 ./mpi 50 > finaloutput.txt