/*
    [ Найти математический размах (spread) чисел ]
    
    Математический размах (spread) чисел — это разница между максимальным и минимальным значением в наборе данных.

    Шаги:
    - Пройти по вектору, чтобы найти максимальное и минимальное значения.
    - Вычесть минимальное значение из максимального, чтобы получить размах.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm> // для std::count

using namespace std;

// Функция для нахождения математического размаха (spread) чисел
int findRange(const std::vector<int>& numbers) {
    if (numbers.empty()) {
        std::cerr << "Ошибка: Файл пуст!\n";
        return 0;
    }

    // Находим минимальное и максимальное значения в векторе
    auto minMax = std::minmax_element(numbers.begin(), numbers.end());
    int minValue = *minMax.first;
    int maxValue = *minMax.second;

    // Вычисляем и возвращаем размах
    return maxValue - minValue;
}

/*
    Объяснение:
    - Мы используем std::minmax_element, чтобы найти минимальное и максимальное значения в векторе.
    - После этого просто вычитаем минимальное значение из максимального, чтобы получить размах.
    - Если вектор пуст, выводится ошибка.
*/