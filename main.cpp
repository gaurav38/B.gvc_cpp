#include <sstream>
#include "solver.h"
#include "graph.h"

using namespace std;

int main(int argc, char *argv[])
{
    stringstream ss(stringstream::in | stringstream::out);

    for(int i = 1; i < argc; i++) ss<<argv[i]<<" ";
    Solver solver(ss,argv[0]);
    solver.run();
    
    //Graph *graph = new Graph(argv[1]);
    //graph->printGraph();
    //int blah = graph->getNumEdgesCovered(2);
    //cout<<"Edges covered by 2 = "<<blah<<endl;
    return 0;
}

