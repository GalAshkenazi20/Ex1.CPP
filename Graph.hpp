#ifndef _GRAPH_HPP_
#define _GRAPH_HPP_  
#include <iostream>
#include "DataStructures.hpp"

namespace graph{
    
    struct Node{
    int vertex;
    int weight;
    Node* next;
    Node(int v, int w): vertex(v), weight(w), next(nullptr){}
    };

    class Graph{
        private: 
            int n;
            Node**  adjacency_List;
            bool isNegative = false;
        public:
            Graph(int n);
            Graph(int n, Node** adj);
            ~Graph();
            void addEdge(int u, int v, int w);
            void removeEdge(int u, int v);
            void print_graph();
            int getNumVertices() const;
            Node** getAdjList() const;
            bool getIsNegative() const;
    };
}
#endif
