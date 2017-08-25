#include "sudoku.h"

Sudoku::Sudoku() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            fields[i][j] = 0;
        }
    }
}

Sudoku::~Sudoku() {
}

int Sudoku::get_field(const int x, const int y) const {
    return fields[x][y];
}

void Sudoku::set_field(const int x, const int y, const int value) {
    fields[x][y] = value;
}

const int* Sudoku::operator[](const int row) const {
    return fields[row];
}

int* Sudoku::operator[](const int row) {
    return fields[row];
}