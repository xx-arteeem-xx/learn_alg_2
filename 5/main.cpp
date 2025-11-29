#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>

using namespace std;

// Интерфейс графа
class IGraph {
public:
    virtual ~IGraph() = default;
    virtual bool containsEdge(int v1, int v2) const = 0;
    virtual void addEdge(int v1, int v2) = 0;
    virtual const vector<int>& getAdjacent(int v) const = 0;
    virtual int size() const = 0;
    virtual void display() const = 0;
};

// Реализация графа через списки смежности
class ListsGraph : public IGraph {
private:
    vector<vector<int>> adjacencyList;

public:
    ListsGraph(int vertexCount) : adjacencyList(vertexCount) {}

    bool containsEdge(int v1, int v2) const override {
        if (v1 < 0 || v1 >= size() || v2 < 0 || v2 >= size()) 
            return false;
        return find(adjacencyList[v1].begin(), adjacencyList[v1].end(), v2) != adjacencyList[v1].end();
    }

    void addEdge(int v1, int v2) override {
        if (v1 < 0 || v1 >= size() || v2 < 0 || v2 >= size() || v1 == v2) 
            return;
        
        if (!containsEdge(v1, v2)) {
            adjacencyList[v1].push_back(v2);
            adjacencyList[v2].push_back(v1);
        }
    }

    const vector<int>& getAdjacent(int v) const override {
        static const vector<int> empty;
        if (v < 0 || v >= size()) return empty;
        return adjacencyList[v];
    }

    int size() const override {
        return adjacencyList.size();
    }

    void display() const override {
        cout << "Списки смежности графа:" << endl;
        for (int i = 0; i < size(); i++) {
            cout << i << " | -> ";
            for (int j = 0; j < adjacencyList[i].size(); j++) {
                cout << adjacencyList[i][j];
                if (j < adjacencyList[i].size() - 1) cout << " | ";
            }
            cout << endl;
        }
    }
};

// Структура для хранения результатов обхода
struct GraphSearchResult {
    vector<int> traversalOrder;
    vector<pair<int, int>> spanningTreeEdges;

    void addVertex(int v) {
        traversalOrder.push_back(v);
    }

    void addEdge(int v1, int v2) {
        spanningTreeEdges.emplace_back(min(v1, v2), max(v1, v2));
    }

    void display() const {
        cout << "Порядок обхода: ";
        for (int v : traversalOrder) {
            cout << v << " ";
        }
        cout << endl;

        cout << "Ребра каркаса: ";
        for (const auto& edge : spanningTreeEdges) {
            cout << "(" << edge.first << "-" << edge.second << ") ";
        }
        cout << endl;
    }
};

// Интерфейс структуры данных для обхода
class IGraphSearchStructure {
public:
    virtual ~IGraphSearchStructure() = default;
    virtual void addVertex(int v) = 0;
    virtual int currentVertex() = 0;
    virtual void removeCurrentVertex() = 0;
    virtual bool isEmpty() const = 0;
    virtual void print() const = 0;
};

// Реализация стека для DFS
class StackStructure : public IGraphSearchStructure {
private:
    stack<int> st;

public:
    void addVertex(int v) override {
        st.push(v);
    }

    int currentVertex() override {
        return st.empty() ? -1 : st.top();
    }

    void removeCurrentVertex() override {
        if (!st.empty()) {
            st.pop();
        }
    }

    bool isEmpty() const override {
        return st.empty();
    }

    void print() const override {
        stack<int> temp = st;
        vector<int> elements;
        while (!temp.empty()) {
            elements.push_back(temp.top());
            temp.pop();
        }
        reverse(elements.begin(), elements.end());
        
        cout << "Стек: [ ";
        for (int v : elements) {
            cout << v << " ";
        }
        cout << "]";
    }
};

// Реализация очереди для BFS
class QueueStructure : public IGraphSearchStructure {
private:
    queue<int> q;

public:
    void addVertex(int v) override {
        q.push(v);
    }

    int currentVertex() override {
        return q.empty() ? -1 : q.front();
    }

    void removeCurrentVertex() override {
        if (!q.empty()) {
            q.pop();
        }
    }

    bool isEmpty() const override {
        return q.empty();
    }

