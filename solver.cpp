#include "solver.h"

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <sys/utsname.h>

#include "gvcsolution.h"
#include "saw.h"
#include "sawj.h"

using namespace std;

Solver::Solver(stringstream &ss, const char program[]){
    defaultValues();
    loadCommandLine(ss,program);
}

void Solver::help(const char program[]){
    const int w = 4;
    cout<<"Usage: "<<program<<" functionName walkName instanceDef [options]"<<endl<<endl;
    cout<<"This program takes three required argument values in this order:"<<endl;
    cout<<endl<<setw(w)<<""<<"functionName walkName instanceDef"<<endl<<endl;
    cout<<"and a number of optional argument values under arbitrary order under the"<<endl;
    cout<<"following names:"<<endl<<endl;
    cout<<setw(w)<<""<<"cntProbeLmt cntRestartLmt coordInit runtimeLmt seed valueTarget"<<endl;
    cout<<setw(w)<<""<<"walkLengthCoef walkLengthLmt walkRestart writeInit writeStdout"<<endl;
    cout<<setw(w)<<""<<"writeTrace writeWalk writeWarning"<<endl<<endl;
    cout<<"Here are examples of two invocations:"<<endl<<endl;
    cout<<setw(w)<<""<<"./solvB fB.labs sawCT 13"<<endl<<endl;
    cout<<setw(w)<<""<<"./solvB fB.labs sawCT 7 -cntProbeLmt 2000 -cntRestartLmt 100 -coordInit 0101011"<<endl;
    cout<<setw(5*w)<<""<<"-runtimeLmt 30 -seed 123 -valueTarget 3 -walkLengthCoef U"<<endl;
    cout<<setw(5*w)<<""<<"-noRestart -writeInit -writeStdout -writeTrace -writeWalk"<<endl;
    cout<<setw(5*w)<<""<<"-writeWarning"<<endl<<endl;
    cout<<"Argument descriptions:"<<endl;
    cout<<setw(w)<<""<<"functionName ... name of the objective function to be optimized under"<<endl;
    cout<<setw(5*w)<<""<<"cordType=B (binary coordinates), e.g. fB.labs"<<endl;
    cout<<setw(w)<<""<<"walkName ....... name of the walk to be invoked by the solver,"<<endl;
    cout<<setw(5*w)<<""<<"e.g. sawCT or sawJT"<<endl;
    cout<<setw(w)<<""<<"instanceDef .... name of the instance to be solved, e.g. an integer"<<endl;
    cout<<setw(5*w)<<""<<"when the function name is fB.labs, a file name"<<endl;
    cout<<setw(5*w)<<""<<"when the function name is fPT.hgrPlace, etc."<<endl;
    cout<<setw(5*w)<<""<<"A value of nDim, the full length of binary coordinate,"<<endl;
    cout<<setw(5*w)<<""<<"is extracted from instanceDef"<<endl<<endl;
    cout<<setw(w)<<""<<"-cntProbeLmt    integer ... stop when this value is reached, default = 2^31 - 1"<<endl;
    cout<<setw(w)<<""<<"-cntRestartLmt  integer ... stop when this value is reached, default = 2^31 - 1"<<endl;
    cout<<setw(w)<<""<<"-coordInit    bitString ... initial binary string of length nDim,"<<endl;
    cout<<setw(8*w)<<""<<"default = a random binary string"<<endl;
    cout<<setw(w)<<""<<"-runtimeLmt     seconds ... stop after this number of seconds; default = 30"<<endl;
    cout<<setw(w)<<""<<"-seed           integer ... **unsigned** integer to initialize the random"<<endl;
    cout<<setw(8*w)<<""<<"number generator; default = internal random"<<endl;
    cout<<setw(w)<<""<<"-valueTarget    integer ... stop when this value is reached,"<<endl;
    cout<<setw(8*w)<<""<<"default = internal best known value to date"<<endl;
    cout<<setw(w)<<""<<"-walkLengthCoef integer ... factor that determines the value of walkLengthLmt:"<<endl;
    cout<<setw(8*w)<<""<<"default = U, implying that walkLengthLmt = 2^31 - 1,"<<endl;
    cout<<setw(8*w)<<""<<"otherwise walkLengthLmt = walkLengthCoef*nDim"<<endl;
    cout<<setw(8*w)<<""<<"(nDim = full length of the binary coordinate)"<<endl;
    cout<<setw(w)<<""<<"-walkLengthLmt  integer ... stop when this value is reached, default = 2^31 - 1"<<endl;
    cout<<setw(w)<<""<<"-noRestart      boolean ... the solver can restart each walk from a new random"<<endl;
    cout<<setw(8*w)<<""<<"coordinate, default = 0"<<endl;
    cout<<setw(w)<<""<<"-writeInit      boolean ... write all initialized arrays to stdout, default = 0"<<endl;
    cout<<setw(w)<<""<<"-writeTrace     boolean ... write traces to stdout, default = 0"<<endl;
    cout<<setw(w)<<""<<"-writeWalk      boolean ... write tabulated walk data to file, default = 0"<<endl;
    cout<<"------------------------------------------------------------------------------------------------"<<endl;
    cout<<"Copyright 2014"<<endl;
    cout<<"*  Franc Brglez, Borko Bošković, and Janez Brest"<<endl;
    cout<<"*  Paper: On Combinatorial Optimization and Self-Avoiding Contiguous and"<<endl;
    cout<<"*         Non-Contiguous Walks: The Labs Problem  (see the latex template from today …)"<<endl;
    cout<<"*  Walks: sawCT, sawJT"<<endl;
    cout<<"*  Preview at http://arxiv.org/"<<endl;
    cout<<"*  Version "<<VERSION<<endl;
}

