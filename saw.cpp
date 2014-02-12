#include "saw.h"

#include <iostream>
#include <limits>

using namespace std;

void SAW::neighborhod(Solution & pivot, unordered_set<uint64_t>& walk, unsigned int & neighbSize){
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
        bit = bestBit[rand(bits)];
        pivot.flip(bit);
        pivot.setValue(stepValue);
        pivot.good();
    }
    else{
        pivot.setBlocked();
        pivot.good();
    }
}

void SAW::run(Solution & pivot, Solution & best){
    unsigned int neighbSize;
    unordered_set<uint64_t> walk;
    step = 0;
    writeWalkLine(pivot,pivot,0);
    writeTraceLine(pivot,pivot,0);
    while(!stoppingConditions(pivot)){
        walk.insert(pivot.getKey());
        Solution old(pivot);
        neighborhod(pivot,walk,neighbSize);
        step++;
        walkLength++;
        if(neighbSize > 0){
            writeWalkLine(pivot,old,neighbSize);
            if(pivot.getValue() <= best.getValue()){
                best = pivot;
                if(pivot.getValue() <= valueTarget) break;
            }
            writeTraceLine(pivot,pivot,0);
        }
        else{
            writeWalkLine(pivot,old,neighbSize);
            writeTraceLine(pivot,pivot,0);
            break;
        }
    }
}
