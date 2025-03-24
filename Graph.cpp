#include "Graph.hpp"
using namespace graph;
Graph::Graph(int n)
{
    this->n = n;
    this->adjacency_List = new Node *[n];
    for (int i = 0; i < n; i++)
    {
        adjacency_List[i] = nullptr;
    }
}
Graph::Graph(int n, Node **adj)
{
    this->n = n;
    this->adjacency_List = adj;
}
void Graph::addEdge(int u, int v, int w)
{
    Node *nodeU = new Node(v, w);
    nodeU->next = adjacency_List[u];
    adjacency_List[u] = nodeU;
    Node *nodeV = new Node(u, w);
    nodeV->next = adjacency_List[v];
    adjacency_List[v] = nodeV;
}
void Graph::removeEdge(int u, int v)
{
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
}
void Graph::print_graph(){
    for (int i = 0; i < n; i++) {
        std::cout << "Vertex " << i << ": ";
        Node* current = adjacency_List[i];
        while (current != nullptr) {
            std::cout << "-> (v:" << current->vertex << ", w:" << current->weight << ") ";
            current = current->next;
        }
        std::cout << std::endl;
    }
}
Graph::~Graph(){
    for(int i = 0; i < n; i++){
        Node* current = adjacency_List[i];
        while(current != nullptr){
            Node* temp  = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] adjacency_List;
}
int Graph::getNumVertices() const{
    return n;
}
Node** Graph::getAdjList() const{
    return adjacency_List;
}
