#include "line_solver.h"

LineSolver::LineSolver() {
}

LineSolver::~LineSolver() {
}

bool LineSolver::solve(Sudoku& s) {
    bool found = false;

    for (int i = 0; i < 9; ++i) {
        if (solve_line(s.begin_row(i), s.end_row(i)))
            found = true;
    }
    for (int i = 0; i < 9; ++i) {
        if (solve_line(s.begin_column(i), s.end_column(i)))
            found = true;
    }
    for (int i = 0; i < 9; ++i) {
        if (solve_line(s.begin_square(i), s.end_square(i)))
            found = true;
    }

    return found;
}
