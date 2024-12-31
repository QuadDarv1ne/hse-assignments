/*
    Тема № 3 Генетические алгоритмы – 4 часа
    
    4 вариант - Задача о раскраске карты (смежные области карты должны быть окрашены в различные цвета)
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <climits>

using namespace std;

// Конфигурация
const int NUM_COLORS = 4;         // Количество доступных цветов
const int POPULATION_SIZE = 100; // Размер популяции
const int GENERATIONS = 500;     // Количество поколений
const double MUTATION_RATE = 0.1; // Вероятность мутации

// Карта в виде списка смежности
vector<vector<int>> graph = {
    {1, 2},    // Регион 0
    {0, 2, 3}, // Регион 1
    {0, 1, 3}, // Регион 2
    {1, 2}     // Регион 3
};

// Генератор случайных чисел
mt19937 rng(static_cast<unsigned>(time(nullptr)));

// Оценочная функция
int fitness(const vector<int>& chromosome) {
    int conflicts = 0;
    for (int node = 0; node < graph.size(); ++node) {
        for (int neighbor : graph[node]) {
            if (chromosome[node] == chromosome[neighbor]) {
                ++conflicts;
            }
        }
    }
    return -conflicts; // Чем меньше конфликтов, тем лучше
}

// Генерация случайной хромосомы
vector<int> createChromosome() {
    vector<int> chromosome(graph.size());
    for (int& gene : chromosome) {
        gene = rng() % NUM_COLORS;
    }
    return chromosome;
}

// Кроссовер (одноточечный)
vector<int> crossover(const vector<int>& parent1, const vector<int>& parent2) {
    int point = rng() % (graph.size() - 1) + 1;
    vector<int> child(graph.size());
    for (int i = 0; i < point; ++i) {
        child[i] = parent1[i];
    }
    for (int i = point; i < graph.size(); ++i) {
        child[i] = parent2[i];
    }
    return child;
}

// Мутация
void mutate(vector<int>& chromosome) {
    if (double(rng() % 100) / 100.0 < MUTATION_RATE) {
        int idx = rng() % chromosome.size();
        chromosome[idx] = rng() % NUM_COLORS;
    }
}

// Генетический алгоритм
vector<int> geneticAlgorithm() {
    // Создаём начальную популяцию
    vector<vector<int>> population(POPULATION_SIZE);
    for (auto& chromosome : population) {
        chromosome = createChromosome();
    }

    for (int generation = 0; generation < GENERATIONS; ++generation) {
        // Оцениваем популяцию
        sort(population.begin(), population.end(), [](const vector<int>& a, const vector<int>& b) {
            return fitness(a) > fitness(b);
        });

        // Если нашли решение без конфликтов
        if (fitness(population[0]) == 0) {
            cout << "Решение найдено на поколении " << generation << endl;
            return population[0];
        }

        // Создаём новую популяцию
        vector<vector<int>> newPopulation;
        for (int i = 0; i < POPULATION_SIZE / 2; ++i) {
            newPopulation.push_back(population[i]); // Селекция лучших
        }

        // Создаём потомков
        while (newPopulation.size() < POPULATION_SIZE) {
            int parent1Idx = rng() % (POPULATION_SIZE / 2);
            int parent2Idx = rng() % (POPULATION_SIZE / 2);
            vector<int> child = crossover(population[parent1Idx], population[parent2Idx]);
            mutate(child);
            newPopulation.push_back(child);
        }

        population = newPopulation;
    }

    // Возврат лучшего решения
    return population[0];
}

int main() {
    vector<int> solution = geneticAlgorithm();
    cout << "Лучшее решение: ";
    for (int color : solution) {
        cout << color << " ";
    }
    cout << endl;

    cout << "Конфликты: " << -fitness(solution) << endl;
    return 0;
}
