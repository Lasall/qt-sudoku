#ifndef SUDOKU_H
#define SUDOKU_H
#include <stdexcept>
#include <string>
#include <iterator>
#include <utility>
#include <vector>
#include <set>

class Sudoku {
 public:
    Sudoku();
    ~Sudoku();

    class Field {
     public:
         Field();
         Field(const int value);
         Field& operator=(int& value);
         ~Field();

         operator int() const { return value; }

         int get_value() const { return value; }
         void set_value(const int value);
         bool get_processed() const { return processed; }
         const std::set<int>& get_suggestions() const { return suggestions; }

         void update_suggestions(std::vector<int> &suggestions);


     private:
         int value;
         std::set<int> suggestions;
         bool processed;
    };

    const Field& get_field(const int x, const int y);  // throws std::out_of_range
    void set_field(const int x, const int y, const int value);  // throws std::out_of_range

    class Column{
     public:
         Column(Field* fields) : fields(fields) {}
         Field& operator[](const int column);  // throws std::out_of_range

     private:
         Field* fields;
    };

    Column operator[](const int row);  // throws std::out_of_range

    class iterator_sudoku : std::iterator<std::bidirectional_iterator_tag, Field> {
     private:
        Field* fields;
        int index_x;
        int index_y;

     public:
        iterator_sudoku(Field* fields, const int x, const int y) : fields(fields),
                                                                   index_x(x),
                                                                   index_y(y) {}
        iterator_sudoku(const iterator_sudoku& it) : fields(it.fields),
                                                     index_x(it.index_x),
                                                     index_y(it.index_y) {}
        iterator_sudoku& operator=(const iterator_sudoku& rhs) {
            fields = rhs.fields;
            index_x = rhs.index_x;
            index_y = rhs.index_y;
            return *this;
        }
        ~iterator_sudoku() {}

        iterator_sudoku& inc_row() {
            ++index_x;
            return *this;
        }
        iterator_sudoku& dec_row() {
            --index_x;
            return *this;
        }
        iterator_sudoku& inc_column() {
            ++index_y;
            return *this;
        }
        iterator_sudoku& dec_column() {
            --index_y;
            return *this;
        }
        iterator_sudoku& inc_square() {
            if (index_x%3 < 2) {
                ++index_x;
            } else {
                index_x -= 2;
                // set index out of range for is_end to detect end of square
                int y_square = index_y/3;
                if (y_square != ++index_y/3)
                    index_y = 9;
            }
            return *this;
        }
        iterator_sudoku& dec_square() {
            if (index_x%3 > 0) {
                --index_x;
            } else {
                index_x += 2;
                int y_square = index_y/3;
                if (y_square != --index_y/3)
                    index_y = -1;
            }
            return *this;
        }

        bool is_end() {
            return index_x < 0 || index_x > 8 || index_y < 0 || index_y > 8;
        }

        bool operator==(const iterator_sudoku& rhs) const {
            return fields == rhs.fields && index_x == rhs.index_x && index_y == rhs.index_y;
        }
        bool operator!=(const iterator_sudoku& rhs) const {
            return fields != rhs.fields || index_x != rhs.index_x || index_y != rhs.index_y;
        }

        Field& operator*() {return *(fields+9*index_y+index_x);}
        Field* operator->() {return fields+9*index_y+index_x;}

        friend void swap(iterator_sudoku& lhs, iterator_sudoku& rhs) {
            iterator_sudoku tmp(lhs);
            lhs = std::move(rhs);
            rhs = std::move(tmp);
        }
    };

    iterator_sudoku get_it_row(const int row) {
        return iterator_sudoku(&fields[0][0], 0, row);
    }
    iterator_sudoku get_it_column(const int column) {
        return iterator_sudoku(&fields[0][0], column, 0);
    }
    iterator_sudoku get_it_square(const int square) {
        return iterator_sudoku(&fields[0][0], square%3*3, square/3*3);
    }

    iterator_sudoku get_it(const int x, const int y) {
        return iterator_sudoku(&fields[0][0], y, x);
    }

 private:
    Field fields[9][9];
    static void validate_field_range(const int field);  // throws::std::out_of_range
};

Sudoku generateSudoku();

#endif  // SUDOKU_H