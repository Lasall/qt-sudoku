#include "gtest/gtest.h"
#include "sudoku.h"
#include <stdexcept>

TEST(Sudoku, construct) {
    Sudoku s;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            EXPECT_EQ(s.get_field(i, j), 0);
        }
    }
}

TEST(Sudoku, getter) {
    Sudoku s;
    s[1][5] = 5;
    s[8][8] = 1;
    EXPECT_EQ(s.get_field(5, 1), 5);
    EXPECT_EQ(s.get_field(8, 8), 1);
}

TEST(Sudoku, getter_exc) {
    Sudoku s;
    EXPECT_THROW(s.get_field(-1, 8), std::out_of_range);
    EXPECT_THROW(s.get_field(1, -8), std::out_of_range);
    EXPECT_THROW(s.get_field(9, 0), std::out_of_range);
    EXPECT_THROW(s.get_field(0, 9), std::out_of_range);
}

TEST(Sudoku, setter) {
    Sudoku s;
    s.set_field(5, 1, 5);
    EXPECT_EQ(s.get_field(5, 1), 5);
    EXPECT_EQ(s[1][5], 5);
    s.set_field(8, 8, 1);
    EXPECT_EQ(s.get_field(8, 8), 1);
    EXPECT_EQ(s[8][8], 1);
}

TEST(Sudoku, setter_exc) {
    Sudoku s;
    EXPECT_THROW(s.set_field(-1, 8, 1), std::out_of_range);
    EXPECT_THROW(s.set_field(1, -8, 1), std::out_of_range);
    EXPECT_THROW(s.set_field(9, 0, 1), std::out_of_range);
    EXPECT_THROW(s.set_field(0, 9, 1), std::out_of_range);
    EXPECT_THROW(s.set_field(0, 8, -1), std::out_of_range);
    EXPECT_THROW(s.set_field(0, 8, 9), std::out_of_range);
}

TEST(Sudoku, Column_arr_operator) {
    int arr[] = {0, 1, 2, 2, 4, 5, 8, -1, 9};
    Sudoku::Column c(arr);
    for (int i = 0; i < 9; ++i) {
        EXPECT_EQ(c[i], arr[i]);
    }
}

TEST(Sudoku, Column_arr_operator_exc) {
    int arr[] = {0, 1, 2, 2, 4, 5, 8, -1, 9};
    Sudoku::Column c(arr);
    EXPECT_THROW(c[9], std::out_of_range);
    EXPECT_THROW(c[-1], std::out_of_range);
}

TEST(Sudoku, arr_operator) {
    Sudoku s;
    int arr[] = {6, 0, 2, 2, 4, 5, 8, 0, 6};
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            s.set_field(j, i, arr[j]);
        }
    }

    for (int i = 0; i < 9; ++i) {
        Sudoku::Column c = s[i];
        for (int j = 0; j < 9; ++j) {
            EXPECT_EQ(c[j], arr[j]);
        }
    }
}

TEST(Sudoku, arr_operator_exc) {
    Sudoku s;
    EXPECT_THROW(s[9], std::out_of_range);
    EXPECT_THROW(s[-1], std::out_of_range);
}
