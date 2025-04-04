#include "DataStructures.hpp"

namespace graph
{

    // ===== Queue Implementation =====

    // Constructor for a fixed-size circular queue
    Queue::Queue(int cap)
    {
        capacity = cap;
        arr = new int[capacity];
        frontIndex = 0;
        rearIndex = -1;
        size = 0;
    }

    // Destructor that frees the allocated memory
    Queue::~Queue()
    {
        delete[] arr;
    }

    // Returns true if the queue is empty
    bool Queue::isEmpty() const
    {
        return size == 0;
    }

    // Returns true if the queue is full
    bool Queue::isFull() const
    {
        return size == capacity;
    }

    // Adds a value to the end of the queue
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

    // Removes and returns the value from the front of the queue
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

    // Checks if the queue contains a specific value
    bool Queue::contains(int val) const
    {
        for (int i = 0, index = frontIndex; i < size; i++, index = (index + 1) % capacity)
        {
            if (arr[index] == val)
            {
                return true;
            }
        }
        return false;
    }

    // ===== UnionFind Implementation =====

    // Constructor that initializes each element as its own set
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

    // Destructor that frees the memory
    UnionFind::~UnionFind()
    {
        delete[] parent;
        delete[] rank;
    }

    // Finds the representative of the set that x belongs to
    int UnionFind::find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]); // path compression
        }
        return parent[x];
    }

    // Unites the sets that contain x and y
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

    // Returns true if x and y are in the same set
    bool UnionFind::connected(int x, int y)
    {
        return find(x) == find(y);
    }

    // ===== MinPriorityQueue Implementation =====

    // Constructor for a min-priority queue with given capacity
    MinPriorityQueue::MinPriorityQueue(int n)
    {
        capacity = n;
        size = 0;
        heap = new Pair[capacity];
        pos = new int[n];
        for (int i = 0; i < n; i++)
            pos[i] = -1;
    }

    // Destructor that releases heap and position arrays
    MinPriorityQueue::~MinPriorityQueue()
    {
        delete[] heap;
        delete[] pos;
    }

    // Checks if the queue is empty
    bool MinPriorityQueue::isEmpty() const
    {
        return size == 0;
    }

    // Checks if a vertex is already in the queue
    bool MinPriorityQueue::contains(int vertex) const
    {
        return pos[vertex] != -1;
    }

    // Inserts a vertex with its distance into the queue
    void MinPriorityQueue::insert(int vertex, int distance)
    {
        if (pos[vertex] != -1)
        {
            std::cerr << "Error: vertex already in queue\n";
            return;
        }
        heap[size] = {vertex, distance};
        pos[vertex] = size;
        heapifyUp(size);
        size++;
    }

    // Updates the distance of a vertex if new distance is smaller
    void MinPriorityQueue::decreaseKey(int vertex, int newDistance)
    {
        int i = pos[vertex];
        if (i == -1 || heap[i].distance <= newDistance)
            return;

        heap[i].distance = newDistance;
        heapifyUp(i);
    }

    // Removes and returns the vertex with the smallest distance
    Pair MinPriorityQueue::extractMin()
    {
        if (isEmpty())
        {
            std::cerr << "Queue underflow\n";
            return {-1, -1};
        }

        Pair min = heap[0];
        pos[min.vertex] = -1;
        heap[0] = heap[size - 1];
        pos[heap[0].vertex] = 0;
        size--;
        heapifyDown(0);
        return min;
    }

    // Swaps two elements in the heap and updates their positions
    void MinPriorityQueue::swap(int i, int j)
    {
        Pair temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
        pos[heap[i].vertex] = i;
        pos[heap[j].vertex] = j;
    }

    // Moves a node up the heap if its priority is better
    void MinPriorityQueue::heapifyUp(int i)
    {
        while (i > 0 && heap[i].distance < heap[(i - 1) / 2].distance)
        {
            swap(i, (i - 1) / 2);
            i = (i - 1) / 2;
        }
    }

    // Moves a node down the heap to restore heap property
    void MinPriorityQueue::heapifyDown(int i)
    {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < size && heap[left].distance < heap[smallest].distance)
            smallest = left;
        if (right < size && heap[right].distance < heap[smallest].distance)
            smallest = right;

        if (smallest != i)
        {
            swap(i, smallest);
            heapifyDown(smallest);
        }
    }

    // Sorts the edges array in ascending order using selection sort
    void selectionSort(Edge *edges, int size)
    {
        for (int i = 0; i < size - 1; i++)
        {
            int minIndex = i;
            for (int j = i + 1; j < size; j++)
            {
                if (edges[j].weight < edges[minIndex].weight)
                {
                    minIndex = j;
                }
            }
            if (minIndex != i)
            {
                Edge temp = edges[i];
                edges[i] = edges[minIndex];
                edges[minIndex] = temp;
            }
        }
    }
}
