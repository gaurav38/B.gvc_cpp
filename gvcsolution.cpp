#include "gvcsolution.h"

#include <limits>
#include <cstring>


GVCSolution::GVCSolution(const unsigned int L, Graph *&graph): Solution(L) {
	this->graph = graph;
}

int GVCSolution::evaluate() {
    value=0;
    int numedges = graph->getNumEdges();
    int edgesCovered = graph->getNumEdgesCovered(coord);        
    cntProbe++;
    if(edgesCovered == numedges) {
        for(unsigned int k=0; k<L; k++)
	    value += coord[k];
    } else {
        value = numedges*(1 + numedges - edgesCovered);
    }
    return(value);
}

void GVCSolution::random(){
    key = 0;
    for(unsigned int i=0; i<L; i++){
        if(brand()){
            coord[i] = 1;
            key ^= rkey[i];
        }
        else coord[i] = 0;
    }
}

GVCSolution& GVCSolution::operator= (const string& str){
    key = 0;
    if(str.length() != L){
        cerr<<"Wrong binary string length:"<<str.length()<<endl;
        exit(1);
    }
    for(unsigned int i=0; i<L; i++){
        if(str[i] == '1') coord[i] = 1;
        else if(str[i] == '0') coord[i] = -1;
        else{
            cerr<<"Wrong sequence:"<<str<<endl;
            exit(1);
        }
        if(coord[i] == 1) key ^= rkey[i];
    }
    return *this;
}

string GVCSolution::toString() const {
    string str = "";
    for(unsigned int i=0; i<L; i++){
        if(coord[i] == 1) str += "1";
        else str += "0";
    }
    return str;
}

void GVCSolution::good() {
    #ifndef NDEBUG
    uint64_t tmpKey = 0;
    for(unsigned int i = 0; i<L; i++){
        if(coord[i] == 1) tmpKey ^= rkey[i];
        else if(coord[i] != -1){
            cerr<<"Wrong sequence (bit)!"<<endl;
            cerr<<*this<<endl;
            exit(1);
        }
    }
    if(key != tmpKey){
        cerr<<"Wrong sequence (key)!"<<endl;
        exit(1);
    }
    int tmpValue = value;
    if(tmpValue != evaluate()){
        cerr<<"Wrong sequence (eval)!"<<endl;
        cerr<<*this<<endl;
        exit(1);
    }
    cntProbe--;
    #endif
}

bool GVCSolution::brand(){
    if(rand()/double(RAND_MAX) < 0.5 ) return true;
    return false;
}
