# HPC.OpenMP.ParallelProgramming
 
Explored shared-memory parallel programming using OpenMP in C++.
 
## What I Did
 
- Created parallel regions and measured how threads divide work among themselves
- Parallelized a vector computation loop using `#pragma omp parallel for`
- Observed work distribution across 4 threads with N = 20 iterations
- Used reduction clause to safely compute a sum across multiple threads
- Demonstrated a race condition and fixed it using `#pragma omp atomic`
- Compared static and dynamic scheduling strategies and measured execution times
- Measured speedup with 1, 2, and 4 threads on a vector computation
## Results
 
### Work Distribution (N = 20, 4 threads)
 
| Thread | Iterations |
|---|---|
| 0 | 0, 1, 2, 3, 4 |
| 1 | 5, 6, 7, 8, 9 |
| 2 | 10, 11, 12, 13, 14 |
| 3 | 15, 16, 17, 18, 19 |
 
### Scheduling (N = 100,000)
 
| Method | Time (seconds) |
|---|---|
| Static | 0.016 |
| Dynamic | 0.039 |
 
### Speedup (N = 10,000,000)
 
| Threads | Time (seconds) | Speedup |
|---|---|---|
| 1 | 0.015 | 1.00 |
| 2 | 0.015 | 1.00 |
| 4 | 0.018 | 0.83 |
 
## Key Takeaways
 
- Parallel loops with independent iterations scale easily with `#pragma omp parallel for`
- Shared variables without synchronization cause race conditions and wrong results
- Static scheduling works well for equal workloads, dynamic is better for unequal ones
- Parallelism does not always improve speed — thread overhead can outweigh the benefit for small tasks
## Tools
 
- C++
- OpenMP
- VS Code + w64devkit (GCC 16.2)
