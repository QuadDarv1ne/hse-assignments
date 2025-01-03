/*
    MPI — это интерфейс для многопроцессорных вычислений, поэтому каждый процесс будет имитировать пчелу или медведя.
*/

#include <iostream>
#include <mpi.h>
#include <atomic>

#define H 10  // Количество порций меда
#define N 5   // Количество пчел

std::atomic<int> honey_pot(0); // Потокобезопасная переменная для горшка с медом

void bee(int id) {
    while (true) {
        int current_honey = honey_pot.load();
        if (current_honey < H) {
            honey_pot.fetch_add(1);  // Пчела приносит мед
            std::cout << "Bee " << id << " adds honey. Pot: " << current_honey + 1 << "/" << H << std::endl;
            if (current_honey + 1 == H) {
                std::cout << "Bee " << id << " fills the pot and wakes up the bear." << std::endl;
            }
        }
    }
}

void bear() {
    while (true) {
        if (honey_pot.load() == H) {
            std::cout << "Bear wakes up and eats honey!" << std::endl;
            honey_pot.store(0);  // Медведь съедает весь мед, горшок снова пуст
            break;
        }
    }
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        bear();
    } else {
        bee(rank);
    }

    MPI_Finalize();
    return 0;
}

/*
    Пояснение:
    1) honey_pot — это переменная, которая отслеживает количество меда в горшке.
       Она является атомарной, чтобы избежать гонки потоков.
    2) Функция bee(int id) — это модель работы пчелы, которая добавляет мед в горшок.
       Пчела, которая приносит последнюю порцию, пробуждает медведя.
    3) Функция bear() — это модель работы медведя.
       Он просыпается, когда горшок полностью заполнен, съедает мед и затем цикл повторяется.
    4) В основном процессе используется MPI, чтобы распределить работу между различными процессами.
       Процесс с rank == 0 выполняет роль медведя, а все остальные процессы — это пчелы.
*/

/*
    Выводы:
    В обоих вариантах — с использованием MPI или OpenMP — мы моделируем задачу с птенцами и их матерью.
    Каждый птенец по очереди ест из миски, а когда еда заканчивается, мать добавляет порции пищи.
    Алгоритм «Портфель задач» помогает синхронизировать действия птенцов и матери, чтобы все происходило правильно и без гонок потоков.
*/