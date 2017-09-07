#ifndef LINE_SOLVER_H
#define LINE_SOLVER_H
#include "solver.h"

class LineSolver : public Solver {
 public:
    LineSolver();
    virtual ~LineSolver();

    virtual bool solve(Sudoku& s) override;  // throw std::out_of_range
    virtual bool solve_step(Sudoku& s) override;  // throw std::out_of_range

 private:
    typedef Sudoku::iterator_sudoku& (Sudoku::iterator_sudoku::*it_inc_callback)(void);
    bool solve_line(const Sudoku::iterator_sudoku& begin, it_inc_callback inc);
};

#endif  // LINE_SOLVER_H
