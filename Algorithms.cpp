#include "Algorithms.hpp"
using namespace graph;

// Runs BFS (Breadth-First Search) from source vertex s.
// Builds and returns the BFS tree as a new Graph object.
// Uses a queue to explore the graph level by level.
// Throws if source index is invalid.
Graph Algorithms::bfs(const Graph &g, int s)
{
    if (s < 0 || s >= g.getNumVertices()) {
        throw std::out_of_range("bfs: Source vertex index out of bounds");
    }

    int n = g.getNumVertices();
    int *parent = new int[n];            // To track parents in BFS tree
    int *weightParent = new int[n];      // To track weights of edges

    for (int i = 0; i < n; i++) {
        parent[i] = -1;                  // -1 means not visited yet
        weightParent[i] = 0;
    }

    Queue q(n);
    q.enqueue(s);                        // Start BFS from source node
    parent[s] = s;                       // Source is its own parent

    while (!q.isEmpty()) {
        int curr = q.dequeue();          // Take the next node from the queue
        Node *neighbor = g.getAdjList()[curr];

        while (neighbor != nullptr) {
            int v = neighbor->vertex;
            if (parent[v] == -1) {       // If not visited yet
                parent[v] = curr;        // Set parent
                weightParent[v] = neighbor->weight;
                q.enqueue(v);            // Add to queue for next visit
            }
            neighbor = neighbor->next;
        }
    }

    Graph bfsTree(n);
    for (int i = 0; i < n; i++) {
        if (parent[i] != -1 && parent[i] != i) {
            bfsTree.addEdge(parent[i], i, weightParent[i]);
        }
    }

    delete[] parent;
    delete[] weightParent;
    return bfsTree;
}

// Helper for DFS: visits one node and goes deeper recursively.
// Marks visited nodes and builds the DFS tree step by step.
// Called by the main DFS function.
void Algorithms::dfs_visit(const Graph &g, int u, bool *visited, Graph &dfsTree)
{
    visited[u] = true;                         // Mark current node as visited
    Node *neighbor = g.getAdjList()[u];

    while (neighbor != nullptr) {
        int v = neighbor->vertex;
        if (!visited[v]) {
            dfsTree.addEdge(u, v, neighbor->weight); // Add edge to DFS tree
            dfs_visit(g, v, visited, dfsTree);        // Visit neighbor
        }
        neighbor = neighbor->next;
    }
}

// Runs DFS (Depth-First Search) starting from vertex s.
// Visits all nodes and builds a DFS tree.
// Wraps around if not all nodes reached from s directly.
Graph Algorithms::dfs(const Graph &g, int s)
{
    if (s < 0 || s >= g.getNumVertices()) {
        throw std::out_of_range("dfs: Source vertex index out of bounds");
    }

    int n = g.getNumVertices();
    bool *visited = new bool[n];
    for (int i = 0; i < n; i++) visited[i] = false;  // All not visited

    Graph dfsTree(n);

    // Go from s to end
    for (int i = s; i < n; i++) {
        if (!visited[i]) {
            dfs_visit(g, i, visited, dfsTree);
        }
    }
    // Then wrap around from 0 to s-1
    for (int i = 0; i < s; i++) {
        if (!visited[i]) {
            dfs_visit(g, i, visited, dfsTree);
        }
    }

    delete[] visited;
    return dfsTree;
}

// Runs Dijkstra's algorithm to find shortest paths from s.
// Builds the shortest-path tree with edge weights.
// Uses a min-priority queue to choose next closest node.
// Throws if graph has negative edge weights.
Graph Algorithms::dijkstra(const Graph &g, int s)
{
    if (g.getIsNegative()) {
        throw std::logic_error("Dijkstra cannot run on graphs with negative edge weights.");
    }
    if (s < 0 || s >= g.getNumVertices()) {
        throw std::out_of_range("dijkstra: Source vertex index out of bounds");
    }

    int n = g.getNumVertices();
    int *dist = new int[n];              // Distance from source
    int *parent = new int[n];            // Parent in shortest-path tree
    int *weightParent = new int[n];      // Edge weight to parent

    for (int i = 0; i < n; i++) {
        dist[i] = 9999;                  // Start with big distance
        parent[i] = -1;
        weightParent[i] = 0;
    }
    dist[s] = 0;
    parent[s] = s;

    MinPriorityQueue mpq(n);
    mpq.insert(s, 0);

    while (!mpq.isEmpty()) {
        Pair curr = mpq.extractMin();    // Get node with smallest distance
        int u = curr.vertex;

        Node *neighbor = g.getAdjList()[u];
        while (neighbor != nullptr) {
            int v = neighbor->vertex;
            int w = neighbor->weight;

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;           // Update distance
                parent[v] = u;                   // Set parent
                weightParent[v] = w;

                if (mpq.contains(v)) {
                    mpq.decreaseKey(v, dist[v]);
                } else {
                    mpq.insert(v, dist[v]);
                }
            }
            neighbor = neighbor->next;
        }
    }

    Graph dijkstraTree(n);
    for (int i = 0; i < n; i++) {
        if (parent[i] != -1 && parent[i] != i) {
            dijkstraTree.addEdge(parent[i], i, weightParent[i]);
        }
    }

    delete[] dist;
    delete[] parent;
    delete[] weightParent;
    return dijkstraTree;
}

