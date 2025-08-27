// Calef Alesse
// Student ID: 2439923
// calesse@chapman.edu
// CPSC 350- 03
// PA06 Kruskal's 

#include "WGraph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <vector>
#include <queue>

WGraph::WGraph(){
  m_size = 0;
  m_adj = NULL;
}

WGraph::WGraph(unsigned int sz){
  m_size = sz;
  recalcFW = true;
  //allocate sz * sz adj matrix
  m_adj = new double*[sz];
  m_conn = new double*[sz]; // allocate m_conn memory 
  for(int i = 0; i < m_size; ++i){
    m_adj[i] = new double[sz];
    m_conn[i] = new double[sz];
  }
  //start with edges
  for(int i = 0; i < m_size; ++i){
    for(int j = 0; j < m_size; ++j){
      m_adj[i][j] = std::numeric_limits<double>::max();
      m_conn[i][j] = std::numeric_limits<double>::max();
    }
  }
}

WGraph::~WGraph(){
  //release memory
}

void WGraph::addEdge(VertexID i, VertexID j, double w){
  if(i < m_size && j < m_size){
    m_adj[i][j] = w;
    m_adj[j][i] = w;
    recalcFW = true;
  }
}

void WGraph::removeEdge(VertexID i, VertexID j){
  if(i < m_size && j < m_size){
    m_adj[i][j] = std::numeric_limits<double>::max();
    m_adj[j][i] = std::numeric_limits<double>::max();
    recalcFW = true;
  }
}

bool WGraph::areAdjacent(VertexID i, VertexID j){
  return (m_adj[i][j] < std::numeric_limits<double>::max());
}

void WGraph::calcFW(){
	if (!recalcFW){ return; }
	
  for(int i = 0; i < m_size; ++i){
    for(int j = 0; j < m_size; ++j){
      m_conn[i][j] = m_adj[i][j]; //start with conn == adj matrix
    }
  }

  // check if there are cheaper paths by going through intermediate nodes (start at 0 and increment)
  for(int im = 0; im < m_size; ++im){ //transitive closure (im = number of intermediate nodes for this path)
    for(int source = 0; source < m_size; ++source){ // iterate through the rows (source)
      for(int sink = 0; sink < m_size; ++sink){ // iterate through columns
        // every possible pair of source, sink and intermediate node
        if(source==sink){ // skip, no self loops
          continue;
        }
        if(m_conn[source][im] != std::numeric_limits<double>::max() && // not infinity
           m_conn[im][sink] != std::numeric_limits<double>::max() && 
           m_conn[source][sink] > m_conn[source][im] + m_conn[im][sink]){ // if direct path is greater than intermediate path
           // set equal to cheaper path through intermediate node
          m_conn[source][sink] = m_conn[source][im] + m_conn[im][sink]; 
        }

      }
    }
  }
}

double WGraph::cheapestCost(VertexID i, VertexID j){
	if (recalcFW){ 
		calcFW();  // only re-calculate if something new was added or removed 
	} 
  return m_conn[i][j];
}


void WGraph::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        // Used Stack Overflow resource to throw errors
        throw std::runtime_error("Error: Unable to open file.");
    }

    std::string line;
    int size;

    // Read number of nodes
    std::getline(file, line);
    std::stringstream ss(line);
    ss >> size;

    // Initialize graph
    *this = WGraph(size);

    // Read adjacency matrix line by line
    for (int i = 0; i < size; ++i) {
        std::getline(file, line);
        std::stringstream row(line);
        for (int j = 0; j < size; ++j) {
            double weight;
            row >> weight;

            if (i == j) {
                m_adj[i][j] = 0.0;
            } else if (weight > 0.0) {
                m_adj[i][j] = weight;
            } else {
                m_adj[i][j] = std::numeric_limits<double>::max();  // No connection
            }
        }
    }

    file.close();

}


  /*CHAT GPT prompt: how to simplify Kruskal's algorithm instead of using multiple vectors? */ 
  /* Response: Use a helper class to represent edges */
class Edge {
    public:
        int u, v;
        double weight;

    // edge with 2 nodes and a weights
    Edge(int from, int to, double w) {
        u = from;
        v = to;
        weight = w;
    }

    // Needed for priority queue (min-heap)
    bool operator>(const Edge& other) const {
        return this->weight > other.weight;
    }
};

void WGraph::computeMST(){

    // Make a copy of the original adjacency matrix
    std::vector<std::vector<double> > mstAdj(m_size, std::vector<double>(m_size, 0.0));

    // copy values over to new matrix
    for (unsigned int i = 0; i < m_size; ++i) {
        for (unsigned int j = 0; j < m_size; ++j) {
            // mstAdj[i][j] = m_adj[i][j];
            mstAdj[i][j] = 0;
        }
    }

    // priority queue to get smallest edge first
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge> > pq;

    // Add all edges from the adjacency matrix to the priority queue
    for (unsigned int i = 0; i < m_size; ++i) {
        for (unsigned int j = i + 1; j < m_size; ++j) {
            if (m_adj[i][j] < std::numeric_limits<double>::max()) {
                pq.push(Edge(i, j, m_adj[i][j]));
            }
        }
    }


    // vector to keep track of which vertices are connected
    std::vector<int> component(m_size);
    for (unsigned int i = 0; i < m_size; ++i) {
        // each start out as their own component
        component[i] = i;
    }

    // total cost
    double mstCost = 0;
    // edges added
    int edgesAdded = 0;

    // process edges, smallest first
    while (edgesAdded < (int)m_size - 1 && !pq.empty()) {
        // get edge with smallest weight 
        Edge current = pq.top();
        pq.pop();

        // first vertex of edge
        int u = current.u;
        // second vertex of edge 
        int v = current.v;

        // if they are not the same 
        if (component[u] != component[v]) {
            // Add edge
            mstAdj[u][v] = current.weight;
            mstAdj[v][u] = current.weight;

            // add edge weight to the total cost
            mstCost += current.weight;
            edgesAdded++;

            // Merge components (sets of vertices connected by edge)
            int oldComponent = component[v];
            int newComponent = component[u];
            for (unsigned int i = 0; i < m_size; ++i) {
                if (component[i] == oldComponent) {
                    component[i] = newComponent;
                }
            }
        }
    }


    // Output the total cost of the MST
    std::cout << "The MST Cost is: " << mstCost << std::endl;

    // Output the MST adjacency matrix
    for (unsigned int i = 0; i < m_size; ++i) {
        for (unsigned int j = 0; j < m_size; ++j) {
            // If the edge is not in the MST, print "0.0"
            if (mstAdj[i][j] == std::numeric_limits<double>::max()) {
                std::cout << "0.0 ";
            } else {
                std::cout << mstAdj[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }

}