#!/bin/bash
#SBATCH --job-name=serial
#SBATCH --mail-type=ALL
#SBATCH --mail-user=kshitijraj@ufl.edu
#SBATCH --account=eel6763
#SBATCH --qos=eel6763
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1
#SBATCH --mem-per-cpu=2000mb
#SBATCH -t 00:15:00
#SBATCH -o hw.txt
#SBATCH -e hw.err
module load ufrc
module load gcc/7.3.0 openmpi
mpicxx -std=c++11 -O3 OpenMP.cpp -o OpenMP -fopenmp
srun -n 1 --mpi=pmix_v1 ./OpenMP 32