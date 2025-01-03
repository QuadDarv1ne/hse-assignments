/*
    OpenMP — это API для многопоточных вычислений, и здесь мы будем использовать потоки вместо процессов.
*/

#include <iostream>
#include <omp.h>
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

int main() {
    #pragma omp parallel num_threads(N + 1) // N пчел и 1 медведь
    {
        int id = omp_get_thread_num();
        if (id == 0) {
            bear();
        } else {
            bee(id);
        }
    }

    return 0;
}

/*
    Пояснение:
    1) В этом коде используется `OpenMP` для многопоточности.
       Здесь мы создаем N+1 потоков — один для медведя и N для пчел.
    2) Мы также используем атомарные операции, чтобы безопасно обновлять количество меда в горшке.
*/

/*
    Выводы:
    В обоих вариантах — с использованием MPI или OpenMP — мы моделируем задачу с птенцами и их матерью.
    Каждый птенец по очереди ест из миски, а когда еда заканчивается, мать добавляет порции пищи.
    Алгоритм «Портфель задач» помогает синхронизировать действия птенцов и матери, чтобы все происходило правильно и без гонок потоков.
*/