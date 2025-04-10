#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#define MAX_EMPLOYEES 1000
#define MAX_LINE_LENGTH 256

typedef struct {
    int id;
    char name[50];
    int age;
    float salary;
    int experience;
} Employee;

Employee employees[MAX_EMPLOYEES];
int employeeCount = 0;

// Read CSV file
void readCSV(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("❌ Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    fgets(line, sizeof(line), file); // Skip header

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d,%49[^,],%d,%f,%d",
               &employees[employeeCount].id,
               employees[employeeCount].name,
               &employees[employeeCount].age,
               &employees[employeeCount].salary,
               &employees[employeeCount].experience);
        employeeCount++;
    }

    fclose(file);
}

// Write CSV file
void writeCSV(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("❌ Error writing file");
        exit(EXIT_FAILURE);
    }

    // Keep headers exactly as input file
    fprintf(file, "EmployeeID,Name,Age,Salary,Experience\n");
    for (int i = 0; i < employeeCount; i++) {
        fprintf(file, "%d,%s,%d,%.2f,%d\n",
                employees[i].id,
                employees[i].name,
                employees[i].age,
                employees[i].salary,
                employees[i].experience);
    }

    fclose(file);
}

// Swap utility
void swap(Employee* a, Employee* b) {
    Employee temp = *a;
    *a = *b;
    *b = temp;
}

// Comparator
int compare(Employee a, Employee b, int option) {
    switch (option) {
        case 1: return a.id - b.id;
        case 2: return (a.salary > b.salary) - (a.salary < b.salary);
        case 3: return a.age - b.age;
        case 4: return a.experience - b.experience;
        default: return 0;
    }
}

// QuickSort with OpenMP
void quickSort(int low, int high, int option) {
    if (low < high) {
        int pivot = low;
        int i = low, j = high;

        while (i < j) {
            while (i <= high && compare(employees[i], employees[pivot], option) <= 0)
                i++;
            while (compare(employees[j], employees[pivot], option) > 0)
                j--;
            if (i < j)
                swap(&employees[i], &employees[j]);
        }
        swap(&employees[pivot], &employees[j]);

        #pragma omp parallel sections
        {
            #pragma omp section
            quickSort(low, j - 1, option);
            #pragma omp section
            quickSort(j + 1, high, option);
        }
    }
}

// Styled Menu
void printMenu() {
    printf("\n=====================================================\n");
    printf("🛠️  EMPLOYEE DATA MANAGEMENT TOOL - QuickSort + OpenMP\n");
    printf("=====================================================\n");
    printf("👨‍💼 Choose Sorting Option:\n");
    printf("  1️⃣  Sort by Employee ID\n");
    printf("  2️⃣  Sort by Salary\n");
    printf("  3️⃣  Sort by Age\n");
    printf("  4️⃣  Sort by Experience\n");
    printf("  5️⃣  Exit\n");
    printf("=====================================================\n");
    printf("Enter your choice: ");
}

int main() {
    printf("\n🌟 Welcome to the Employee Data Management Tool 🌟\n");
    readCSV("employee_data1.csv");

    int choice;
    do {
        printMenu();
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 4) {
            double start = omp_get_wtime();
            quickSort(0, employeeCount - 1, choice);
            double end = omp_get_wtime();

            writeCSV("sorted_employees.csv");
            printf("✅ Sorting completed in %.4f seconds.\n", end - start);
            printf("📁 Output written to 'sorted_employees.csv'.\n");
        } else if (choice != 5) {
            printf("❌ Invalid choice. Please try again.\n");
        }

    } while (choice != 5);

    printf("\n👋 Thank you for using the Employee Data Management Tool. Goodbye!\n");
    return 0;
}
