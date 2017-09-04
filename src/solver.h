#ifndef SOLVER_H
#define SOLVER_H
#include "sudoku.h"

class Solver {
 public:
    Solver() {};
    virtual ~Solver() {};

    virtual bool solve(Sudoku& s) = 0;
};

#endif  // SOLVER_H
