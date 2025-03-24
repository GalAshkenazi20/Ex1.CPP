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
        weightParent[i] = 0 ;
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
