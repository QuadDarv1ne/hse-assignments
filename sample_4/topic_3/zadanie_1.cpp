/* 
    Задание VII: Определение общего числа тредов и уникальных номеров тредов

    Для выполнения этого задания, программа на OpenMP должна получить общее количество тредов и уникальные номера тредов.
*/

#include <stdio.h>
#include <omp.h>

int main() {
    // Ожидание начала параллельного выполнения
    #pragma omp parallel
    {
        int nthreads = omp_get_num_threads();  // Общее количество тредов
        int thread_id = omp_get_thread_num();  // Уникальный номер треда

        std::cout << "Всего тредов: " << nthreads << ", Тред " << thread_id << std::endl;
    }

    return 0;
}

/*
    `omp_get_num_threads()` возвращает общее количество тредов.
    `omp_get_thread_num()` возвращает уникальный идентификатор каждого треда, который в пределах от 0 до n-1.
*/