#ifndef LINE_SOLVER_H
#define LINE_SOLVER_H
#include "solver.h"
#include <vector>
#include <algorithm>
#include <utility>
#include <stdexcept>
#include <string>

class LineSolver : public Solver {
 public:
    LineSolver();
    virtual ~LineSolver();

    virtual bool solve(Sudoku& s) override;  // throw std::out_of_range

 private:
    typedef Sudoku::iterator_sudoku& (Sudoku::iterator_sudoku::*iterator_inc_callback)(void);
    bool solve_line(const Sudoku::iterator_sudoku& begin, iterator_inc_callback inc) {
        bool found = false;
        std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        Sudoku::Field* empty_it = 0;
        for (auto it = begin; !it.is_end(); (it.*inc)()) {
            if (*it == 0) {
                if (empty_it == 0) {
                    empty_it = &*it;
                } else {
                    empty_it = 0;
                    break;
                }
            } else {
                auto nit = std::find(numbers.begin(), numbers.end(), *it);
                if (nit != numbers.end()) {
                    std::swap(*nit, numbers.back());
                    numbers.pop_back();
                } else {
                    throw std::out_of_range("invalid Sudoku value (duplicate?) : " + std::to_string(*it));
                }
            }
        }
        if (empty_it != 0 && numbers.size() == 1) {
            *empty_it = numbers.front();
            found = true;
        }
        return found;
    }
};

#endif  // LINE_SOLVER_H
