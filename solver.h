#ifndef SOLVER_H
#define SOLVER_H

#include <sstream>
#include <stdint.h>

#include "solution.h"
#include "walk.h"
#include "graph.h"

using namespace std;

/**
  * The class Solver represents a general solver of a combinatorial problem under
  * any objective function of cordType=B (binary). To add a new walk or a
  * combinatorial problem the method run has to be updated.
  * A new walk has to inherit class Walk and a new combinatorial problem has to
  * inherit class Solution.
  */
class Solver{
public:
    /**
      * Constructs a solver object, initializing its value depending on the argument values.
      * \param ss stream of command line arguments
      * \param program program name
      */
    Solver(stringstream& ss, const char program[]);

    /**
      * Method runs a search algorithm with the specific walk to solve a specific problem.
      */
    void run();
private:
    void loadCommandLine(stringstream& ss, const char program[]);
    void help(const char program[]);
    void defaultValues();
    bool stoppingConditions(Solution &solution);
    void results(const Solution & init, const Solution & best, const Walk& walk) const;
    void printSettings(const Solution & init, const Walk& walk) const;

    string functionName;
    string walkName;
    //
    string instanceDef;
    //
    uint64_t cntProbeLmt;
    uint64_t cntRestartLmt;
    string coordInit;
    double runtimeLmt;
    uint32_t seed;
    unsigned int valueTarget;
    unsigned int walkLengthCoef;
    unsigned int walkLengthLmt;
    bool noRestart;
    bool writeInit;
    bool writeTrace;
    bool writeWalk;

    double start;
    double stop;
    uint64_t cntRestart;
};

#endif // SOLVER_H
