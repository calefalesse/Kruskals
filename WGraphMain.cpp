// Calef Alesse
// Student ID: 2439923
// calesse@chapman.edu
// CPSC 350- 03
// PA06 Kruskal's 

#include "WGraph.h"
#include <iostream>


int main(int argc, char* argv[]){

    // arg 1 = file
    std::string input = argv[1];

    // object of WGraph
    WGraph graph;
    graph.loadFromFile(input);  
    // run method  
    graph.computeMST();


    // test code
    // WGraph myGraph(7);

    // double adj[7][7] = {
    //     {0.0, 1.0, 0.0, 1.0, 8.0,10.0, 0.0},
    //     {1.0, 0.0, 1.0, 0.0, 0.0,10.0, 0.0},
    //     {0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0},
    //     {1.0, 0.0, 0.0, 0.0, 5.0, 5.0, 0.0},
    //     {8.0, 0.0, 1.0, 5.0, 0.0, 2.0, 2.0},
    //     {10.0,10.0, 0.0, 5.0, 2.0, 0.0, 0.0},
    //     {0.0, 0.0, 0.0, 0.0, 2.0, 0.0, 0.0}
    // };

    // for (int i = 0; i < 7; ++i) {
    //     for (int j = i + 1; j < 7; ++j) {
    //         if (adj[i][j] != 0.0) {
    //             myGraph.addEdge(i, j, adj[i][j]);
    //         }
    //     }
    // }

    // myGraph.computeMST();

  return 0;
}