// Runs Prim's algorithm to find a Minimum Spanning Tree.
// First checks if the graph is connected using BFS.
// Then uses a priority queue to grow the MST.
// Returns the MST as a new graph.
Graph Algorithms::prim(const Graph &g, int randS)
{
    if (randS < 0 || randS >= g.getNumVertices()) {
        throw std::out_of_range("prim: Source vertex index out of bounds");
    }

    // First check if graph is connected
    Graph bfsTree = Algorithms::bfs(g, randS);
    int edgeCount = 0;
    for (int i = 0; i < bfsTree.getNumVertices(); i++) {
        Node* curr = bfsTree.getAdjList()[i];
        while (curr != nullptr) {
            edgeCount++;
            curr = curr->next;
        }
    }
    edgeCount /= 2;  // Because undirected edges counted twice

    if (edgeCount < g.getNumVertices() - 1) {
        throw std::logic_error("Prim requires a connected graph.");
    }

    int n = g.getNumVertices();
    bool *inMST = new bool[n];           // Tracks which nodes are in MST
    int *parent = new int[n];
    int *key = new int[n];               // Best edge weight to MST
    MinPriorityQueue mpq(n);

    for (int i = 0; i < n; i++) {
        key[i] = 9999;
        parent[i] = -1;
        inMST[i] = false;
    }

    key[randS] = 0;
    mpq.insert(randS, 0);

    while (!mpq.isEmpty()) {
        Pair curr = mpq.extractMin();    // Get node with smallest key
        int u = curr.vertex;
        inMST[u] = true;

        Node *neigbor = g.getAdjList()[u];
        while (neigbor != nullptr) {
            int v = neigbor->vertex;
            int w = neigbor->weight;

            if (!inMST[v] && w < key[v]) {
                key[v] = w;              // Update best edge to v
                parent[v] = u;

                if (mpq.contains(v)) {
                    mpq.decreaseKey(v, key[v]);
                } else {
                    mpq.insert(v, key[v]);
                }
            }
            neigbor = neigbor->next;
        }
    }

    Graph mst(n);
    for (int v = 0; v < n; v++) {
        if (parent[v] != -1) {
            mst.addEdge(parent[v], v, key[v]);
        }
    }

    delete[] inMST;
    delete[] key;
    delete[] parent;
    return mst;
}

// Goes over the graph and collects all edges (no duplicates).
// Only adds edge (u,v) when v > u to avoid counting both directions.
// Returns a dynamic array of Edge and updates edgeCount.
Edge* Algorithms::extractEdgesFromGraph(const Graph &g, int& edgeCount)
{
    int n = g.getNumVertices();
    Node** adj = g.getAdjList();

    Edge* edges = new Edge[n * (n - 1) / 2]; // Max possible
    edgeCount = 0;

    for (int u = 0; u < n; u++) {
        Node* curr = adj[u];
        while (curr != nullptr) {
            int v = curr->vertex;
            int w = curr->weight;

            if (v > u) {                 // Avoid duplicates
                edges[edgeCount++] = Edge(u, v, w);
            }
            curr = curr->next;
        }
    }

    return edges;
}

// Runs Kruskal's algorithm to find MST of the graph.
// Sorts all edges and uses Union-Find to avoid cycles.
// Adds smallest edges that connect new components.
// Returns MST as a new Graph.
Graph Algorithms::kruskal(const Graph &g)
{
    int n = g.getNumVertices();
    int edgeCount = 0;

    Edge *edge = extractEdgesFromGraph(g, edgeCount);  // Get edges
    selectionSort(edge, edgeCount);                    // Sort edges by weight

    UnionFind uf(n);
    Graph mst(n);

    for (int i = 0; i < edgeCount; i++) {
        int u = edge[i].u;
        int v = edge[i].v;

        if (!uf.connected(u, v)) {
            uf.unite(u, v);                     // Join sets
            mst.addEdge(u, v, edge[i].weight);  // Add edge to MST
        }
    }

    delete[] edge;
    return mst;
}
