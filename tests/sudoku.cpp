#include "gtest/gtest.h"
#include "sudoku.h"

TEST(Sudoku, construct) {
    Sudoku s;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            EXPECT_EQ(s.get_field(i, j), 0);
        }
    }
}
