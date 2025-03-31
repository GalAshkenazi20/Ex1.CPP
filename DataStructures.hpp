#ifndef _DATA_STRUCTURES_
#define _DATA_STRUCTURES_

#include <iostream>

namespace graph {

    // ===== Queue =====
    class Queue {
    private:
        int* arr;
        int capacity;
        int frontIndex;
        int rearIndex;
        int size;

    public:
        Queue(int cap);
        ~Queue();
        bool isEmpty() const;
        bool isFull() const;
        void enqueue(int val);
        int dequeue();
        bool contains(int val) const;
    };

    // ===== Union-Find =====
    class UnionFind {
    private:
        int* parent;
        int* rank;
        int size;

    public:
        UnionFind(int n);
        ~UnionFind();
        int find(int x);
        void unite(int x, int y);
        bool connected(int x, int y);
    };

    // ===== Edge struct (for Kruskal) =====
    struct Edge {
        int u;
        int v;
        int weight;

        Edge() : u(0), v(0), weight(0) {}
        Edge(int a, int b, int w) : u(a), v(b), weight(w) {}
    };
    void selectionSort(Edge* edges, int size);

    // ===== Pair struct (for MinPriorityQueue) =====
    struct Pair {
        int vertex;
        int distance;
    };

    // ===== MinPriorityQueue (for Dijkstra) =====
    class MinPriorityQueue {
    private:
        Pair* heap;
        int* pos;
        int capacity;
        int size;

        void swap(int i, int j);
        void heapifyUp(int i);
        void heapifyDown(int i);

    public:
        MinPriorityQueue(int n);
        ~MinPriorityQueue();

        bool isEmpty() const;
        bool contains(int vertex) const;
        void insert(int vertex, int distance);
        void decreaseKey(int vertex, int newDistance);
        Pair extractMin();
    };

}

#endif