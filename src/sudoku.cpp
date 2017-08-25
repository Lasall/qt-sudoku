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

int Sudoku::get_field(const int x, const int y) {
    validate_field_range(x);
    validate_field_range(y);
    return fields[x][y];
}

void Sudoku::set_field(const int x, const int y, const int value) {
    validate_field_range(x);
    validate_field_range(y);
    fields[x][y] = value;
}

Sudoku::Column Sudoku::operator[](const int row) {
    validate_field_range(row);
    return Column(fields[row]);
}

int& Sudoku::Column::operator[](int column) {
    validate_field_range(column);
    return fields[column];
}

void Sudoku::validate_field_range(const int field) {
    if (field < 0 || field > 8)
        throw std::out_of_range(std::to_string(field) + " != [0-8]");
}