#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Graph.hpp"
#include "Algorithms.hpp"
#include "DataStructures.hpp"
using namespace graph;

TEST_CASE("Queue") {
    Queue q(5);
    CHECK(q.isEmpty());
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    CHECK_FALSE(q.isEmpty());
    CHECK(q.dequeue() == 1);
    CHECK(q.dequeue() == 2);
    CHECK(q.dequeue() == 3);
    CHECK(q.isEmpty());
    q.enqueue(4);
    CHECK(q.dequeue() == 4);
    q.enqueue(5);
    q.enqueue(6);
    q.enqueue(7);
    q.enqueue(8);
    q.enqueue(9);
    CHECK(q.isFull());
    CHECK(q.dequeue() == 5);
    CHECK(q.dequeue() == 6);
    CHECK(q.dequeue() == 7);
    CHECK(q.dequeue() == 8);
    CHECK(q.dequeue() == 9);
    CHECK(q.isEmpty());
    
}

TEST_CASE("UnionFind") {
    UnionFind uf(5);
    CHECK_FALSE(uf.connected(0, 1));
    uf.unite(0, 1);
    CHECK(uf.connected(0, 1));
    CHECK_FALSE(uf.connected(1, 2));
    uf.unite(1, 2);
    CHECK(uf.connected(0, 2));
    CHECK_FALSE(uf.connected(3, 4));
    uf.unite(3, 4);
    CHECK(uf.connected(3, 4));
}

TEST_CASE("Graph") {
    Graph g(5);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 4);

    CHECK(g.getNumVertices() == 5);
    CHECK_FALSE(g.getIsNegative());

    Node** adjList = g.getAdjList();
    bool foundEdge = false;
    Node* curr = adjList[0];
    while (curr != nullptr) {
        if (curr->vertex == 3 && curr->weight == 5) {
            foundEdge = true;
            break;
        }
        curr = curr->next;
    }
    CHECK(foundEdge);
}

TEST_CASE("Algorithms") {
    Graph g(5);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 4);

    CHECK_NOTHROW(Algorithms::bfs(g, 0));
    CHECK_NOTHROW(Algorithms::dfs(g, 0));
    CHECK_NOTHROW(Algorithms::dijkstra(g, 0));
    CHECK_NOTHROW(Algorithms::kruskal(g));
    CHECK_THROWS_AS(Algorithms::prim(g, -1), std::out_of_range);

    Graph g2(3);
    g2.addEdge(0, 1, 1);
    g2.addEdge(1, 2, 2);
    CHECK_NOTHROW(Algorithms::prim(g2, 0));
}

TEST_CASE("MinPriorityQueue") {
    MinPriorityQueue mpq(5);
    CHECK(mpq.isEmpty());
    mpq.insert(0, 10);
    mpq.insert(1, 5);
    mpq.insert(2, 20);
    Pair min = mpq.extractMin();
    CHECK(min.vertex == 1);
    CHECK(min.distance == 5);
    min = mpq.extractMin();
    CHECK(min.vertex == 0);
    CHECK(min.distance == 10);
    min = mpq.extractMin();
    CHECK(min.vertex == 2);
    CHECK(min.distance == 20);
    CHECK(mpq.isEmpty());
}

TEST_CASE("SelectionSort") {
    Edge edges[] = {Edge(0, 1, 10), Edge(0, 2, 6), Edge(0, 3, 5), Edge(1, 3, 15), Edge(2, 3, 4)};
    int size = sizeof(edges) / sizeof(edges[0]);
    selectionSort(edges, size);
    CHECK(edges[0].weight == 4);
    CHECK(edges[1].weight == 5);
    CHECK(edges[2].weight == 6);
    CHECK(edges[3].weight == 10);
    CHECK(edges[4].weight == 15);
}

TEST_CASE("Graph with Negative Edges") {
    Graph g(5);
    g.addEdge(0, 1, -10);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 4);
    CHECK(g.getIsNegative());
    CHECK_THROWS_AS(Algorithms::dijkstra(g, 0), std::logic_error);
}