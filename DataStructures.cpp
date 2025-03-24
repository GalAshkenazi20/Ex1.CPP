#include "DataStructures.hpp"
namespace graph
{
    Queue::Queue(int cap)
    {
        capacity = cap;
        arr = new int[capacity];
        frontIndex = 0;
        rearIndex = -1;
        size = 0;
    }

    Queue::~Queue()
    {
        delete[] arr;
    }

    bool Queue::isEmpty() const
    {
        return size == 0;
    }

    bool Queue::isFull() const
    {
        return size == capacity;
    }

    void Queue::enqueue(int val)
    {
        if (isFull())
        {
            std::cout << "Queue is full!" << std::endl;
            return;
        }
        rearIndex = (rearIndex + 1) % capacity;
        arr[rearIndex] = val;
        size++;
    }

    int Queue::dequeue()
    {
        if (isEmpty())
        {
            std::cout << "Queue is empty!" << std::endl;
            return -1;
        }
        int val = arr[frontIndex];
        frontIndex = (frontIndex + 1) % capacity;
        size--;
        return val;
    }
    bool Queue::contains(int val) const {
        for (int i = 0, index = frontIndex; i < size; i++, index = (index + 1) % capacity) {
            if (arr[index] == val) {
                return true;
            }
        }
        return false;
    }

    UnionFind::UnionFind(int n)
    {
        size = n;
        parent = new int[size];
        rank = new int[size];
        for (int i = 0; i < size; i++)
        {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    UnionFind::~UnionFind()
    {
        delete[] parent;
        delete[] rank;
    }

    int UnionFind::find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }

    void UnionFind::unite(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY)
        {
            if (rank[rootX] < rank[rootY])
            {
                parent[rootX] = rootY;
            }
            else if (rank[rootX] > rank[rootY])
            {
                parent[rootY] = rootX;
            }
            else
            {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }

    bool UnionFind::connected(int x, int y)
    {
        return find(x) == find(y);
    }

}