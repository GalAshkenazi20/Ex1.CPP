#include "Graph.hpp"
using namespace graph;
//adding to adjacency list the vertices
Graph::Graph(int n)
{
    this->n = n;
    this->adjacency_List = new Node *[n];
    for (int i = 0; i < n; i++)
    {
        adjacency_List[i] = nullptr;
    }
}
// Constructor
Graph::Graph(int n, Node **adj)
{
    this->n = n;
    this->adjacency_List = adj;
}
void Graph::addEdge(int u, int v, int w)
{
    // Check if the vertex indices are within bounds
    if (u < 0 || u >= n || v < 0 || v >= n)
    {
        throw std::out_of_range("addEdge: Vertex index out of bounds");
    }
    //Check if we add a negative edge to the graph and update the variable
    if (w < 0)
    {
        isNegative = true;
    }
    // Create a new node for the edge and add it to the adjacency list
    Node *nodeU = new Node(v, w);
    nodeU->next = adjacency_List[u];
    adjacency_List[u] = nodeU;
    //because the graph is undirected, we add the edge for to the other vertex too
    Node *nodeV = new Node(u, w);
    nodeV->next = adjacency_List[v];
    adjacency_List[v] = nodeV;
}
// Function to remove an edge from the graph
void Graph::removeEdge(int u, int v)
{
    // Check if the vertex indices are within bounds
    if (u < 0 || u >= n || v < 0 || v >= n)
    {
        throw std::out_of_range("removeEdge: Vertex index out of bounds");
    }
    Node *currU = adjacency_List[u];
    if (currU != nullptr && currU->vertex == v)
    {
        adjacency_List[u] = currU->next;
        delete currU;
    }
    else
    {
        while (currU != nullptr && currU->next != nullptr)
        {
            if (currU->next->vertex == v)
            {
                Node *temp = currU->next;
                currU->next = currU->next->next;
                delete (temp);
                break;
            }
            currU = currU->next;
        }
    }
    Node *currV = adjacency_List[v];
    if (currV != nullptr && currV->vertex == u)
    {
        adjacency_List[v] = currV->next;
        delete currV;
    }
    else
    {
        while (currV != nullptr && currV->next != nullptr)
        {
            if (currV->next->vertex == u)
            {
                Node *temp = currV->next;
                currV->next = currV->next->next;
                delete (temp);
                break;
            }
            currV = currV->next;
        }
    }
    isNegative = false;
    for (int i = 0; i < n; i++)
    {
        Node *curr = adjacency_List[i];
        while (curr != nullptr)
        {
            if (curr->weight < 0)
            {
                isNegative = true;
                return;
            }
            curr = curr->next;
        }
    }
}
// Function to print the graph
void Graph::print_graph()
{
    for (int i = 0; i < n; i++)
    {
        std::cout << "Vertex " << i << ": ";
        Node *current = adjacency_List[i];
        while (current != nullptr)
        {
            std::cout << "-> (v:" << current->vertex << ", w:" << current->weight << ") ";
            current = current->next;
        }
        std::cout << std::endl;
    }
}
// Destructor to free memory
Graph::~Graph()
{
    for (int i = 0; i < n; i++)
    {
        Node *current = adjacency_List[i];
        while (current != nullptr)
        {
            Node *temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] adjacency_List;
}
//helper function to get the number of vertices
int Graph::getNumVertices() const
{
    return n;
}
//getter for the adjacency list, beacause adjacency_list is private
Node **Graph::getAdjList() const
{
    return adjacency_List;
}
//getter for isNegative, to check if the graph has negative edges(for dijkstra)
bool Graph::getIsNegative() const
{
    return isNegative;
}
