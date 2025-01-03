#include <iostream>
#include <mpi.h>

const int n = 100;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;

    // Получаем номер текущего процесса и общее количество процессов
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int a[n][n], b[n][n], c[n][n];

    // Инициализация матриц a и b только на процессе с рангом 0
    if (rank == 0) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                a[i][j] = i + j;
                b[i][j] = i - j;
            }
        }
    }

    // Разделяем строки матриц между процессами
    int rows_per_process = n / size;
    int local_a[rows_per_process][n], local_b[rows_per_process][n], local_c[rows_per_process][n];

    // Рассылаем части матриц а и b каждому процессу
    MPI_Scatter(a, rows_per_process * n, MPI_INT, local_a, rows_per_process * n, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(b, rows_per_process * n, MPI_INT, local_b, rows_per_process * n, MPI_INT, 0, MPI_COMM_WORLD);

    // Параллельное сложение матриц (каждый процесс выполняет сложение своей части)
    for (int i = 0; i < rows_per_process; i++) {
        for (int j = 0; j < n; j++) {
            local_c[i][j] = local_a[i][j] + local_b[i][j];
        }
    }

    // Собираем результат обратно в процесс с рангом 0
    MPI_Gather(local_c, rows_per_process * n, MPI_INT, c, rows_per_process * n, MPI_INT, 0, MPI_COMM_WORLD);

    // Выводим результат только на процессе с рангом 0
    if (rank == 0) {
        std::cout << "Результат сложения матриц:" << std::endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                std::cout << c[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    MPI_Finalize();
    return 0;
}
