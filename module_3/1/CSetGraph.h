#ifndef ALGORITHMS_CSETGRAPH_H
#define ALGORITHMS_CSETGRAPH_H


#include "IGraph.h"
#include <set>

class CSetGraph : public IGraph{
public:
    explicit CSetGraph(int verticesAmount_);

    // Конструктор копирования
    explicit CSetGraph(const IGraph &graph);

    ~CSetGraph() override;

    // Добавление ребра от from к to.
    void AddEdge(int from, int to) override;
    int VerticesCount() const override;
    vector<int> GetNextVertices(int vertex) const override;
    vector<int> GetPrevVertices(int vertex) const override;
    void MainDFS(const std::function<void(int, int)>& callback) const override;

private:
    void dfs(int i, const std::function<void(int, int)>& callback, vector<int>& visited) const override;
    vector< set<int>> vectorSets;
};


#endif //ALGORITHMS_CSETGRAPH_H
