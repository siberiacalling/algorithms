#ifndef ALGORITHMS_CMATRIXGRAPH_H
#define ALGORITHMS_CMATRIXGRAPH_H

#include "IGraph.h"

class CMatrixGraph : public IGraph{
public:
     CMatrixGraph(int verticesAmount_);

    // Конструктор копирования
     CMatrixGraph(const IGraph &graph);

    ~ CMatrixGraph();

    // Добавление ребра от from к to.
    void AddEdge(int from, int to) override;
    int VerticesCount() const override;
    vector<int> GetNextVertices(int vertex) const override;
    vector<int> GetPrevVertices(int vertex) const override;
    void MainDFS(const std::function<void(int, int)>& callback) const override;


    void PrintMatrix();

private:
    void dfs(int i, const std::function<void(int, int)>& callback, vector<int>& visited) const override;
    vector<vector<int>> adjacencyMatrix;
};


#endif //ALGORITHMS_CMATRIXGRAPH_H
