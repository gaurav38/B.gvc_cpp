#include "walk.h"
#include <sstream>
#include <fstream>
#include <iomanip>
#include <iostream>

void Walk::run(Solution & init, Solution &best){
    best = init;
    step = 0;
}

bool Walk::stoppingConditions(Solution& solution){
    if(step >= walkLengthLmt) return true;
    if(runtimeLmt != 0){
        double currentTime = double(clock() - start) / CLOCKS_PER_SEC;
        if(currentTime >= (double)runtimeLmt){
            solution.setCensored();
            return true;
        }
    }
    if(solution.isTargetReached()) return true;
    if(cntProbeLmt != 0 && Solution::getCntProbe() >= cntProbeLmt){
        solution.setCensored();
        return true;
    }
    return false;
}

void Walk::writeWalkLine(const Solution &solution, const Solution & old,
                         const unsigned int neighbSize) const{
    stringstream ss;
    ss<<solution.getType()<<"-"<<getType()<<"-"<<solution.getL()<<"-"<<seed<<"-walk.txt";
    string filename = ss.str();
    ofstream file;

    static bool header = true;
    if(!writeWalk) return;
    if(header){
        file.open(filename,ofstream::out);
        if(!file.good()){
            cerr<<"Error opening file ("<<filename<<")"<<endl;
            exit(1);
        }
        header = false;
        time_t now = time(0);
        tm *ltm = localtime(&now);
        file<<"# From "<<getType()<<endl;
        file<<"# fileName = "<<filename<<endl;
        file<<"# timeStamp = "<<1900 + ltm->tm_year;
        if(1 + ltm->tm_mon < 10) file<<"0";
        file<<1 + ltm->tm_mon;
        if(ltm->tm_mday < 10) file<<"0";
        file<<ltm->tm_mday;
        if(1 + ltm->tm_hour < 10) file<<"0";
        file<<1 + ltm->tm_hour;
        if(1 + ltm->tm_min < 10) file<<"0";
        file<<1 + ltm->tm_min;
        if(1 + ltm->tm_sec < 10) file<<"0";
        file<<1 + ltm->tm_sec<<endl;
        file<<"# dateStamp = "<<ctime(&now);
        file<<"#"<<endl;
        file<<"# .. this file can be read in R."<<endl;
        file<<"#"<<endl;
        file<<setw(5)<<"step";
        file<<setw(11)<<"cntRestart";
        file<<setw(9)<<"distance";
        file<<setw(solution.getL()+1)<<"coord";
        file<<setw(6)<<"value";
        file<<setw(11)<<"neighbSize";
        file<<setw(9)<<"cntProbe";
        file<<setw(14)<<"targetReached";
        file<<endl;
    }
    else{
        file.open(filename, ofstream::out| ofstream::app);
        if(!file.good()){
            cerr<<"Error opening file ("<<filename<<")"<<endl;
            exit(1);
        }
    }
    file<<setw(5)<<step;
    file<<setw(11)<<cntRestart;
    file<<setw(9)<<solution.distance(old);
    file<<setw(solution.getL()+1)<<solution;
    file<<setw(6)<<solution.getValue();
    file<<setw(11)<<neighbSize;
    file<<setw(9)<<Solution::getCntProbe();
    file<<setw(14)<<solution.isTargetReached();
    file<<endl;

    file.close();
}

void Walk::writeTraceLine(const Solution &solution, const Solution & old,
                         const unsigned int neighbSize) const{
    static bool header = true;
    if(!writeTrace) return;
    if(header){
        header = false;
        cout<<setw(5)<<"step";
        cout<<setw(11)<<"cntRestart";
        cout<<setw(9)<<"distance";
        cout<<setw(solution.getL()+1)<<"coord";
        cout<<setw(6)<<"value";
        cout<<setw(11)<<"neighbSize";
        cout<<setw(9)<<"cntProbe";
        cout<<setw(14)<<"targetReached";
        cout<<endl;
    }

    cout<<setw(5)<<step;
    cout<<setw(11)<<cntRestart;
    cout<<setw(9)<<solution.distance(old);
    cout<<setw(solution.getL()+1)<<solution;
    cout<<setw(6)<<solution.getValue();
    cout<<setw(11)<<neighbSize;
    cout<<setw(9)<<Solution::getCntProbe();
    cout<<setw(14)<<solution.isTargetReached();
    cout<<endl;
}
