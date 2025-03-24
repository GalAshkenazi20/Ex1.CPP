#ifndef _DATA_STRUCTURES_
#define _DATA_STRUCTURES_
#include <iostream>
namespace graph
{

    class Queue
    {
    private:
        int *arr;
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

    class UnionFind
    {
    private:
        int *parent;
        int *rank;
        int size;

    public:
        UnionFind(int n);
        ~UnionFind();
        int find(int x);
        void unite(int x, int y);
        bool connected(int x, int y);
    };

}
#endif