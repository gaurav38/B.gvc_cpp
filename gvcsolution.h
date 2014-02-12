#ifndef GVCSOLUTION_H
#define GVCSOLUTION_H

#include "solution.h"
#include "graph.h"

#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <stdint.h>
#include <cstdlib>

using namespace std;

class GVCSolution : public Solution {
public:
    GVCSolution(const unsigned int L, Graph*&);
    int evaluate();	//returns the number of edges not covered by a vertex-cover
    void random();
    string toString() const;
    void good();
    GVCSolution& operator= (const string& str);
    void flip(const unsigned int i) { 
    	Solution::flip(i); 
        coord[i] = (coord[i] == 1)? 0:1;
	key ^= rkey[i];
    };
    static int getKnownTarget(const unsigned int L) { 
	return L;
    };
    inline string getType() const { return "B.gvc"; }

private:
    Graph *graph;
    static bool brand();
};

#endif // GVCSOLUTION_H
