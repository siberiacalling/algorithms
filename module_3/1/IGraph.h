#ifndef ALGORITHMS_IGRAPH_H
#define ALGORITHMS_IGRAPH_H

#include <iostream>
#include <vector>
#include <functional>

using namespace std;

class IGraph {
public:
    explicit IGraph(int verticesAmount_) {verticesAmount = verticesAmount_;}
    virtual ~IGraph() = default;

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
    virtual void MainDFS(const std::function<void(int, int)>& callback) const = 0;
    virtual void dfs(int i, const std::function<void(int, int)>& callback, vector<int>& visited) const = 0;

    int verticesAmount{};

};


#endif //ALGORITHMS_IGRAPH_H
