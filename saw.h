#ifndef SAW_H
#define SAW_H

#include <cstdlib>
#include <unordered_set>

#include "walk.h"

using namespace std;

class SAW : public Walk{
public:
    void run(Solution & init, Solution &best);
    string getType() const { return "sawCT"; }

protected:
    virtual void neighborhod(Solution & pivot, unordered_set<uint64_t>& walk, unsigned int& neighbSize);
    unsigned int rand(unsigned int n) { return n*(std::rand()/(RAND_MAX+1.0)); }
    
};

#endif // SAW_H
