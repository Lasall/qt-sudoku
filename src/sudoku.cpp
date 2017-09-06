#include "sudoku.h"
#include <algorithm>

Sudoku::Sudoku() {
}

Sudoku::~Sudoku() {
}

Sudoku::Field::Field() : value(0),
                         suggestions(std::set<int>()),
                         processed(false) {
}

Sudoku::Field::Field(const int value) : value(value),
                                        suggestions(std::set<int>()),
                                        processed(false) {
}

Sudoku::Field& Sudoku::Field::operator=(int& value) {
    set_value(value);
    return *this;
}

Sudoku::Field::~Field() {
}

inline void Sudoku::Field::set_value(const int value) {
    this->value = value;
    suggestions = std::set<int>();
    processed = false;
}

void Sudoku::Field::update_suggestions(std::vector<int> &suggestions) {
    if (!processed) {
        std::for_each(suggestions.begin(),
                      suggestions.end(),
                      [this](int &v){this->suggestions.insert(v);});
        processed = true;
    } else {
        std::set<int> intersect;
        std::set_intersection(this->suggestions.begin(), this->suggestions.end(),
                              suggestions.begin(), suggestions.end(),
                              std::inserter(intersect, intersect.begin()));
        this->suggestions = intersect;
    }
}

const Sudoku::Field& Sudoku::get_field(const int x, const int y) {
    validate_field_range(x);
    validate_field_range(y);
    return fields[y][x];
}

void Sudoku::set_field(const int x, const int y, const int value) {
    validate_field_range(x);
    validate_field_range(y);
    validate_field_range(value-1);
    fields[y][x].set_value(value);
}

Sudoku::Column Sudoku::operator[](const int row) {
    validate_field_range(row);
    return Column(fields[row]);
}

Sudoku::Field& Sudoku::Column::operator[](const int column) {
    validate_field_range(column);
    return fields[column];
}

void Sudoku::validate_field_range(const int field) {
    if (field < 0 || field > 8)
        throw std::out_of_range(std::to_string(field) + ((field < 0) ? " < 0" : " > 8"));
}

Sudoku generateSudoku() {
    int field[9][9] = { {5,3,4,6,7,8,9,1,2},
                        {6,7,2,1,9,5,3,4,8},
                        {1,9,8,3,4,2,5,6,7},
                        {8,5,9,7,6,1,4,2,3},
                        {4,2,6,8,5,3,7,9,1},
                        {7,1,3,9,2,4,8,5,6},
                        {9,6,1,5,3,7,2,8,4},
                        {2,8,7,4,1,9,6,3,5},
                        {3,4,5,2,8,6,1,7,9} };
    Sudoku sud;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            sud.set_field(i, j, field[i][j]);
        }
    }
    return sud;
}