    void print() const override {
        queue<int> temp = q;
        cout << "Очередь: [ ";
        while (!temp.empty()) {
            cout << temp.front() << " ";
            temp.pop();
        }
        cout << "]";
    }
};

// Класс для обхода графа
class GraphTraversal {
private:
    IGraph* graph;
    vector<bool> visited;

    int getNextUnvisited(int currentVertex) {
        for (int neighbor : graph->getAdjacent(currentVertex)) {
            if (!visited[neighbor]) {
                return neighbor;
            }
        }
        return -1;
    }

public:
    GraphTraversal(IGraph* g) : graph(g) {}

    GraphSearchResult search(int startVertex, IGraphSearchStructure* structure) {
        GraphSearchResult result;
        visited.assign(graph->size(), false);

        if (startVertex < 0 || startVertex >= graph->size()) {
            cout << "Неверная стартовая вершина!" << endl;
            return result;
        }

        structure->addVertex(startVertex);
        result.addVertex(startVertex);
        visited[startVertex] = true;

        cout << "Начало обхода с вершины " << startVertex << endl;

        while (!structure->isEmpty()) {
            structure->print();
            cout << " | ";

            int current = structure->currentVertex();
            int nextVertex = getNextUnvisited(current);

            if (nextVertex != -1) {
                visited[nextVertex] = true;
                result.addVertex(nextVertex);
                result.addEdge(current, nextVertex);
                
                structure->addVertex(nextVertex);
                cout << " + " << nextVertex << " " << current << "-" << nextVertex << endl;
            } else {
                structure->removeCurrentVertex();
                cout << " - удаление" << endl;
            }
        }

        cout << "Обход завершен!" << endl;
        return result;
    }
};

// Генератор случайного графа
class RandomGraphGenerator {
private:
    mt19937 gen;

public:
    RandomGraphGenerator() : gen(chrono::steady_clock::now().time_since_epoch().count()) {}

    ListsGraph generateGraph(int vertexCount, double edgeProbability) {
        ListsGraph graph(vertexCount);
        uniform_real_distribution<double> dist(0.0, 1.0);

        for (int i = 0; i < vertexCount; i++) {
            for (int j = i + 1; j < vertexCount; j++) {
                if (dist(gen) < edgeProbability) {
                    graph.addEdge(i, j);
                }
            }
        }

        return graph;
    }
};

// Функция для демонстрации работы
void demonstrateTraversal(IGraph* graph, int startVertex, bool useBFS) {
    cout << "\n=== " << (useBFS ? "ОБХОД В ШИРИНУ (BFS)" : "ОБХОД В ГЛУБИНУ (DFS)") << " ===" << endl;
    
    GraphTraversal traversal(graph);
    unique_ptr<IGraphSearchStructure> structure;
    
    if (useBFS) {
        structure = make_unique<QueueStructure>();
    } else {
        structure = make_unique<StackStructure>();
    }

    GraphSearchResult result = traversal.search(startVertex, structure.get());
    result.display();
}

int main() {
    // Создание тестового графа
    ListsGraph graph(10);
    
    // Добавление ребер (пример из лекции)
    graph.addEdge(0, 2);
    graph.addEdge(0, 3);
    graph.addEdge(0, 6);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(1, 7);
    graph.addEdge(2, 5);
    graph.addEdge(4, 8);
    graph.addEdge(5, 9);
    graph.addEdge(6, 9);
    graph.addEdge(7, 9);
    graph.addEdge(8, 9);

    // Отображение графа
    graph.display();
    cout << endl;

    // Демонстрация обходов
    int startVertex;
    
    cout << "Введите стартовую вершину (0-" << graph.size()-1 << "): ";
    cin >> startVertex;

    // Обход в ширину
    demonstrateTraversal(&graph, startVertex, true);
    
    // Обход в глубину
    demonstrateTraversal(&graph, startVertex, false);

    // Дополнительное задание: генерация случайного графа
    cout << "\n=== ГЕНЕРАЦИЯ СЛУЧАЙНОГО ГРАФА ===" << endl;
    RandomGraphGenerator generator;
    ListsGraph randomGraph = generator.generateGraph(8, 0.3);
    
    randomGraph.display();
    
    cout << "\nОбход случайного графа:" << endl;
    demonstrateTraversal(&randomGraph, 0, true);
    demonstrateTraversal(&randomGraph, 0, false);

    return 0;
}