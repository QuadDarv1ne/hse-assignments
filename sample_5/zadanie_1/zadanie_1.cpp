/*
    Тема №1. Абстрактные типы данных (линейные структуры) – 4 часа

    АТД «стек» - задача коммивояжера, исчерпывающий поиск в глубину
*/

#include <iostream>
#include <vector>
#include <stack>
#include <limits>
#include <algorithm>

using namespace std;

struct State {
    int currentNode;
    vector<int> path;
    int distance;

    State(int node, vector<int> p, int d) : currentNode(node), path(move(p)), distance(d) {}
};

pair<int, vector<int>> tsp_dfs(const vector<vector<int>>& graph, int startNode) {
    int numNodes = graph.size();
    stack<State> st;
    st.push(State(startNode, {startNode}, 0));
    int minDistance = numeric_limits<int>::max();
    vector<int> minPath;

    while (!st.empty()) {
        State state = st.top();
        st.pop();

        int currentNode = state.currentNode;
        vector<int> path = state.path;
        int distance = state.distance;

        // Если посещены все узлы и есть путь к начальному узлу
        if (path.size() == numNodes && graph[currentNode][startNode] > 0) {
            int totalDistance = distance + graph[currentNode][startNode];
            if (totalDistance < minDistance) {
                minDistance = totalDistance;
                minPath = path;
                minPath.push_back(startNode);
            }
        }

        // Продолжаем обход
        for (int neighbor = 0; neighbor < numNodes; ++neighbor) {
            if (find(path.begin(), path.end(), neighbor) == path.end() && graph[currentNode][neighbor] > 0) {
                vector<int> newPath = path;
                newPath.push_back(neighbor);
                st.push(State(neighbor, newPath, distance + graph[currentNode][neighbor]));
            }
        }
    }

    return {minDistance, minPath};
}

int main() {
    // Матрица смежности графа
    vector<vector<int>> graph = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };
    int startNode = 0;

    pair<int, vector<int>> result = tsp_dfs(graph, startNode);
    int minDistance = result.first;
    vector<int> minPath = result.second;

    cout << "Минимальная длина пути: " << minDistance << endl;
    cout << "Кратчайший путь: ";
    for (int node : minPath) {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}
