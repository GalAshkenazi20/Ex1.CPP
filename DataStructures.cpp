#include "DataStructures.hpp"

namespace graph {

    // ===== Queue Implementation =====
    Queue::Queue(int cap) {
        capacity = cap;
        arr = new int[capacity];
        frontIndex = 0;
        rearIndex = -1;
        size = 0;
    }

    Queue::~Queue() {
        delete[] arr;
    }

    bool Queue::isEmpty() const {
        return size == 0;
    }

    bool Queue::isFull() const {
        return size == capacity;
    }

    void Queue::enqueue(int val) {
        if (isFull()) {
            std::cout << "Queue is full!" << std::endl;
            return;
        }
        rearIndex = (rearIndex + 1) % capacity;
        arr[rearIndex] = val;
        size++;
    }

    int Queue::dequeue() {
        if (isEmpty()) {
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

    // ===== UnionFind Implementation =====
    UnionFind::UnionFind(int n) {
        size = n;
        parent = new int[size];
        rank = new int[size];
        for (int i = 0; i < size; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    UnionFind::~UnionFind() {
        delete[] parent;
        delete[] rank;
    }

    int UnionFind::find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void UnionFind::unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }

    bool UnionFind::connected(int x, int y) {
        return find(x) == find(y);
    }

    // ===== MinPriorityQueue Implementation =====
    MinPriorityQueue::MinPriorityQueue(int n) {
        capacity = n;
        size = 0;
        heap = new Pair[capacity];
        pos = new int[n];
        for (int i = 0; i < n; i++) pos[i] = -1;
    }

    MinPriorityQueue::~MinPriorityQueue() {
        delete[] heap;
        delete[] pos;
    }

    bool MinPriorityQueue::isEmpty() const {
        return size == 0;
    }

    bool MinPriorityQueue::contains(int vertex) const {
        return pos[vertex] != -1;
    }

    void MinPriorityQueue::insert(int vertex, int distance) {
        if (pos[vertex] != -1) {
            std::cerr << "Error: vertex already in queue\n";
            return;
        }
        heap[size] = {vertex, distance};
        pos[vertex] = size;
        heapifyUp(size);
        size++;
    }

    void MinPriorityQueue::decreaseKey(int vertex, int newDistance) {
        int i = pos[vertex];
        if (i == -1 || heap[i].distance <= newDistance) return;

        heap[i].distance = newDistance;
        heapifyUp(i);
    }

    Pair MinPriorityQueue::extractMin() {
        if (isEmpty()) {
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

    void MinPriorityQueue::swap(int i, int j) {
        Pair temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
        pos[heap[i].vertex] = i;
        pos[heap[j].vertex] = j;
    }

    void MinPriorityQueue::heapifyUp(int i) {
        while (i > 0 && heap[i].distance < heap[(i - 1) / 2].distance) {
            swap(i, (i - 1) / 2);
            i = (i - 1) / 2;
        }
    }

    void MinPriorityQueue::heapifyDown(int i) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < size && heap[left].distance < heap[smallest].distance)
            smallest = left;
        if (right < size && heap[right].distance < heap[smallest].distance)
            smallest = right;

        if (smallest != i) {
            swap(i, smallest);
            heapifyDown(smallest);
        }
    }

}
