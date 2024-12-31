/*
    Тема № 4 Итерационные алгоритмы оптимизации – 4 часа

    Задача о минимальном остове (на базе остовного леса)
*/

//Реализация на C++ (Алгоритм Прима)

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

// Граф в виде матрицы смежности
vector<vector<int>> graph = {
    {0, 2, 0, 6, 0},
    {2, 0, 3, 8, 5},
    {0, 3, 0, 0, 7},
    {6, 8, 0, 0, 9},
    {0, 5, 7, 9, 0}
};

void primMST(const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<bool> inMST(n, false);  // Указывает, входит ли вершина в остовное дерево
    vector<int> key(n, INF);      // Минимальный вес ребра для каждой вершины
    vector<int> parent(n, -1);    // Хранит родительскую вершину для построения дерева

    key[0] = 0; // Начинаем с вершины 0
    for (int count = 0; count < n - 1; ++count) {
        // Выбираем минимальное ребро
        int minKey = INF, u = -1;
        for (int v = 0; v < n; ++v) {
            if (!inMST[v] && key[v] < minKey) {
                minKey = key[v];
                u = v;
            }
        }

        inMST[u] = true; // Добавляем вершину в остовное дерево

        // Обновляем ключевые значения для соседей вершины u
        for (int v = 0; v < n; ++v) {
            if (graph[u][v] && !inMST[v] && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    // Вывод остовного дерева
    cout << "Ребро \tВес\n";
    for (int i = 1; i < n; ++i) {
        cout << parent[i] << " - " << i << "\t" << graph[i][parent[i]] << endl;
    }
}

int main() {
    cout << "Минимальное остовное дерево (алгоритм Прима):\n";
    primMST(graph);
    return 0;
}



// Реализация на C++ (Алгоритм Крускала)

#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

struct Edge {
    int u, v, weight;
    Edge(int u, int v, int w) : u(u), v(v), weight(w) {}
};

// Функции для работы с системой непересекающихся множеств (DSU)
int find(vector<int>& parent, int v) {
    if (parent[v] == v) return v;
    return parent[v] = find(parent, parent[v]);
}

void unionSets(vector<int>& parent, vector<int>& rank, int a, int b) {
    a = find(parent, a);
    b = find(parent, b);
    if (a != b) {
        if (rank[a] < rank[b]) {
            swap(a, b);
        }
        parent[b] = a;
        if (rank[a] == rank[b]) {
            rank[a]++;
        }
    }
}

void kruskalMST(vector<Edge>& edges, int n) {
    // Сортируем рёбра по весу
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });

    vector<int> parent(n), rank(n, 0);
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
    }

    int totalWeight = 0;
    vector<Edge> mst;

    for (const auto& edge : edges) {
        if (find(parent, edge.u) != find(parent, edge.v)) {
            mst.push_back(edge);
            totalWeight += edge.weight;
            unionSets(parent, rank, edge.u, edge.v);
        }
    }

    // Вывод остовного дерева
    cout << "Ребро \tВес\n";
    for (const auto& edge : mst) {
        cout << edge.u << " - " << edge.v << "\t" << edge.weight << endl;
    }
    cout << "Общий вес: " << totalWeight << endl;
}

int main() {
    vector<Edge> edges = {
        {0, 1, 2}, {0, 3, 6}, {1, 2, 3}, {1, 3, 8}, {1, 4, 5},
        {2, 4, 7}, {3, 4, 9}
    };
    int n = 5; // Количество вершин

    cout << "Минимальное остовное дерево (алгоритм Крускала):\n";
    kruskalMST(edges, n);
    return 0;
}
