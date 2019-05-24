#include "CListGraph.h"


CListGraph::CListGraph(int verticesAmount_) : IGraph(verticesAmount_), adjacencyMatrix(verticesAmount_, vector<int>(verticesAmount_)) {
}

CListGraph::~CListGraph() {

}

CListGraph::CListGraph(const IGraph &graph) : IGraph(graph.verticesAmount),
                                              adjacencyMatrix(graph.verticesAmount, vector<int>(graph.verticesAmount)) {
   // graph.MainDFS(CListGraph::AddEdge, this);
}

void CListGraph::dfs(int i, const std::function<void(int, int)> &callback, vector<int> &visited) const {
    visited[i] = 1;
    vector<int> nextVertices = GetNextVertices(i);
    for (const auto& verticeIndex :nextVertices) {
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
    adjacencyMatrix[from][to] = 1;
}

int CListGraph::VerticesCount() const {
    return verticesAmount;
}


vector<int> CListGraph::GetNextVertices(int vertex) const {
    vector<int> result;
    for (int j = 0; j < verticesAmount; j++) {
        if (adjacencyMatrix[vertex][j] == 1) {
            result.push_back(j);
        }
    }
    return result;
}

vector<int> CListGraph::GetPrevVertices(int vertex) const {
    vector<int> result;
    int j = vertex;
    cout << endl;
    for (int i = 0; i < verticesAmount; i++) {
        cout << adjacencyMatrix[i][j];
        if (adjacencyMatrix[i][j] == 1) {
            result.push_back(i);
        }
    }
    cout << endl;
    return result;
}


void CListGraph::PrintMatrix() {
    for (int i = 0; i < verticesAmount; i++) {
        for (int j = 0; j < verticesAmount; j++) {
            cout << adjacencyMatrix[i][j];
        }
        cout << endl;
    }
}


int main() {
    CListGraph a(4);
    a.AddEdge(1, 0);
    a.AddEdge(1, 3);
    a.AddEdge(2, 1);
    a.AddEdge(2, 3);
    a.AddEdge(3, 2);
    //a.AddEdge(3, 4);

    a.PrintMatrix();
    a.MainDFS([](int value, int value2) {
        cout << "из " << value << "  в " << value2 << endl;
    });
}
