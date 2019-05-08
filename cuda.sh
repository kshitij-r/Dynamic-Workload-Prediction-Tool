#!/bin/bash
#SBATCH --job-name=myMPIGPUjob
#SBATCH --mail-type=ALL
#SBATCH --output=mpicudaout.txt
#SBATCH --error=mpicudaerr.txt
#SBATCH --mail-user=kaustubh.shukla@ufl.edu
#SBATCH --account=eel6763
#SBATCH --qos=eel6763
#SBATCH --time=00:30:00
#SBATCH --nodes=16
#SBATCH --ntasks-per-node=1
#SBATCH --partition=gpu
#SBATCH --gres=gpu:tesla:1

srun --mpi=pmix_v1 ./cudaexe 50