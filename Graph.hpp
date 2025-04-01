#ifndef _GRAPH_HPP_
#define _GRAPH_HPP_  
#include <iostream>
#include "DataStructures.hpp"

namespace graph{
    
    struct Node{
    int vertex;
    int weight;
    Node* next;
    Node(int v, int w): vertex(v), weight(w), next(nullptr){} // constructor
    };

    class Graph{
        private: 
            int n; //number of vertices
            Node**  adjacency_List; 
            bool isNegative = false; //boolean variable to check if the graph has negative weights
        public:
            Graph(int n); //addding to adjacency list the vertices
            Graph(int n, Node** adj);// constructor to initialize the graph with an adjacency list
            ~Graph(); // destructor to free memory
            void addEdge(int u, int v, int w); // function to add an edge
            void removeEdge(int u, int v); // function to remove an edge
            void print_graph(); //print the graph
            int getNumVertices() const; // Getter for number of vertices
            Node** getAdjList() const; //getter for adjacency list
            bool getIsNegative() const; //getter for isNegative
    };
}
#endif
