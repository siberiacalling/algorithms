#include "CSetGraph.h"

CSetGraph::CSetGraph(int verticesAmount_) : IGraph(verticesAmount_), vectorSets(verticesAmount_) {

}

CSetGraph::CSetGraph(const IGraph &graph) : IGraph(graph.verticesAmount),
                                            vectorSets(graph.verticesAmount) {

}

CSetGraph::~CSetGraph() = default;

void CSetGraph::AddEdge(int from, int to) {
    vectorSets[from].insert(to);
}

int CSetGraph::VerticesCount() const {
    return 0;
}

vector<int> CSetGraph::GetNextVertices(int vertex) const {
    vector<int> result(vectorSets[vertex].begin(), vectorSets[vertex].end());
    return result;
}

vector<int> CSetGraph::GetPrevVertices(int vertex) const {
    vector<int> result;
    for (int i = 0; i < (int)vectorSets.size(); i ++) {
        if (vectorSets[i].count(vertex) > 0) {
            result.push_back(i);
        }
    }
    return result;
}

void CSetGraph::dfs(int i, const std::function<void(int, int)> &callback, vector<int> &visited) const {
    visited[i] = 1;
    vector<int> nextVertices = GetNextVertices(i);
    for (const auto &verticeIndex :nextVertices) {
        callback(i, verticeIndex);
        if (!visited[verticeIndex]) {
            dfs(verticeIndex, callback, visited);
        }
    }
}

void CSetGraph::MainDFS(const std::function<void(int, int)> &callback) const {
    vector<int> visited(verticesAmount);
    for (int i = 0; i < verticesAmount; ++i)
        if (!visited[i])
            dfs(i, callback, visited);
}


int main() {
    CSetGraph a(5);
    a.AddEdge(1, 0);
    a.AddEdge(1, 3);
    a.AddEdge(2, 1);
    a.AddEdge(2, 3);
    a.AddEdge(3, 2);
    a.AddEdge(3, 4);

    vector<int> result = a.GetPrevVertices(0);
    for (int i : result) {
        cout << i << " ";
    }
    cout << endl;
    a.MainDFS([](int value, int value2) {
        cout << "из " << value << "  в " << value2 << endl;
    });
}