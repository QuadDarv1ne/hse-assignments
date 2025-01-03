/*
    Задание VIII: Сложение матриц с использованием OpenMP

    Для сложения матриц a[n][n] и b[n][n] с получением матрицы c[n][n], можно использовать директиву OpenMP #pragma omp parallel for schedule(dynamic).
*/

#include <iostream>
#include <omp.h>

const int n = 100;

int main() {
    int a[n][n], b[n][n], c[n][n];

    // Инициализация матриц a и b
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = i + j;
            b[i][j] = i - j;
        }
    }

    // Параллельное сложение матриц
    #pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }

    // Вывод результата
    std::cout << "Результат сложения матриц:" << std::endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << c[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}