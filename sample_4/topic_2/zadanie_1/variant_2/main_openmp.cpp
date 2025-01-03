#include <iostream>
#include <omp.h>
#include <atomic>

#define F 10  // Количество порций пищи в миске
#define N 5   // Количество птенцов
#define M 3   // Количество пищи, которое мать добавляет в миску

std::atomic<int> food_bowl(0); // Потокобезопасная переменная для миски с едой

void chick(int id) {
    while (true) {
        if (food_bowl.load() > 0) {
            food_bowl.fetch_add(-1); // Птенец съедает порцию пищи
            std::cout << "Chick " << id << " eats food. Bowl: " << food_bowl.load() << "/" << F << std::endl;
        }
    }
}

void mother() {
    while (true) {
        if (food_bowl.load() == 0) {
            food_bowl.fetch_add(M); // Мать добавляет еду в миску
            std::cout << "Mother refills the bowl with " << M << " portions of food. Bowl: " << food_bowl.load() << "/" << F << std::endl;
        }
    }
}

int main() {
    #pragma omp parallel num_threads(N + 1) // N птенцов и 1 мать
    {
        int id = omp_get_thread_num();
        if (id == 0) {
            mother();  // Мать
        } else {
            chick(id);  // Птенцы
        }
    }

    return 0;
}

/*
    Пояснение:
    1) В этом коде используется OpenMP для многопоточности.
       Мы создаем N+1 потоков: один поток для матери и N потоков для птенцов.
    2) Атомарные операции на переменной food_bowl обеспечивают безопасность доступа к ресурсу (миске с едой).
*/

/*
    Выводы:
    В обоих вариантах — с использованием MPI или OpenMP — мы моделируем задачу с птенцами и их матерью.
    Каждый птенец по очереди ест из миски, а когда еда заканчивается, мать добавляет порции пищи.
    Алгоритм «Портфель задач» помогает синхронизировать действия птенцов и матери, чтобы все происходило правильно и без гонок потоков.
*/