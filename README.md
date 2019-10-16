# Dynamic-Workload-Prediction-Tool
This tool is suitable for Trace driven simulation. It is based on Parallel models such as MPI, OpenMP and CUDA.

All programs were tested and executed on the University of Florida's supercomputer Hipergator.
Results were obtained by varying the number of nodes from 1 to 32. 
----------------------------------------------------------------------------------------------
Extract all files in a directory.
Make sure that all timestep files are there in the same directory.

1] To run MPI:
    (a) use MPI.cpp file.
    (b) run mpi.sh file using "bash mpi.sh" command and vary the number of ranks and 
      input files in the last line of the mpi.sh file.

2] To run MPI + OpenMP:
    (a)use OpenMP.cpp file.
    (b) run the script openmp.sh

3] To run MPI + Cuda:
    (a)use CUDA.cu file.
    (b) run the script cuda.sh
