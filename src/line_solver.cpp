#include "line_solver.h"
#include <vector>
#include <algorithm>
#include <utility>
#include <stdexcept>
#include <string>

LineSolver::LineSolver() {
}

LineSolver::~LineSolver() {
}

bool LineSolver::solve(Sudoku& s) {
    bool found_orig = false;

    bool found;
    do {
        found = false;
        for (int i = 0; i < 9; ++i) {
            if (solve_line(s.get_it_row(i), &Sudoku::iterator_sudoku::inc_row))
                found = true;
        }
        for (int i = 0; i < 9; ++i) {
            if (solve_line(s.get_it_column(i), &Sudoku::iterator_sudoku::inc_column))
                found = true;
        }
        for (int i = 0; i < 9; ++i) {
            if (solve_line(s.get_it_square(i), &Sudoku::iterator_sudoku::inc_square))
                found = true;
        }
        if (found)
            found_orig = true;
    } while (found);

    return found_orig;
}

bool LineSolver::solve_step(Sudoku &s) {
    for (int i = 0; i < 9; ++i) {
        if (solve_line(s.get_it_row(i), &Sudoku::iterator_sudoku::inc_row))
            return true;
    }
    for (int i = 0; i < 9; ++i) {
        if (solve_line(s.get_it_column(i), &Sudoku::iterator_sudoku::inc_column))
            return true;
    }
    for (int i = 0; i < 9; ++i) {
        if (solve_line(s.get_it_square(i), &Sudoku::iterator_sudoku::inc_square))
            return true;
    }
    return false;
}

bool LineSolver::solve_line(const Sudoku::iterator_sudoku& begin,
                            it_inc_callback inc) {
    /*
     * Significantly more efficient than vector and set.
     *
     * Store index to last valid array member. Already found members
     * are swapped further to the front.
     */
    int numbers[9] {1,2,3,4,5,6,7,8,9};
    int last_index = 8;
    Sudoku::Field* empty_it = 0;
    for (auto it = begin; !it.is_end(); (it.*inc)()) {
        if (*it == 0) {
            if (empty_it == 0) {
                empty_it = &*it;
            } else {
                return false;
            }
        } else {
            /*
             * Use goto to jump over exception in case of success (likely).
             * Gaining some speed with dropping conditional request  in effect.
             */
            for (int i = 0; i <= last_index; ++i) {
                if (numbers[i] == *it) {
                    numbers[i] = numbers[last_index--];
                    goto found;
                }
            }
            throw std::out_of_range("invalid Sudoku value (duplicate?) : " + std::to_string(*it));
        }
        found: {}
    }
    if (empty_it != 0) {
        // *empty_it = numbers.front();
        *empty_it = numbers[0];
        return true;
    }
    return false;
}
