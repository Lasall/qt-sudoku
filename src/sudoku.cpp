#include "sudoku.h"

Sudoku::Sudoku() {
}

Sudoku::~Sudoku() {
}

const int Sudoku::get_field(const int x, const int y) const {
	return fields[x, y];
}

void Sudoku::set_field(const int x, const int y, const int value) {
	fields[x, y] = value;
}