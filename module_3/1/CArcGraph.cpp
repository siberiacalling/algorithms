#include "CArcGraph.h"

CArcGraph::CArcGraph(int verticesAmount_) : IGraph(verticesAmount_) {

}

CArcGraph::CArcGraph(const IGraph &graph) : IGraph(graph.verticesAmount),
                                            vectorPairs(graph.verticesAmount) {
    graph.MainDFS([this](int a, int b) { this->AddEdge(a, b); });
}

CArcGraph::~CArcGraph() = default;

void CArcGraph::AddEdge(int from, int to) {
    vectorPairs.emplace_back(from, to);
}

int CArcGraph::VerticesCount() const {
    return 0;
}

vector<int> CArcGraph::GetNextVertices(int vertex) const {
    vector<int> result;
    for (const auto &pair :vectorPairs) {
        if (pair.first == vertex) {
            result.push_back(pair.second);
        }
    }
    return result;
}

vector<int> CArcGraph::GetPrevVertices(int vertex) const {
    vector<int> result;
    for (const auto &pair :vectorPairs) {
        if (pair.second == vertex) {
            result.push_back(pair.first);
        }
    }
    return result;
}

void CArcGraph::dfs(int i, const std::function<void(int, int)> &callback, vector<int> &visited) const {
    visited[i] = 1;
    vector<int> nextVertices = GetNextVertices(i);
    for (const auto &verticeIndex :nextVertices) {
        callback(i, verticeIndex);
        if (!visited[verticeIndex]) {
            dfs(verticeIndex, callback, visited);
        }
    }
}

void CArcGraph::MainDFS(const std::function<void(int, int)> &callback) const {
    vector<int> visited(verticesAmount);
    for (int i = 0; i < verticesAmount; ++i)
        if (!visited[i])
            dfs(i, callback, visited);
}


int main() {
    CArcGraph a(5);
    a.AddEdge(1, 0);
    a.AddEdge(1, 3);
    a.AddEdge(2, 1);
    a.AddEdge(2, 3);
    a.AddEdge(3, 2);
    a.AddEdge(3, 4);

    a.PrintMatrix();
    vector<int> result = a.GetNextVertices(3);
    for (int i : result) {
        cout << i << " ";
    }
    cout << endl;
    a.MainDFS([](int value, int value2) {
        cout << "из " << value << "  в " << value2 << endl;
    });
}