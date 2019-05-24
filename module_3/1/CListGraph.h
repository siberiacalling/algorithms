#ifndef ALGORITHMS_CLISTGRAPH_H
#define ALGORITHMS_CLISTGRAPH_H

#include "IGraph.h"

class CListGraph : public IGraph {
public:
    CListGraph(int verticesAmount_);

    // Конструктор копирования
    CListGraph(const IGraph &graph);

    ~CListGraph();

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


#endif //ALGORITHMS_CLISTGRAPH_H