void Solver::defaultValues(){
    functionName = "gvc";
    walkName = "sawCT";
    instanceDef = "";

    cntProbeLmt = pow(2,31) - 1;
    cntRestartLmt = pow(2,31) - 1;
    coordInit = "";
    runtimeLmt = 30;
    seed = 0;
    valueTarget = 0;
    walkLengthCoef =  pow(2,31) - 1;
    walkLengthLmt = pow(2,31) - 1;
    noRestart = false;
    writeInit = false;
    writeTrace = false;
    writeWalk = false;

    cntRestart = 0;
}

void Solver::loadCommandLine(stringstream& ss, const char program[]){
    string command;
     bool userSeed = false;
    if(ss.str().empty()){
        help(program);
        exit(0);
    }
    if(!(ss >> functionName)){
        cerr<<"Error: argument functionName!"<<endl<<endl;
        exit(1);
    }
    if(!(ss >> walkName)){
        cerr<<"Error: argument walkName!"<<endl<<endl;
        exit(1);
    }
    if(!(ss >> instanceDef)){
        cerr<<"Error: argument instanceDef!"<<endl<<endl;
        exit(1);
    }
    while(ss >> command){
        if(command == "-cntProbeLmt"){ ss>>cntProbeLmt; }
        else if(command == "-cntRestartLmt"){ ss>>cntRestartLmt; }
        else if(command == "-coordInit"){ ss>>coordInit; }
        else if(command == "-runtimeLmt"){ ss>>runtimeLmt; }
        else if(command == "-seed"){
            ss>>seed;
            userSeed = true;
        }
        else if(command == "-valueTarget"){ ss>>valueTarget; }
        else if(command == "-walkLengthCoef"){
            ss>>walkLengthCoef;
            if(!ss.good()){
                ss.clear();
                string wl;
                ss>>wl;
                if(wl == "U") walkLengthCoef = walkLengthLmt = pow(2,31) - 1;
            }
        }
        else if(command == "-walkLengthLmt"){ ss>>walkLengthLmt; }
        else if(command == "-noRestart"){ noRestart = true; }
        else if(command == "-writeInit"){ writeInit = true; }
        else if(command == "-writeTrace"){ writeTrace = true; }
        else if(command == "-writeWalk"){ writeWalk = true; }
        else{
            cerr<<"Wrong commnad line argument:"<<command<<endl;
            exit(1);
        }
        if(!ss.good()){
            cerr<<"Wrong commnad line argument:"<<command<<endl;
            exit(1);
        }
    }
    if(!userSeed){
        srand((uint32_t)time(NULL));
        seed = (uint32_t)rand();
    }
    srand(seed);
}

