#include "solution.h"

#include <limits>
#include <cstring>

unsigned int Solution::MAX_L = 0;
int Solution::valueTarget = 0;
uint64_t* Solution::rkey = NULL;
uint64_t Solution::cntProbe = 0;

Solution::Solution(const unsigned int L){
    if(L > MAX_L || L < MIN_L){
        cerr<<"Wrong L:"<<L<<endl;
        exit(1);
    }
    this->L = L;
    coord = new int[L];
    key = 0;
    value =  numeric_limits<int>::max();
    //value = L;
    censored = blocked = 0;
}

void Solution::init(const unsigned int MAX_L){
    if(MAX_L < MIN_L){
        cerr<<"Wrong MAX_L:"<<MAX_L<<endl;
        exit(1);
    }
    Solution::MAX_L = MAX_L;
    if(rkey != NULL) delete [] rkey;
    // No need for rkey in VC problem. Commenting this
    rkey = new uint64_t[MAX_L];
    for(unsigned int i=0; i<MAX_L; i++) rkey[i] = rand64();
    cntProbe = 0;
}

Solution& Solution::operator= (const string& str){
    key = 0;
    if(str.length() != L){
        cerr<<"Wrong binary string length:"<<str.length()<<endl;
        exit(1);
    }
    for(unsigned int i=0; i<L; i++) coord[i] = str[i] - '0';
    return *this;
}

int Solution::distance(const Solution solution) const{
    unsigned int diff = 0;
    for(unsigned int i=0; i<L ; i++){
        if(coord[i] != solution.coord[i]) diff++;
    }
    return diff;
}
