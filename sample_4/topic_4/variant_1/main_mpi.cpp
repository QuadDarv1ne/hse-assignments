/*
    Чтобы интегрировать MPI в этот код, мы можем распараллелить части программы, такие как чтение файла и подсчёт вхождений чисел.
    
    В данном случае, код можно модифицировать следующим образом:
    1) Чтение и генерация данных: каждый процесс может работать с частью данных, чтобы ускорить обработку.
    2) Подсчёт вхождений: каждый процесс может подсчитывать количество вхождений определённого числа в своей части данных, а затем результаты собираются в один процесс.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <random>
#include <chrono>
#include <algorithm>
#include <mpi.h>

using namespace std;

// Функция для генерации файла с случайными числами
void generateFile(const string& filename, size_t count, int minValue, int maxValue) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Ошибка: Невозможно создать файл!\n";
        return;
    }

    // Генератор случайных чисел с использованием устройства случайных чисел и времени как начального значения
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(minValue, maxValue);

    // Заполнение файла случайными числами
    for (size_t i = 0; i < count; ++i) {
        outFile << dis(gen) << (i < count - 1 ? " " : "");
    }

    outFile.close();
}

// Функция для чтения чисел из файла в вектор
vector<int> readFile(const string& filename) {
    vector<int> numbers;
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Ошибка: Невозможно открыть файл!\n";
        return numbers;
    }

    int num;
    while (inFile >> num) {
        numbers.push_back(num);
    }
    inFile.close();
    return numbers;
}

// Функция для вычисления среднего значения чисел
double calculateAverage(const vector<int>& numbers) {
    if (numbers.empty()) return 0.0;
    long long sum = accumulate(numbers.begin(), numbers.end(), 0LL);
    return static_cast<double>(sum) / numbers.size();
}

// Функция для подсчёта количества вхождений конкретного числа в массив
int countOccurrences(const vector<int>& numbers, int target) {
    return count(numbers.begin(), numbers.end(), target);
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const string filename = "numbers.txt";
    const size_t numberCount = 5000;
    const int minValue = 1, maxValue = 100;
    
    if (rank == 0) {
        // Шаг 1: Генерация файла с случайными числами (только для процесса 0)
        generateFile(filename, numberCount, minValue, maxValue);
        cout << "Файл \"" << filename << "\" сгенерирован с " << numberCount << " случайными числами.\n";
    }

    // Шаг 2: Чтение чисел из файла
    // Каждый процесс читает файл и делит данные на части
    vector<int> numbers;
    if (rank == 0) {
        numbers = readFile(filename);
    }

    // Разделяем данные между процессами
    size_t localSize = numberCount / size;
    vector<int> localNumbers(localSize);

    // Распределяем части данных среди процессов
    MPI_Scatter(numbers.data(), localSize, MPI_INT, localNumbers.data(), localSize, MPI_INT, 0, MPI_COMM_WORLD);

    // Шаг 3: Вычисление среднего значения
    double localAverage = calculateAverage(localNumbers);
    double globalAverage;

    // Собираем средние значения от всех процессов
    MPI_Reduce(&localAverage, &globalAverage, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        globalAverage /= size;  // Среднее значение от всех процессов
        cout << "Среднее значение чисел: " << globalAverage << "\n";
    }

    // Шаг 4: Подсчёт вхождений конкретного числа
    int target = 42;
    int localOccurrences = countOccurrences(localNumbers, target);
    int globalOccurrences;

    // Собираем общее количество вхождений
    MPI_Reduce(&localOccurrences, &globalOccurrences, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        cout << "Число " << target << " встречается " << globalOccurrences << " раз(а) в файле.\n";
    }

    MPI_Finalize();
    return 0;
}

/*
[ Компиляция и запуск ]

Компиляция:
```bash
mpic++ -o mpi_example mpi_example.cpp
```

Запуск:
```bash
mpirun -np 4 ./mpi_example
```

Этот код будет выполняться на 4 процессах (или на другом количестве, в зависимости от параметра -np).
Программа генерирует случайные числа, делит работу по процессам, а затем собирает результаты для вычисления среднего значения и подсчёта вхождений числа.
*/
