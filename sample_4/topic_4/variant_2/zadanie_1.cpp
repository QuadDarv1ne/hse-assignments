/*
    [ Найти число уникальных чисел и их количество ]

    Для решения этой задачи нам нужно:
    - Прочитать числа из файла.
    - Подсчитать, сколько раз каждое число встречается (т.е. частота каждого числа).
    - Найти уникальные числа и их количество.

    Для этого можно использовать std::map или std::unordered_map, чтобы хранить числа и их частоту.

    Шаги:
    - Пройти по числам в векторе.
    - Вставить каждое число в карту, где ключом будет число, а значением — количество его вхождений.
    - В конце карта будет содержать все уникальные числа и их частоту.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm> // для std::count

using namespace std;

// Функция для чтения чисел из файла
std::vector<int> readFile(const std::string& filename) {
    std::vector<int> numbers;
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Ошибка: Невозможно открыть файл!\n";
        return numbers;
    }

    int num;
    while (inFile >> num) {
        numbers.push_back(num);
    }
    inFile.close();
    return numbers;
}

// Функция для нахождения уникальных чисел и их количества
void countUniqueNumbers(const std::vector<int>& numbers) {
    std::map<int, int> frequency;

    // Подсчитываем частоту каждого числа
    for (int num : numbers) {
        frequency[num]++;
    }

    // Выводим уникальные числа и их количество
    std::cout << "Уникальные числа и их количество:\n";
    for (const auto& pair : frequency) {
        std::cout << "Число: " << pair.first << ", Количество: " << pair.second << "\n";
    }

    std::cout << "Всего уникальных чисел: " << frequency.size() << "\n";
}

/*
    Объяснение:
    - Функция countUniqueNumbers проходит по вектору чисел, и для каждого числа увеличивает его счётчик в map.
    - После того как все числа обработаны, мы выводим уникальные числа и их количество.
    - В конце выводим, сколько уникальных чисел было найдено, используя размер карты.
*/