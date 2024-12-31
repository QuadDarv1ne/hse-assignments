class Stack:
    """Класс для реализации стека"""
    def __init__(self):
        self.items = []

    def push(self, item):
        self.items.append(item)

    def pop(self):
        if not self.is_empty():
            return self.items.pop()
        raise IndexError("Попытка извлечения из пустого стека")

    def peek(self):
        if not self.is_empty():
            return self.items[-1]
        return None

    def is_empty(self):
        return len(self.items) == 0

    def size(self):
        return len(self.items)


def tsp_dfs(graph, start_node):
    """
    Решение задачи коммивояжера с использованием DFS.
    :param graph: матрица смежности графа (2D список)
    :param start_node: начальная вершина
    :return: минимальная длина пути и соответствующий путь
    """
    num_nodes = len(graph)
    stack = Stack()
    stack.push((start_node, [start_node], 0))  # текущий узел, посещённые узлы, длина пути
    min_path = None
    min_distance = float('inf')

    while not stack.is_empty():
        current_node, path, distance = stack.pop()

        # Если посещены все узлы и есть путь к начальной вершине
        if len(path) == num_nodes and graph[current_node][start_node] > 0:
            total_distance = distance + graph[current_node][start_node]
            if total_distance < min_distance:
                min_distance = total_distance
                min_path = path + [start_node]

        # Продолжаем обход
        for neighbor in range(num_nodes):
            if neighbor not in path and graph[current_node][neighbor] > 0:
                stack.push((neighbor, path + [neighbor], distance + graph[current_node][neighbor]))

    return min_distance, min_path


# Пример использования
if __name__ == "__main__":
    # Матрица смежности графа
    graph = [
        [0, 10, 15, 20],
        [10, 0, 35, 25],
        [15, 35, 0, 30],
        [20, 25, 30, 0]
    ]
    start_node = 0

    min_distance, min_path = tsp_dfs(graph, start_node)
    print("Минимальная длина пути:", min_distance)
    print("Кратчайший путь:", min_path)
