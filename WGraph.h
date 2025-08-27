// Calef Alesse
// Student ID: 2439923
// calesse@chapman.edu
// CPSC 350- 03
// PA06 Kruskal's 

#ifndef WGraph_H
#define WGraph_H

#include <cstdlib>
#include <deque>
#include <set>
#include <stack>
#include <iostream>
#include <limits>

// an unweighted, undirected WGraph implemented with adjacency matrix
// fixed size

typedef unsigned int VertexID;

class WGraph{
public:
  WGraph();
  WGraph(unsigned int sz);
  ~WGraph();
  void addEdge(VertexID i, VertexID j, double w);
  void removeEdge(VertexID i, VertexID j);
  bool areAdjacent(VertexID i, VertexID j);
  double cheapestCost(VertexID i, VertexID j);
  void calcFW();
  void computeMST();
  void loadFromFile(const std::string& filename); // constructor reads in file

private:
  double** m_adj;
  unsigned int m_size; //nodes in WGraph (fixed)
  // FW code
  bool recalcFW; // Flag to determine if Floyd-Warshall needs recalculation
  double** m_conn; // result of FW

};

// WGraph::WGraph(){
//   m_size = 0;
//   m_adj = NULL;
// }

// WGraph::WGraph(unsigned int sz){
//   m_size = sz;
//   recalcFW = true;
//   //allocate sz * sz adj matrix
//   m_adj = new double*[sz];
//   m_conn = new double*[sz]; // allocate m_conn memory 
//   for(int i = 0; i < m_size; ++i){
//     m_adj[i] = new double[sz];
//     m_conn[i] = new double[sz];
//   }
//   //start with edges
//   for(int i = 0; i < m_size; ++i){
//     for(int j = 0; j < m_size; ++j){
//       m_adj[i][j] = std::numeric_limits<double>::max();
//       m_conn[i][j] = std::numeric_limits<double>::max();
//     }
//   }
// }

// WGraph::~WGraph(){
//   //release memory
// }

// void WGraph::addEdge(VertexID i, VertexID j, double w){
//   if(i < m_size && j < m_size){
//     m_adj[i][j] = w;
//     m_adj[j][i] = w;
//     recalcFW = true;
//   }
// }

// void WGraph::removeEdge(VertexID i, VertexID j){
//   if(i < m_size && j < m_size){
//     m_adj[i][j] = std::numeric_limits<double>::max();
//     m_adj[j][i] = std::numeric_limits<double>::max();
//     recalcFW = true;
//   }
// }

// bool WGraph::areAdjacent(VertexID i, VertexID j){
//   return (m_adj[i][j] < std::numeric_limits<double>::max());
// }

// void WGraph::calcFW(){
// 	if (!recalcFW){ return; }
	
//   for(int i = 0; i < m_size; ++i){
//     for(int j = 0; j < m_size; ++j){
//       m_conn[i][j] = m_adj[i][j]; //start with conn == adj matrix
//     }
//   }

//   // check if there are cheaper paths by going through intermediate nodes (start at 0 and increment)
//   for(int im = 0; im < m_size; ++im){ //transitive closure (im = number of intermediate nodes for this path)
//     for(int source = 0; source < m_size; ++source){ // iterate through the rows (source)
//       for(int sink = 0; sink < m_size; ++sink){ // iterate through columns
//         // every possible pair of source, sink and intermediate node
//         if(source==sink){ // skip, no self loops
//           continue;
//         }
//         if(m_conn[source][im] != std::numeric_limits<double>::max() && // not infinity
//            m_conn[im][sink] != std::numeric_limits<double>::max() && 
//            m_conn[source][sink] > m_conn[source][im] + m_conn[im][sink]){ // if direct path is greater than intermediate path
//            // set equal to cheaper path through intermediate node
//           m_conn[source][sink] = m_conn[source][im] + m_conn[im][sink]; 
//         }

//       }
//     }
//   }
// }

// double WGraph::cheapestCost(VertexID i, VertexID j){
// 	if (recalcFW){ 
// 		calcFW();  // only re-calculate if something new was added or removed 
// 	} 
//   return m_conn[i][j];
// }


#endif