bool Solver::stoppingConditions(Solution & solution){
    if(runtimeLmt != 0){
        double cuurentTime = double(clock() - start) / CLOCKS_PER_SEC;
        if(cuurentTime >= (double)runtimeLmt){
            solution.setCensored();
            return true;
        }
    }
    if(solution.isTargetReached())
        return true;
    if(cntRestart != 0 && cntRestart >= cntRestartLmt){
        solution.setCensored();
        return true;
    }
    if(cntProbeLmt != 0 && Solution::getCntProbe() >= cntProbeLmt){
        solution.setCensored();
        return true;
    }
    return false;
}

void Solver::results(const Solution &init, const Solution &best, const Walk & walk) const{
    const unsigned int w = 20;
    string hostId;
    utsname un;
    uname(&un);
    hostId = un.machine;
    hostId += "-";
    hostId += un.release;
    hostId += "-";
    hostId += un.sysname;

    cout<<left;
    cout<<setw(w)<<"instanceDef"<<instanceDef<<endl;
    cout<<setw(w)<<"nDim"<<best.getNDim()<<endl;
    cout<<setw(w)<<"nAsymp"<<best.getL()<<endl;
    cout<<setw(w)<<"functionName"<<best.getType()<<endl;
    cout<<setw(w)<<"solverName"<<walk.getType()<<endl;
    if(walkLengthCoef != 2147483647) cout<<setw(w)<<"walkLengthCoef"<<walkLengthCoef<<endl;
    else cout<<setw(w)<<"walkLengthCoef"<<"U"<<endl;
    cout<<setw(w)<<"walkLengthLmt"<<walkLengthLmt<<endl;
    cout<<setw(w)<<"walkLength"<<walk.getWalkLength()<<endl;
    cout<<setw(w)<<"cntRestartLmt"<<cntRestartLmt<<endl;
    cout<<setw(w)<<"cntRestart"<<cntRestart<<endl;
    cout<<setw(w)<<"cntProbeLmt"<<cntProbeLmt<<endl;
    cout<<setw(w)<<"cntProbe"<<best.getCntProbe()<<endl;
    cout<<setw(w)<<"runtimeLmt"<<runtimeLmt<<endl;
    cout<<setw(w)<<"runtime"<<(stop-start)/ CLOCKS_PER_SEC<<endl;
    cout<<setw(w)<<"speed"<<best.getCntProbe()/((stop-start)/CLOCKS_PER_SEC)<<endl;
    cout<<setw(w)<<"seedFirst"<<seed<<endl;
    cout<<setw(w)<<"coordInit"<<init<<endl;
    cout<<setw(w)<<"coordBest"<<best<<endl;
    cout<<setw(w)<<"valueInit"<<init.getValue()<<endl;
    cout<<setw(w)<<"valueBest"<<best.getValue()<<endl;
    cout<<setw(w)<<"valueTarget"<<valueTarget<<endl;
    cout<<setw(w)<<"targetReached"<<best.isTargetReached()<<endl;
    cout<<setw(w)<<"isCensored"<<best.isCensored()<<endl;
    cout<<setw(w)<<"hostID"<<hostId<<endl;
}

