#ifndef SOLUTION_H
#define SOLUTION_H

#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <stdint.h>
#include <cstdlib>

using namespace std;

/**
  * The class Solution represents a general solution of a combinatorial problem under
  * any objective function of cordType=B (binary).
  * New solutions (combinatorial problems) have to be inherited from this class and
  * implement at least the following methods:
  *     Solution(const unsigned int L);
  *     int evaluate();
  *     void random();
  *     string toString() const;
  *     void good();
  *     Solution& operator= (const string& str);
  *     void flip(const unsigned int i);
  *     static int getKnownTarget(const unsigned int L);
  *     string getType() const;
  *
  * Solution is defined with a coordinate (coord), a value and a key.
  *   coordinate is an array of integers.
  *   value is an integer value.
  *   key is an uin64_t value.
  */
class Solution {
public:
    /** Copy constructor */
    Solution(const Solution & sol){ L = sol.L; coord = new int[L]; *this = sol; }

    /** Destructor */
    virtual ~Solution() { delete [] coord; }

    /** The method represents objective function. It calculates, sets and returns solution value. */
    /** The method must increase the value of cntProbe by 1. */
    virtual int evaluate() { cntProbe++; return 0; }

    /** The method generates random solution. */
    virtual void random() { }

    /** The method converts solution to the string. */
    virtual string toString() const { return ""; }

    /** Checks whether the state of the solution is good */
    virtual void good() { }

    /** The method returns solution (combinatorial problem) type or solution (combinatorial problem) name. */
    virtual string getType() const {return "undefined"; }

    /** Replaces the contents of the solution according to the given string. */
    virtual Solution& operator= (const string& str);


    /** The method sets censored status. */
    inline virtual void setCensored(const bool censored=true) { this->censored = censored; }

    /** The method sets blocked status. */
    inline virtual void setBlocked(const bool blocked=true) { this->blocked = blocked; }

    /** The method sets solution value. */
    inline virtual void setValue(const int value) { this->value = value; }

    /** The method flips the i-th value in the coordinate (coord array) */
    virtual void flip(const unsigned int i) { if(i>=L){ cerr<<"Wring flipped index"<<endl; exit(1); } };

    /** The method checks for targetReached status */
    inline virtual int isTargetReached() const {
        if(value == valueTarget) return 1;
        else if(value < valueTarget) return 2;
        return 0;
    }

    /** The method returns censored status */
    inline virtual bool isCensored() const { return censored; }

    /** The method returns blocked status */
    inline virtual bool isBlocked() const { return blocked; }

    /** The method returns solution key */
    inline virtual uint64_t getKey() const { return key; }

    /** The method returns solution value */
    inline virtual int getValue() const { return value; }

    /** The method returns coordinate length */
    inline virtual unsigned int getL() const { return L; }

    /** The method returns dimension of the problem */
    inline virtual unsigned int getNDim() const { return L; }
    inline friend istream& operator>>(istream& in, Solution& seq) {
        string s; in>>s; seq = s; return in;
    }

    /**  The stream insertion is overloaded */
    inline friend ostream& operator<<(ostream& out, const Solution& seq) {
        out<<seq.toString(); return out;
    }

    /** The stream extraction is overloaded. */
    inline virtual Solution& operator= (const Solution& seq) {
        copy(seq.coord,seq.coord+L,coord); value = seq.value; key = seq.key;
        L = seq.L; censored = seq.censored; blocked = seq.blocked;
        return *this;
    }

    /** The method inicializes array of random numbers that are required for key calculation.*/
    static void init(const unsigned int MAX_L);

    /** The method returns the best known target values. */
    static int getKnownTarget(const unsigned int L) { return L; };

    /** The method sets solution target value. */
    static void setValueTarget(const int valueTarget) { Solution::valueTarget = valueTarget; }

    /** The method returns number of cntProbre. */
    static uint64_t getCntProbe() { return cntProbe; }

    /** The method returns MAX_L. */
    inline static unsigned int getMAX_L() { return MAX_L; }

    /** The method returns Hamming distance. */
    int distance(const Solution solution) const;

protected:
    Solution(const unsigned int L);
    Solution() { L=0; key=0; value=0; coord = NULL; blocked = censored = false;}

    int * coord;
    int value;
    uint64_t key;
    unsigned int L;
    bool censored;
    bool blocked;

    static unsigned int MAX_L;
    static const unsigned int MIN_L=1;
    static uint64_t* rkey;
    static int valueTarget;
    static uint64_t cntProbe;

    static uint64_t rand64(){ return (uint64_t(rand()) | (uint64_t(rand())<<31) | (uint64_t(rand())<<62)); }

};

#endif // SEQUENCE_H
