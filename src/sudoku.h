#ifndef SUDOKU_H
#define SUDOKU_H

class Sudoku {
 public:
	 Sudoku();
	 ~Sudoku();
	 const int get_field(const int x, const int y) const;
	 void set_field(const int x, const int y, const int value);

 private:
	 int fields[9][9];
};

#endif  // SUDOKU_H