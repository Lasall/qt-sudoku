#include "line_solver.h"

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
