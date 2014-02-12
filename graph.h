#ifndef GRAPH_H
#define GRAPH_H

//#include "node.h"
#include <vector>
#include <utility>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>

using namespace std;

typedef pair<unsigned int, unsigned int> Edge;
typedef vector<Edge> EdgeList;
typedef unsigned int NodeID;

/**
  * The class Graph reads the graph filename represented by instanceDef in the
  * in the input parameters. Graph is stored as an adjacency list where an unordered_map
  * is used to store the pointers to all the nodes indexed by their id. Each node has a 
  * vector which stores ids of all its neighbors. Refer node.cpp and node.h for the 
  * implementation of vectors representing adjacency list.
  */

class Graph {
public:
	//Constructor to initialize the graph. Requires filename as a mandatory parameter
	Graph(string);

	/**
	  * Function to return the number of nodes in the graph. This value will be used to
	  * set the value of "L"
	  */ 
	unsigned int getNumNodes();

	/**
	  * Function to return the number of edges in the graph. This value will be used to
	  * during function evaluation to check whether all the edges have been covered by a
	  * set of vertices.
	  */
	int getNumEdges();

	/**
	  * Function to return the number of edges covered by a coord. This function will
	  * be used during evaluation to get the total number of edges covered by a coordinate
	  */
	int getNumEdgesCovered(int*);

	void printGraph();
private:
	/**
	  * Function to read graph from a file specified by instanceDef. 
	  * This function reads an edge from the file and saves it to a 
	  * vector of "pairs" represented by edgeList member variable.
	  */
	void readGraph();

	string instanceDef;	
	EdgeList edgeList;
	unsigned int numNodes;
	int numEdges;
};

#endif // GRAPH_H
	
