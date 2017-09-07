#include "gtest/gtest.h"
#include "line_solver.h"
#include <stdexcept>

extern Sudoku init_sudoku(const int (&arr)[9][9]);
const int arr[9][9] = {{0,0,0,0,0,0,0,0,0},
                       {6,0,2,1,9,5,3,4,8},
                       {1,9,0,3,4,2,5,6,7},
                       {0,5,9,0,6,1,4,2,3},
                       {4,2,6,8,0,3,7,0,1},
                       {7,1,3,9,2,0,8,5,6},
                       {0,6,1,5,3,7,0,8,4},
                       {2,8,7,4,0,9,6,0,5},
                       {3,4,5,2,8,6,1,7,0}};
const int arr_solved[9][9] = {{5,3,4,6,7,8,9,1,2},
                              {6,7,2,1,9,5,3,4,8},
                              {1,9,8,3,4,2,5,6,7},
                              {8,5,9,7,6,1,4,2,3},
                              {4,2,6,8,5,3,7,9,1},
                              {7,1,3,9,2,4,8,5,6},
                              {9,6,1,5,3,7,2,8,4},
                              {2,8,7,4,1,9,6,3,5},
                              {3,4,5,2,8,6,1,7,9}};
const int arr_faulty[9][9] = {{0,0,0,0,0,0,0,0,0},
                              {6,0,2,1,9,5,3,4,8},
                              {1,9,9,3,4,2,5,6,7},
                              {0,5,9,0,6,1,4,2,3},
                              {4,2,6,8,0,3,7,0,1},
                              {7,1,3,9,2,0,8,5,6},
                              {0,6,1,5,3,7,0,8,4},
                              {2,8,7,4,0,9,6,0,5},
                              {3,4,5,2,8,6,1,7,0}};

TEST(LineSolver, solve) {
    Sudoku s = init_sudoku(arr);
    LineSolver ls;
    ls.solve(s);
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            ASSERT_EQ(s[i][j], arr_solved[i][j]);
        }
    }
}

TEST(LineSolver, solve_step) {
    Sudoku s = init_sudoku(arr);
    LineSolver ls;

    EXPECT_EQ(s[1][1], 0);
    ls.solve_step(s);
    ASSERT_EQ(s[1][1], arr_solved[1][1]);

    EXPECT_EQ(s[2][2], 0);
    ls.solve_step(s);
    ASSERT_EQ(s[2][2], arr_solved[2][2]);

    EXPECT_EQ(s[5][5], 0);
    ls.solve_step(s);
    ASSERT_EQ(s[5][5], arr_solved[5][5]);

    EXPECT_EQ(s[8][8], 0);
    ls.solve_step(s);
    ASSERT_EQ(s[8][8], arr_solved[8][8]);

    EXPECT_EQ(s[0][1], 0);
    ls.solve_step(s);
    ASSERT_EQ(s[0][1], arr_solved[0][1]);

    EXPECT_EQ(s[0][2], 0);
    ls.solve_step(s);
    ASSERT_EQ(s[0][2], arr_solved[0][2]);

    EXPECT_EQ(s[0][5], 0);
    ls.solve_step(s);
    ASSERT_EQ(s[0][5], arr_solved[0][5]);

    EXPECT_EQ(s[0][8], 0);
    ls.solve_step(s);
    ASSERT_EQ(s[0][8], arr_solved[0][8]);

    EXPECT_EQ(s[0][0], 0);
    ls.solve_step(s);
    ASSERT_EQ(s[0][0], arr_solved[0][0]);

    for (int i = 0; i < 12; ++i) {
        ls.solve_step(s);
    }
    EXPECT_FALSE(ls.solve_step(s));

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            ASSERT_EQ(s[i][j], arr_solved[i][j]);
        }
    }
}

TEST(LineSolver, solve_exc) {
    Sudoku s = init_sudoku(arr_faulty);
    LineSolver ls;
    EXPECT_THROW(ls.solve(s), std::out_of_range);
}
