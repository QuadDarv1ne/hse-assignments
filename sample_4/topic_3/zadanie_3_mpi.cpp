#include <iostream>
#include <cmath>
#include <mpi.h>

const double tmax = 10.0;  // Максимальное значение t
const double tau = 0.001;  // Шаг по времени
const int num_steps = tmax / tau;  // Количество шагов

// Функция f(t, y) для ОДУ
double f(double t, double y) {
    return -y + std::sin(t);  // Пример уравнения: y' = -y + sin(t)
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;

    // Получаем номер текущего процесса и общее количество процессов
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Разделение работы на процессы
    int steps_per_process = num_steps / size;
    int remainder = num_steps % size;

    // Индексы для обработки шага
    int start_step = rank * steps_per_process + std::min(rank, remainder);
    int end_step = start_step + steps_per_process + (rank < remainder ? 1 : 0);

    double y[num_steps], y_pred[num_steps], y_corr[num_steps];

    // Инициализация начальных условий только для процесса с rank = 0
    if (rank == 0) {
        y[0] = 1.0;  // Начальное значение y при t = 0
    }

    // Рассылаем начальные условия всем процессам
    MPI_Bcast(&y[0], 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Параллельный расчет с использованием предиктора-корректора
    for (int i = start_step + 1; i < end_step; i++) {
        double t = i * tau;
        
        // Прогноз (предсказание)
        y_pred[i] = y[i-1] + tau * f(t - tau, y[i-1]);
        
        // Коррекция
        y_corr[i] = y[i-1] + tau * f(t, y_pred[i]);
        
        // Обновление значения
        y[i] = 0.5 * (y_pred[i] + y_corr[i]);
    }

    // Собираем результаты на процессе с рангом 0
    MPI_Gather(&y[start_step], end_step - start_step, MPI_DOUBLE, y, 
               steps_per_process + (rank < remainder ? 1 : 0), MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Вывод результатов только на процессе с рангом 0
    if (rank == 0) {
        for (int i = 0; i < num_steps; i++) {
            std::cout << "t = " << i * tau << ", y = " << y[i] << std::endl;
        }
    }

    MPI_Finalize();
    return 0;
}
