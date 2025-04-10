FROM gcc:latest

WORKDIR /app

# Don’t copy anything or compile yet

# Compile at runtime and run
CMD ["bash", "-c", "gcc -fopenmp -o omp_sort omp_sort_employees.c && ./omp_sort"]
