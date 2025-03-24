#ifndef _ALGORITHMS_HPP_
#include <iostream>
#include "Graph.hpp"
namespace graph{
    class Algorithms{
        public:
            static Graph bfs(const Graph& g, int s);
            static Graph dfs (const Graph& g, int s);
            static Graph dijkstra(const Graph& g, int s);
            static Graph prim(const Graph& g);
            static Graph kruskal(const Graph& g);

    };
}
#endif