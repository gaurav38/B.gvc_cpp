#include "graph.h"
#include <iostream>


Graph::Graph(string filename) {
	instanceDef = filename;
	readGraph();
}

void Graph::readGraph() {
	ifstream inFile(instanceDef.c_str());
	string inLine, comment;
	NodeID node1, node2;
	char lineType;
	Edge edge;
	if(inFile.is_open()) {
                getline(inFile, inLine);
                istringstream iss(inLine);
                lineType = iss.get();
                while(lineType != 'p') {
                        getline(inFile, inLine);
                        istringstream iss(inLine);
                        lineType = iss.get();
                }
                
                if(lineType == 'p') {
                        istringstream iss(inLine);
                        iss>>lineType>>comment>>numNodes>>numEdges;
                }
                while(getline(inFile, inLine)) {
                        istringstream iss(inLine);
                        if(!(iss>>lineType>>node1>>node2)) {
				cerr<<"Invalid edge representation in the graph file"<<endl<<endl;
				exit(1);
			}
                        edge = make_pair(node1, node2);
			edgeList.push_back(edge);
                }
		inFile.close();
        }
	else {
		cerr<<"Error opening the instanceDef "<<instanceDef<<endl<<endl;
		exit(1);
	}
}

unsigned int Graph::getNumNodes() {
	return numNodes;
}

int Graph::getNumEdges() {
	return numEdges;
}

int Graph::getNumEdgesCovered(int *coord) {
	EdgeList::iterator it;
	int edgesCovered = 0;
	for(it=edgeList.begin(); it<edgeList.end(); it++) {
		if(coord[it->first-1] == 1 || coord[it->second-1] == 1)
			edgesCovered++;
	}
	return(edgesCovered);
}
	
void Graph::printGraph() {
	int edges = 0;
	EdgeList::iterator it;
	for(it=edgeList.begin(); it<edgeList.end(); it++) {
		cout<<"Edge = "<<it->first<<" "<<it->second<<endl;
		edges++;
	}
	cout<<"Total edges read= "<<edges<<endl;
}


				
