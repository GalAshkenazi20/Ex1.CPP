#include "Graph.hpp"
#include "Algorithms.hpp"
#include "DataStructures.hpp"
using namespace graph;

int main()
{
    // Example usage of the Graph and Algorithms classes
    Graph g(5);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 4);
    std::cout << "Graph:" << std::endl;
    g.print_graph();

    std::cout << "BFS:" << std::endl;
    Graph bfsTree = Algorithms::bfs(g, 0);
    bfsTree.print_graph();

    std::cout << "DFS:" << std::endl;
    Graph dfsTree = Algorithms::dfs(g, 0);
    dfsTree.print_graph();

    std::cout << "Dijkstra:" << std::endl;
    Graph dijkstraTree = Algorithms::dijkstra(g, 0);
    dijkstraTree.print_graph();

    std::cout << "Kruskal:" << std::endl;
    Graph kruskalTree = Algorithms::kruskal(g);
    kruskalTree.print_graph();

    try
    {
        std::cout << "Prim:" << std::endl;
        Graph primTree = Algorithms::prim(g, 0);
        primTree.print_graph();
    }
    catch (const std::logic_error &e)
    {
        std::cerr << "Prim Error: " << e.what() << '\n';
    }
    std::cout << "All algorithms executed successfully." << std::endl;

    return 0;
}