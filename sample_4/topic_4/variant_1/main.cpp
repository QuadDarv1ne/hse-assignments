#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>   // для std::accumulate
#include <random>    // для генерации случайных чисел
#include <chrono>    // для генерации случайных чисел с использованием времени
#include <algorithm> // для std::count

using namespace std;

// Функция для генерации файла с случайными числами
void generateFile(const string& filename, size_t count, int minValue, int maxValue) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Ошибка: Невозможно создать файл!\n";
        return;
    }

    // Генератор случайных чисел с использованием устройства случайных чисел и времени как начального значения
    random_device rd;  // Источник случайных чисел
    mt19937 gen(rd()); // Генератор случайных чисел
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

// Функция для подсчёта количества вхождений конкретного числа
int countOccurrences(const vector<int>& numbers, int target) {
    return count(numbers.begin(), numbers.end(), target); // Теперь эта функция доступна
}

int main() {
    const string filename = "numbers.txt";
    const size_t numberCount = 5000;
    const int minValue = 1, maxValue = 100;

    // Шаг 1: Генерация файла с случайными числами
    generateFile(filename, numberCount, minValue, maxValue);
    cout << "Файл \"" << filename << "\" сгенерирован с " << numberCount << " случайными числами.\n";

    // Шаг 2: Чтение чисел из файла
    vector<int> numbers = readFile(filename);
    if (numbers.empty()) {
        cerr << "Ошибка: Не удалось прочитать числа из файла.\n";
        return 1;
    }

    // Шаг 3: Вычисление среднего значения
    double average = calculateAverage(numbers);
    cout << "Среднее значение чисел: " << average << "\n";

    // Шаг 4: Подсчёт вхождений конкретного числа
    int target = 42; // Пример целевого числа
    int occurrences = countOccurrences(numbers, target);
    cout << "Число " << target << " встречается " << occurrences << " раз(а) в файле.\n";

    return 0;
}
