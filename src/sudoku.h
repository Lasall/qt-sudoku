#ifndef SUDOKU_H
#define SUDOKU_H
#include <stdexcept>
#include <string>

class Sudoku {
 public:
    Sudoku();
    ~Sudoku();

    int get_field(const int x, const int y);  // throws std::out_of_range
    void set_field(const int x, const int y, const int value);  // throws std::out_of_range

    class Column {
     public:
         Column(int fields[]) : fields(fields) {}
         int& operator[](int column);  // throws std::out_of_range

     private:
         int* fields;
    };

    Column operator[](const int row);  // throws std::out_of_range

 private:
    int fields[9][9];
    static void validate_field_range(const int field);  // throws::std::out_of_range
};

#endif  // SUDOKU_H