#include "Algorithms.hpp"
using namespace graph;

Graph Algorithms::bfs(const Graph &g, int s)
{
    int n = g.getNumVertices();
    int *parent = new int[n];
    int *weightParent = new int[n];
    for (int i = 0; i < n; i++)
    {
        parent[i] = -1;
        weightParent[i] = 0;
    }

    Queue q(n);
    q.enqueue(s);
    parent[s] = s;
    while (!q.isEmpty())
    {
        int curr = q.dequeue();
        Node *neighbor = g.getAdjList()[curr];
        while (neighbor != nullptr)
        {
            int v = neighbor->vertex;
            if (parent[v] == -1)
            {
                parent[v] = curr;
                weightParent[v] = neighbor->weight;
                q.enqueue(v);
            }
            neighbor = neighbor->next;
        }
    }
    Graph bfsTree(n);
    for (int i = 0; i < n; i++)
    {
        if (parent[i] != -1 && parent[i] != i)
        {
            bfsTree.addEdge(parent[i], i, weightParent[i]);
        }
    }
    delete[] parent;
    delete[] weightParent;
    return bfsTree;
}

void Algorithms::dfs_visit(const Graph &g, int u, bool *visited, Graph &dfsTree)
{
    visited[u] = true;
    Node *neighbor = g.getAdjList()[u];
    while (neighbor != nullptr)
    {
        int v = neighbor->vertex;
        if (!visited[v])
        {
            dfsTree.addEdge(u, v, neighbor->weight);
            dfs_visit(g, v, visited, dfsTree);
        }
        neighbor = neighbor->next;
    }
}

Graph Algorithms::dfs(const Graph &g, int s)
{
    int n = g.getNumVertices();
    bool *visited = new bool[n];
    for (int i = 0; i < n; i++)
        visited[i] = false;

    Graph dfsTree(n);

    for (int i = s; i < n; i++)
    {
        if (!visited[i])
        {
            dfs_visit(g, i, visited, dfsTree);
        }
    }
    for (int i = 0; i < s; i++)
    {
        if (!visited[i])
        {
            dfs_visit(g, i, visited, dfsTree);
        }
    }

    delete[] visited;
    return dfsTree;
}
Graph Algorithms::dijkstra(const Graph &g, int s)
{
    if (g.getIsNegative()) {
        throw std::logic_error("Dijkstra cannot run on graphs with negative edge weights.");
    }

    if (s < 0 || s >= g.getNumVertices()) {
        throw std::out_of_range("dijkstra: Source vertex index out of bounds");
    }
    int n = g.getNumVertices();
    int *dist = new int[n];
    int *parent = new int[n];
    int *weightParent = new int[n];
    for (int i = 0; i < n; i++)
    {
        dist[i] = 9999;
        parent[i] = -1;
        weightParent[i] = 0;
    }
    parent[s] = s;
    dist[s] = 0;
    MinPriorityQueue mpq(n);
    mpq.insert(s, 0);
    while (!mpq.isEmpty())
    {
        Pair curr = mpq.extractMin();
        int u = curr.vertex;

        Node *neighbor = g.getAdjList()[u];
        while (neighbor != nullptr)
        {
            int v = neighbor->vertex;
            int w = neighbor->weight;
            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                parent[v] = u;
                weightParent[v] = w;

                if (mpq.contains(v))
                {
                    mpq.decreaseKey(v, dist[v]);
                }
                else
                {
                    mpq.insert(v, dist[v]);
                }
            }
            neighbor = neighbor->next;
        }
    }
    Graph dijkstraTree(n);
    for (int i = 0; i < n; i++)
    {
        if (parent[i] != -1 && parent[i] != i)
        {
            dijkstraTree.addEdge(parent[i], i, weightParent[i]);
        }
    }

    delete[] dist;
    delete[] parent;
    delete[] weightParent;
    return dijkstraTree;
}

Graph Algorithms::prim(const Graph &g, int randS)
{
    //here i check if the graph is connected
    if (randS < 0 || randS >= g.getNumVertices()) {
        throw std::out_of_range("prim: Source vertex index out of bounds");
    }
    Graph bfsTree = Algorithms::bfs(g, randS);
    int edgeCount = 0;
    for (int i = 0; i < bfsTree.getNumVertices(); i++) {
        Node* curr = bfsTree.getAdjList()[i];
        while (curr != nullptr) {
            edgeCount++;
            curr = curr->next;
        }
    }
    edgeCount /= 2; // beacuse every edge is counted twice

    if (edgeCount < g.getNumVertices() - 1)
     {
        throw std::logic_error("Prim requires a connected graph.");
    }
    int n = g.getNumVertices();
    bool *inMST = new bool[n];
    int *parent = new int[n];
    int *key = new int[n];
    MinPriorityQueue mpq(n);
    for (int i = 0; i < n; i++)
    {
        key[i] = 9999;
        parent[i] = -1;
        inMST[i] = false;
    }
    key[randS] = 0;
    mpq.insert(randS, 0);
    while (!mpq.isEmpty())
    {
        Pair curr = mpq.extractMin();
        int u = curr.vertex;
        inMST[u] = true;
        Node *neigbor = g.getAdjList()[u];
        while (neigbor != nullptr)
        {
            int v = neigbor->vertex;
            int w = neigbor->weight;
            if (!inMST[v] && w < key[v])
            {
                key[v] = w;
                parent[v] = u;

                if (mpq.contains(v))
                {
                    mpq.decreaseKey(v, key[v]);
                }
                else
                {
                    mpq.insert(v, key[v]);
                }
            }
            neigbor = neigbor->next;
        }
    }
    Graph mst(n);
    for (int v = 0; v < n; v++)
    {
        if (parent[v] != -1)
        {
            mst.addEdge(parent[v], v, key[v]);
        }
    }

    delete[] inMST;
    delete[] key;
    delete[] parent;

    return mst;
}
Edge* Algorithms::extractEdgesFromGraph(const Graph &g,int& edgeCount){
    int n = g.getNumVertices();
    Node** adj = g.getAdjList();

    Edge* edges = new Edge[n * (n - 1) / 2]; 
    edgeCount = 0;

    for (int u = 0; u < n; u++) {
        Node* curr = adj[u];
        while (curr != nullptr) {
            int v = curr->vertex;
            int w = curr->weight;

            if (v > u) { 
                edges[edgeCount++] = Edge(u, v, w);
            }

            curr = curr->next;
        }
    }

    return edges;
}
Graph Algorithms::kruskal(const Graph &g)
{
int n = g.getNumVertices();
int edgeCount = 0;
Edge *edge = extractEdgesFromGraph(g,edgeCount);
selectionSort(edge,edgeCount);
UnionFind uf(n);
Graph mst(n);

for(int i = 0; i < edgeCount; i++)
{
int u = edge[i].u;
int v = edge[i].v;

if(!uf.connected(u,v))
{
uf.unite(u,v);
mst.addEdge(u,v,edge[i].weight);
}
}
delete[] edge;
return mst;
}
