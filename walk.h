#ifndef WALK_H
#define WALK_H

#include "solution.h"

/**
  * The class Walk represents a general walk algorithm of a combinatorial problem under
  * any objective function of cordType=B (binary).
  * New walks have to be inherited from this class and implement at least the
  * following methods:
  *   void run(Solution & init, Solution &best);
  *   string getType();
  * First method makes the walk and second method returns the walk type or the walk name.
  */
class Walk{
public:
  /** Default constructor */
   Walk() {
       step = walkLengthLmt = runtimeLmt = cntProbeLmt = cntRestart = 0;
       valueTarget = 0;
       start = 0;
       writeWalk = false;
       writeTrace = false;
   }

   /** Destructor */
   virtual ~Walk() {}
   /**
     * The method makes the walk.
     * \param init Initial solution.
     * \param best Best solution. It is updated only when the new best solution is found.
     */
   virtual void run(Solution & init, Solution &best);

   /** The method sets walkLengthLmt. */
   virtual inline void setWalkLengthLmt(const unsigned int walkLength) { this->walkLengthLmt = walkLength; }

   /** The method sets runTimeLmt. */
   virtual inline void setRuntimeLmt(const unsigned int runtimeLmt) { this->runtimeLmt = runtimeLmt; }

   /** The method sets cntProbeLmt. */
   virtual inline void setCntProbeLmt(const unsigned int cntProbeLmt) { this->cntProbeLmt = cntProbeLmt; }

   /** The method sets start time. */
   virtual inline void setStart(const double start) { this->start = start; }

   /** The method sets valueTarget. */
   virtual inline void setValueTarget(const int valueTarget) { this->valueTarget = valueTarget; }

   /** The method sets cntRestart. */
   virtual inline void setCntRestart(const unsigned int cntRestart) { this->cntRestart = cntRestart; }

   /** The method sets writeWalk. */
   virtual inline void setWriteWalk(const bool writeWalk) { this->writeWalk = writeWalk; }

   /** The method sets writeTrace. */
   virtual inline void setWriteTrace(const bool writeTrace) { this->writeTrace = writeTrace; }

   /** The method sets seed. */
   virtual inline void setSeed(const uint32_t seed) {this->seed = seed; }

   /** The method sets walkLength. */
   virtual inline void setWalkLength(unsigned int walkLength) { this->walkLength = walkLength;}

   /** The method returns WalkLength. */
   virtual inline unsigned int getWalkLength() const { return walkLength; }

   /** The method writes tabulated walk data to the file */
   virtual void writeWalkLine(const Solution &solution, const Solution & old,
                              const unsigned int neighbSize) const;

   /** The method writes traces to the stdout */
   virtual void writeTraceLine(const Solution &solution, const Solution & old,
                              const unsigned int neighbSize) const;

   /** The method returns walk type or walk name */
   virtual string getType() const { return "walk"; }
protected:

   virtual bool stoppingConditions(Solution &solution);

   unsigned int walkLengthLmt;
   unsigned int walkLength;
   unsigned int step;
   unsigned int runtimeLmt;
   unsigned int cntProbeLmt;
   int valueTarget;
   unsigned int cntRestart;
   double start;
   bool writeWalk;
   bool writeTrace;
   uint32_t seed;

};

#endif // WALK_H
