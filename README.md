# 🧑‍💼 Employee Management System using OpenMP for Parallel Sorting and Searching

This mini-project demonstrates the use of **OpenMP** for accelerating computational tasks such as sorting employee salary data in a **shared memory environment**. It highlights the effectiveness of parallelization using OpenMP for improved performance, particularly for large datasets.

---

## 🚀 Key Features

- Parallel Sorting using OpenMP (e.g. Quick Sort)
- Handles large datasets efficiently
- Command-line interface for managing employee data
- **Dockerized environment** for easy deployment and execution

---

## 🛠️ Technologies Used

- **C / C++**
- **OpenMP** for parallelization
- **Docker** for containerized deployment
- GNU Compiler (`g++`) with OpenMP flag

---

## 📁 Project Structure
- ├── Dockerfile 
- ├── README.md 
- ├── employee_management.cpp 
- ├── Makefile 
- └── input.txt


---

## 🧪 How to Run

### ✅ Compile (without Docker)

```bash
g++ -fopenmp -o emp_system employee_management.cpp
./emp_system
```

## 🐳 Using Docker (Highly Recommended)

- 1. 🔨 Build Docker Image
  ```bash
  docker build -t openmp-employee-system .
  ```
- 2. ▶️ Run the Container
  ```bash
  docker run -it openmp-employee-system
  ```
