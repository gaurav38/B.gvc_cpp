#include "sawj.h"

#include <limits>

void SAWJ::neighborhod(Solution & pivot, unordered_set<uint64_t>& walk, unsigned int & neighbSize){
    unsigned int bestBit[pivot.getNDim()], bits, bit;
    int fValue, stepValue;
    neighbSize = 0, bits=0;
    stepValue = numeric_limits<int>::max();
    Solution old(pivot);
    for(unsigned int i=0; i<pivot.getNDim() && !pivot.isTargetReached(); i++){
        pivot.flip(i);
        if(walk.count(pivot.getKey()) > 0){
            pivot.flip(i);
            continue;
        }
        fValue = pivot.evaluate();
        neighbSize ++;
        writeTraceLine(pivot,old,neighbSize);
        pivot.flip(i);
        if(fValue < stepValue){
            pivot.flip(i);
            bestBit[0] = i;
            bits = 1;
            stepValue = fValue;
        }
        else if(fValue == stepValue){
            bestBit[bits] = i;
            bits++;
        }
    }
    if(bits > 0){
        if(bits > 1){
            bit = bestBit[1+rand(bits-1)];
            pivot.flip(bit);
        }
        pivot.setValue(stepValue);
        pivot.good();
    }
    else{
        pivot.setBlocked();
        pivot.good();
    }
}

