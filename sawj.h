#ifndef SAWJ_H
#define SAWJ_H

#include "saw.h"

class SAWJ : public SAW
{
public:
     string getType() const { return "sawJT"; }
private:
     void neighborhod(Solution & pivot, unordered_set<uint64_t>& walk, unsigned int& neighbSize);
};

#endif // SAWJ_H
