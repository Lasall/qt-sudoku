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

    int get_field(const int x, const int y);  // throws std::out_of_range
    void set_field(const int x, const int y, const int value);  // throws std::out_of_range


    class Field {
     public:
         Field();
         Field(const int value);
         Field& operator=(int& value);
         ~Field();

         operator int() const { return value; }

         int get_value() const { return value; }
         void set_value(const int value);
         bool get_processed() const { return processed; };

         void update_suggestions(std::vector<int> &suggestions);


     private:
         int value;
         std::set<int> suggestions;
         bool processed;
    };

    class Column{
     public:
         Column(Field* fields) : fields(fields) {}
         Field& operator[](const int column);  // throws std::out_of_range

     private:
         Field* fields;
    };

    Column operator[](const int row);  // throws std::out_of_range

    class iterator_row : std::iterator<std::bidirectional_iterator_tag, Field> {
     private:
        Field* row;

     public:
        iterator_row(Field* row) : row(row) {}
        iterator_row(const iterator_row& it) : row(it.row) {}
        iterator_row& operator=(const iterator_row& rhs) {row = rhs.row; return *this;}
        ~iterator_row() {row = 0;}

        iterator_row& operator++() {++row; return *this;}
        iterator_row operator++(int) {
            iterator_row tmp(*this);
            operator++();
            return tmp;
        }
        iterator_row& operator--() {--row; return *this;}
        iterator_row operator--(int) {
            iterator_row tmp(*this);
            operator--();
            return tmp;
        }

        bool operator==(const iterator_row& rhs) const {return row == rhs.row;}
        bool operator!=(const iterator_row& rhs) const {return row != rhs.row;}

        Field& operator*() {return *row;}
        Field* operator->() {return row;}

        friend void swap(iterator_row& lhs, iterator_row& rhs) {
            iterator_row tmp(lhs);
            lhs = std::move(rhs);
            rhs = std::move(tmp);
        }
    };

    iterator_row begin_row(const int row) {
        return iterator_row(&fields[row][0]);
    }
    iterator_row end_row(const int row) {
        return iterator_row(&fields[row+1][0]);
    }

    class iterator_column : std::iterator<std::bidirectional_iterator_tag, Field> {
     private:
        Field* column;

     public:
        iterator_column(Field* column) : column(column)  {}
        iterator_column(const iterator_column& it) : column(it.column) {}
        iterator_column& operator=(const iterator_column& rhs) {column = rhs.column; return *this;}
        ~iterator_column() {column = 0;}

        iterator_column& operator++() {column += 9; return *this;}
        iterator_column operator++(int) {
            iterator_column tmp(*this);
            operator++();
            return tmp;
        }
        iterator_column& operator--() {column -= 9; return *this;}
        iterator_column operator--(int) {
            iterator_column tmp(*this);
            operator--();
            return tmp;
        }

        bool operator==(const iterator_column& rhs) const {return column == rhs.column;}
        bool operator!=(const iterator_column& rhs) const {return column != rhs.column;}

        Field& operator*() {return *column;}
        Field* operator->() {return column;}

        friend void swap(iterator_column& lhs, iterator_column& rhs) {
            iterator_column tmp(lhs);
            lhs = std::move(rhs);
            rhs = std::move(tmp);
        }
    };

    iterator_column begin_column(const int column) {
        return iterator_column(&fields[0][column]);
    }
    iterator_column end_column(const int column) {
        return iterator_column(&fields[9][column]);
    }

    class iterator_square : std::iterator<std::bidirectional_iterator_tag, Field> {
     private:
        Field* square;
        int index;

     public:
        iterator_square(Field* square) : square(square), index(0) {}
        iterator_square(const iterator_square& it) : square(it.square), index(it.index) {}
        iterator_square& operator=(const iterator_square& rhs) {square = rhs.square; return *this;}
        ~iterator_square() {square = 0;}

        iterator_square& operator++() {
            if (index < 2) {
                ++square;
                ++index;
            } else {
                square += 7;
                index = 0;
            }
            return *this;
        }
        iterator_square operator++(int) {
            iterator_square tmp(*this);
            operator++();
            return tmp;
        }
        iterator_square& operator--() {
            if (index > 0) {
                --square;
                --index;
            } else {
                square -= 7;
                index = 2;
            }
            return *this;
        }
        iterator_square operator--(int) {
            iterator_square tmp(*this);
            operator--();
            return tmp;
        }

        bool operator==(const iterator_square& rhs) const {return square == rhs.square;}
        bool operator!=(const iterator_square& rhs) const {return square != rhs.square;}

        Field& operator*() {return *square;}
        Field* operator->() {return square;}

        friend void swap(iterator_square& lhs, iterator_square& rhs) {
            iterator_square tmp(lhs);
            lhs = std::move(rhs);
            rhs = std::move(tmp);
        }
    };

    iterator_square begin_square(const int square) {
        return iterator_square(&fields[square/3*3][square%3*3]);
    }
    iterator_square end_square(const int square) {
        return iterator_square(&fields[square/3*3 + 3][square%3*3]);
    }

 private:
    Field fields[9][9];
    static void validate_field_range(const int field);  // throws::std::out_of_range
};

#endif  // SUDOKU_H