#include "CListGraph.h"


CListGraph::CListGraph(int verticesAmount_) : IGraph(verticesAmount_), lists(verticesAmount_) {
}

CListGraph::~CListGraph() = default;

CListGraph::CListGraph(const IGraph &graph) : IGraph(graph.verticesAmount),
                                              lists(graph.verticesAmount) {
    // graph.MainDFS(CListGraph::AddEdge, this);
}

void CListGraph::dfs(int i, const std::function<void(int, int)> &callback, vector<int> &visited) const {
    visited[i] = 1;
    vector<int> nextVertices = GetNextVertices(i);
    for (const auto &verticeIndex :nextVertices) {
        callback(i, verticeIndex);
        if (!visited[verticeIndex]) {
            dfs(verticeIndex, callback, visited);
        }
    }

}

void CListGraph::MainDFS(const std::function<void(int, int)> &callback) const {
    vector<int> visited(verticesAmount);
    for (int i = 0; i < verticesAmount; ++i)
        if (!visited[i])
            dfs(i, callback, visited);
}

void CListGraph::AddEdge(int from, int to) {
    lists[from].push_back(to);
}

int CListGraph::VerticesCount() const {
    return verticesAmount;
}


vector<int> CListGraph::GetNextVertices(int vertex) const {
    return lists[vertex];
}

vector<int> CListGraph::GetPrevVertices(int vertex) const {
    vector<int> result;
    for (int i = 0; i < verticesAmount; i++) {
        for (int j = 0; j < (int) lists[i].size(); j++) {
            if (lists[i][j] == vertex) {
                result.push_back(i);
            }
        }
    }
    return result;
}


void CListGraph::PrintMatrix() {
    for (int i = 0; i < verticesAmount; i++) {
        for (int j : GetNextVertices(i)) {
            cout << j;
        }
        cout << endl;
    }
}


int main() {
    CListGraph a(5);
    a.AddEdge(1, 0);
    a.AddEdge(1, 3);
    a.AddEdge(2, 1);
    a.AddEdge(2, 3);
    a.AddEdge(3, 2);
    a.AddEdge(3, 4);

//    a.PrintMatrix();
//    vector<int> result = a.GetPrevVertices(2);
//    for (int i : result) {
//        cout << i << " ";
//    }
    a.MainDFS([](int value, int value2) {
        cout << "из " << value << "  в " << value2 << endl;
    });
}