void Solver::printSettings(const Solution & init, const Walk& walk) const{
    const unsigned int w = 20;
    string hostId;
    utsname un;
    uname(&un);
    hostId = un.machine;
    hostId += "-";
    hostId += un.release;
    hostId += "-";
    hostId += un.sysname;

    cout<<left;
    cout<<setw(w)<<"# instanceDef"<<instanceDef<<endl;
    cout<<setw(w)<<"# nDim"<<init.getNDim()<<endl;
    cout<<setw(w)<<"# nAsymp"<<init.getL()<<endl;
    cout<<setw(w)<<"# functionName"<<init.getType()<<endl;
    cout<<setw(w)<<"# solverName"<<walk.getType()<<endl;
    cout<<setw(w)<<"# walkLengthCoef"<<walkLengthCoef<<endl;
    cout<<setw(w)<<"# walkLengthLmt"<<walkLengthLmt<<endl;
    cout<<setw(w)<<"# cntRestartLmt"<<cntRestartLmt<<endl;
    cout<<setw(w)<<"# cntProbeLmt"<<cntProbeLmt<<endl;
    cout<<setw(w)<<"# runtimeLmt"<<runtimeLmt<<endl;
    cout<<setw(w)<<"# seedFirst"<<seed<<endl;
    cout<<setw(w)<<"# coordInit"<<init<<endl;
    cout<<setw(w)<<"# valueInit"<<init.getValue()<<endl;
    cout<<setw(w)<<"# valueTarget"<<valueTarget<<endl;
    cout<<setw(w)<<"# hostID"<<hostId<<endl;
}

void Solver::run(){
    Solution * pivot = NULL, * best  = NULL, * init = NULL;
    Walk * walk = NULL;
    Graph *graph = new Graph(instanceDef);
    unsigned int instanceSize = graph->getNumNodes();
    start = clock();
    cntRestart = 0;

    if(functionName == "gvc"){
        if(valueTarget == 0)
            valueTarget = GVCSolution::getKnownTarget(instanceSize);
        GVCSolution::init(instanceSize);
        GVCSolution::setValueTarget(valueTarget);
        pivot = new GVCSolution(instanceSize, graph);
        best = new GVCSolution(instanceSize, graph);
        init = new GVCSolution(instanceSize, graph);
    }
    else{
        cerr<<"Error: functionName = "<<functionName<<endl;
        exit(1);
    }

    if(walkName == "sawCT"){ walk = new SAW(); }
    else if(walkName == "sawJT"){ walk = new SAWJ(); }
    else{
        cerr<<"Error: walkName ="<<walkName<<endl;
        exit(1);
    }

    if(coordInit.size() > 0) *pivot = coordInit;
    else pivot->random();

    if(walkLengthLmt == 2147483647 && walkLengthCoef != 2147483647)
        walkLengthLmt = walkLengthCoef * pivot->getNDim();

    walk->setWalkLengthLmt(walkLengthLmt);
    walk->setCntProbeLmt(cntProbeLmt);
    walk->setRuntimeLmt(runtimeLmt);
    walk->setStart(start);
    walk->setValueTarget(valueTarget);
    walk->setWriteWalk(writeWalk);
    walk->setCntRestart(cntRestart);
    walk->setSeed(seed);
    walk->setWriteTrace(writeTrace);
    walk->setWalkLength(0);

    pivot->evaluate();
    *init = *best = *pivot;
    if(writeInit) printSettings(*init,*walk);
    if(best->isTargetReached()) walk->writeWalkLine(*best,*best,0);
    pivot->good();
    best->good();
    while(!stoppingConditions(*best)){
        //cout<<"Starting pivot value is : "<<pivot->getValue()<<endl;
        walk->run(*pivot,*best);
	//cout<<"Best value is : "<<best->getValue()<<endl;
        if(best->isTargetReached()) break;
        if(noRestart){
            best->setCensored();
            break;
        }
        cntRestart++;
        walk->setWalkLength(walk->getWalkLength()+1);
        walk->setCntRestart(cntRestart);
        pivot->random();
        if(pivot->evaluate() < best->getValue()){
            *best = *pivot;
            if(best->isTargetReached()){
                walk->writeWalkLine(*best,*best,0);
                break;
            }
        }
    }

    stop = clock();
    results(*init, *best, *walk);

    delete pivot;
    delete best;
    delete walk;
}
