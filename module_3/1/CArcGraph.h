#ifndef ALGORITHMS_CARCGRAPH_H
#define ALGORITHMS_CARCGRAPH_H

#include "IGraph.h"

class CArcGraph : public IGraph{
public:
    explicit CArcGraph(int verticesAmount_);

    // Конструктор копирования
    explicit CArcGraph(const IGraph &graph);

    ~CArcGraph() override;

    // Добавление ребра от from к to.
    void AddEdge(int from, int to) override;
    int VerticesCount() const override;
    vector<int> GetNextVertices(int vertex) const override;
    vector<int> GetPrevVertices(int vertex) const override;
    void MainDFS(const std::function<void(int, int)>& callback) const override;


    void PrintMatrix();

private:
    void dfs(int i, const std::function<void(int, int)>& callback, vector<int>& visited) const override;
    vector< pair<int, int>> vectorPairs;
};


#endif //ALGORITHMS_CARCGRAPH_H
