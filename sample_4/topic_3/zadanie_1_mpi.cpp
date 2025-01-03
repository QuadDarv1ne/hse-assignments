#include <stdio.h>
#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
    // Инициализация MPI
    MPI_Init(&argc, &argv);

    int rank, size;

    // Получаем номер текущего процесса (rank) и общее количество процессов (size)
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Выводим информацию о количестве процессов и номере текущего процесса
    std::cout << "Всего процессов: " << size << ", Процесс " << rank << std::endl;

    // Завершаем работу с MPI
    MPI_Finalize();

    return 0;
}
