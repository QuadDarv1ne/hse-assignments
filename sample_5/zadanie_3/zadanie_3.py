import random

# Конфигурация
NUM_COLORS = 4  # Количество доступных цветов
POPULATION_SIZE = 100  # Размер популяции
GENERATIONS = 500  # Количество поколений
MUTATION_RATE = 0.1  # Вероятность мутации

# Пример карты (графа)
graph = {
    0: [1, 2],
    1: [0, 2, 3],
    2: [0, 1, 3],
    3: [1, 2]
}

def fitness(chromosome):
    """Оценочная функция (число конфликтов)."""
    conflicts = 0
    for node, neighbors in graph.items():
        for neighbor in neighbors:
            if chromosome[node] == chromosome[neighbor]:
                conflicts += 1
    return -conflicts  # Чем меньше конфликтов, тем лучше

def create_chromosome():
    """Создаёт случайную хромосому (раскраску)."""
    return [random.randint(0, NUM_COLORS - 1) for _ in range(len(graph))]

def crossover(parent1, parent2):
    """Одноточечный кроссовер."""
    point = random.randint(1, len(graph) - 1)
    child = parent1[:point] + parent2[point:]
    return child

def mutate(chromosome):
    """Мутация хромосомы."""
    if random.random() < MUTATION_RATE:
        idx = random.randint(0, len(graph) - 1)
        chromosome[idx] = random.randint(0, NUM_COLORS - 1)

def genetic_algorithm():
    """Генетический алгоритм для задачи о раскраске карты."""
    # Создаём начальную популяцию
    population = [create_chromosome() for _ in range(POPULATION_SIZE)]

    for generation in range(GENERATIONS):
        # Оцениваем популяцию
        population.sort(key=fitness, reverse=True)

        # Если нашли решение без конфликтов
        if fitness(population[0]) == 0:
            print(f"Решение найдено на поколении {generation}")
            return population[0]

        # Отбор лучших
        new_population = population[:POPULATION_SIZE // 2]

        # Создание потомков
        while len(new_population) < POPULATION_SIZE:
            parent1, parent2 = random.sample(population[:10], 2)  # Выбираем из топ-10
            child = crossover(parent1, parent2)
            mutate(child)
            new_population.append(child)

        population = new_population

    # Возврат лучшего найденного решения
    return population[0]

if __name__ == "__main__":
    solution = genetic_algorithm()
    print("Лучшее решение:", solution)
    print("Конфликты:", -fitness(solution))
