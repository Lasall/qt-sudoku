#include "gtest/gtest.h"
#include "sudoku.h"
#include <stdexcept>

Sudoku init_sudoku(const int (&arr)[9][9]);
const int arr[9][9] = {{5,3,4,6,7,8,9,1,2},
                       {6,7,2,1,9,5,3,4,8},
                       {1,9,8,3,4,2,5,6,7},
                       {8,5,9,7,6,1,4,2,3},
                       {4,2,6,8,5,3,7,9,1},
                       {7,1,3,9,2,4,8,5,6},
                       {9,6,1,5,3,7,2,8,4},
                       {2,8,7,4,1,9,6,3,5},
                       {3,4,5,2,8,6,1,7,9}};
const int arr_square[9][9] = {{5,3,4,6,7,2,1,9,8},
                              {6,7,8,1,9,5,3,4,2},
                              {9,1,2,3,4,8,5,6,7},
                              {8,5,9,4,2,6,7,1,3},
                              {7,6,1,8,5,3,9,2,4},
                              {4,2,3,7,9,1,8,5,6},
                              {9,6,1,2,8,7,3,4,5},
                              {5,3,7,4,1,9,2,8,6},
                              {2,8,4,6,3,5,1,7,9}};


TEST(Sudoku, construct) {
    Sudoku s;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            ASSERT_EQ(s.get_field(i, j), 0);
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
    s.set_field(8, 8, 9);
    EXPECT_EQ(s.get_field(8, 8), 9);
    EXPECT_EQ(s[8][8], 9);
}

TEST(Sudoku, setter_exc) {
    Sudoku s;
    EXPECT_THROW(s.set_field(-1, 8, 1), std::out_of_range);
    EXPECT_THROW(s.set_field(1, -8, 1), std::out_of_range);
    EXPECT_THROW(s.set_field(9, 0, 1), std::out_of_range);
    EXPECT_THROW(s.set_field(0, 9, 1), std::out_of_range);
    EXPECT_THROW(s.set_field(0, 8, -1), std::out_of_range);
    EXPECT_THROW(s.set_field(0, 8, 10), std::out_of_range);
}

TEST(Sudoku, Field_construct) {
    Sudoku::Field f;
    EXPECT_EQ(f.get_value(), 0);
    EXPECT_EQ(f, 0);
    EXPECT_FALSE(f.get_processed());
    EXPECT_EQ(f.get_suggestions().size(), 0);

    Sudoku::Field f2(1);
    EXPECT_EQ(f2.get_value(), 1);
    EXPECT_EQ(f2, 1);
    EXPECT_FALSE(f2.get_processed());
    EXPECT_EQ(f2.get_suggestions().size(), 0);
}

TEST(Sudoku, Field_assign) {
    Sudoku::Field f;
    f = 1;
    EXPECT_EQ(f.get_value(), 1);
    EXPECT_EQ(f, 1);
    EXPECT_FALSE(f.get_processed());
    EXPECT_EQ(f.get_suggestions().size(), 0);

    f.set_value(2);
    EXPECT_EQ(f.get_value(), 2);
    EXPECT_EQ(f, 2);
    EXPECT_FALSE(f.get_processed());
    EXPECT_EQ(f.get_suggestions().size(), 0);
}

TEST(Sudoku, Field_upd_suggs) {
    Sudoku::Field f;
    std::vector<int> v {1, 2, 3, 4};
    std::set<int> vs {1, 2, 3, 4};
    std::vector<int> v2 {2, 3, 9};
    std::set<int> vs2 {2, 3};

    f.update_suggestions(v);
    EXPECT_EQ(f.get_value(), 0);
    EXPECT_EQ(f, 0);
    EXPECT_TRUE(f.get_processed());
    EXPECT_EQ(f.get_suggestions(), vs);

    f.update_suggestions(v2);
    EXPECT_EQ(f.get_value(), 0);
    EXPECT_EQ(f, 0);
    EXPECT_TRUE(f.get_processed());
    EXPECT_EQ(f.get_suggestions(), vs2);

    f.set_value(1);
    EXPECT_EQ(f.get_value(), 1);
    EXPECT_EQ(f, 1);
    EXPECT_FALSE(f.get_processed());
    EXPECT_EQ(f.get_suggestions().size(), 0);
}

TEST(Sudoku, Column_arr_operator) {
    Sudoku::Field arr[] = {Sudoku::Field(0), Sudoku::Field(1), Sudoku::Field(2),
                           Sudoku::Field(2), Sudoku::Field(4), Sudoku::Field(5),
                           Sudoku::Field(8), Sudoku::Field(-1), Sudoku::Field(9)};
    Sudoku::Column c(arr);
    for (int i = 0; i < 9; ++i) {
        ASSERT_EQ(c[i], arr[i]);
    }
}

TEST(Sudoku, Column_arr_operator_exc) {
    Sudoku::Field arr[] = {Sudoku::Field(0), Sudoku::Field(1), Sudoku::Field(2),
                           Sudoku::Field(2), Sudoku::Field(4), Sudoku::Field(5),
                           Sudoku::Field(8), Sudoku::Field(-1), Sudoku::Field(9)};
    Sudoku::Column c(arr);
    EXPECT_THROW(c[9], std::out_of_range);
    EXPECT_THROW(c[-1], std::out_of_range);
}

TEST(Sudoku, arr_operator) {
    Sudoku s;
    int arr[] = {6, 1, 2, 2, 4, 5, 8, 9, 6};
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            s.set_field(j, i, arr[j]);
        }
    }

    for (int i = 0; i < 9; ++i) {
        Sudoku::Column c = s[i];
        for (int j = 0; j < 9; ++j) {
            ASSERT_EQ(c[j], arr[j]);
        }
    }
}

TEST(Sudoku, arr_operator_exc) {
    Sudoku s;
    EXPECT_THROW(s[9], std::out_of_range);
    EXPECT_THROW(s[-1], std::out_of_range);
}

TEST(Sudoku, validate_string) {
    Sudoku s;
    try {
        s.set_field(9, 0, 0);
        FAIL();
    } catch (std::out_of_range &e) {
        EXPECT_STREQ(e.what(), "9 > 8");
    }
    try {
        s.set_field(-1, 0, 0);
        FAIL();
    } catch (std::out_of_range &e) {
        EXPECT_STREQ(e.what(), "-1 < 0");
    }
}

// iterator_row
TEST(Sudoku, iterator_row_inc) {
    Sudoku s = init_sudoku(arr);

    // prefix
    for (int i = 0; i < 9; ++i) {
        int j = 0;
        for (auto it = s.begin_row(i); it != s.end_row(i); ++it, ++j) {
            ASSERT_EQ(*it, arr[i][j]);
        }
    }

    // suffix
    for (int i = 0; i < 9; ++i) {
        int j = 0;
        for (auto it = s.begin_row(i); it != s.end_row(i); it++, ++j) {
            ASSERT_EQ(*it, arr[i][j]);
        }
    }
}

TEST(Sudoku, iterator_row_dec) {
    Sudoku s = init_sudoku(arr);

    // prefix
    for (int i = 8; i > -1; --i) {
        int j = 8;
        for (auto it = --(s.end_row(i)); it != --(s.begin_row(i)); --it, --j) {
            ASSERT_EQ(*it, arr[i][j]);
        }
    }

    // suffix
    for (int i = 8; i > -1; --i) {
        int j = 8;
        for (auto it = --(s.end_row(i)); it != --(s.begin_row(i)); it--, --j) {
            ASSERT_EQ(*it, arr[i][j]);
        }
    }
}

TEST(Sudoku, iterator_row_copy) {
    Sudoku s = init_sudoku(arr);

    Sudoku::iterator_row it = s.begin_row(0);
    Sudoku::iterator_row it2(it);
    EXPECT_TRUE(it == it2);
    EXPECT_FALSE(it != it2);

    for (int i = 0; i < 9; ++i) {
        int j = 0;
        for (auto it = s.begin_row(i); it != s.end_row(i); ++it, ++j) {
            ASSERT_EQ(*it, arr[i][j]);
        }
    }
}

TEST(Sudoku, iterator_row_assign) {
    Sudoku s = init_sudoku(arr);

    Sudoku::iterator_row it = s.begin_row(0);
    Sudoku::iterator_row it2 = it;
    EXPECT_TRUE(it == it2);
    EXPECT_FALSE(it != it2);

    for (int i = 0; i < 9; ++i) {
        int j = 0;
        for (auto it = s.begin_row(i); it != s.end_row(i); ++it, ++j) {
            ASSERT_EQ(*it, arr[i][j]);
        }
    }
}

TEST(Sudoku, iterator_row_oparrow) {
    Sudoku s = init_sudoku(arr);

    Sudoku::iterator_row it = s.begin_row(0);
    EXPECT_EQ(*(it.operator->()), arr[0][0]);
}

TEST(Sudoku, iterator_row_swap) {
    Sudoku s = init_sudoku(arr);

    Sudoku::iterator_row it = s.begin_row(0);
    Sudoku::iterator_row it2 = ++(s.begin_row(0));

    swap(it, it2);
    int j = 0;
    for (auto it = s.begin_row(0); it != s.end_row(0); ++it, ++j) {
        ASSERT_EQ(*it, arr[0][j]);
    }
    j = 0;
    for (auto it = s.begin_row(1); it != s.end_row(1); ++it, ++j) {
        ASSERT_EQ(*it, arr[1][j]);
    }
}

// iterator_column
TEST(Sudoku, iterator_column_inc) {
    Sudoku s = init_sudoku(arr);

    // prefix
    for (int i = 0; i < 9; ++i) {
        int j = 0;
        for (auto it = s.begin_column(i); it != s.end_column(i); ++it, ++j) {
            ASSERT_EQ(*it, arr[j][i]);
        }
    }

    // suffix
    for (int i = 0; i < 9; ++i) {
        int j = 0;
        for (auto it = s.begin_column(i); it != s.end_column(i); it++, ++j) {
            ASSERT_EQ(*it, arr[j][i]);
        }
    }
}

TEST(Sudoku, iterator_column_dec) {
    Sudoku s = init_sudoku(arr);

    // prefix
    for (int i = 8; i > -1; --i) {
        int j = 8;
        for (auto it = --(s.end_column(i)); it != --(s.begin_column(i)); --it, --j) {
            ASSERT_EQ(*it, arr[j][i]);
        }
    }

    // suffix
    for (int i = 8; i > -1; --i) {
        int j = 8;
        for (auto it = --(s.end_column(i)); it != --(s.begin_column(i)); it--, --j) {
            ASSERT_EQ(*it, arr[j][i]);
        }
    }
}

TEST(Sudoku, iterator_column_copy) {
    Sudoku s = init_sudoku(arr);

    Sudoku::iterator_column it = s.begin_column(0);
    Sudoku::iterator_column it2(it);
    EXPECT_TRUE(it == it2);
    EXPECT_FALSE(it != it2);

    for (int i = 0; i < 9; ++i) {
        int j = 0;
        for (auto it = s.begin_column(i); it != s.end_column(i); ++it, ++j) {
            ASSERT_EQ(*it, arr[j][i]);
        }
    }
}

TEST(Sudoku, iterator_column_assign) {
    Sudoku s = init_sudoku(arr);

    Sudoku::iterator_column it = s.begin_column(0);
    Sudoku::iterator_column it2 = it;
    EXPECT_TRUE(it == it2);
    EXPECT_FALSE(it != it2);

    for (int i = 0; i < 9; ++i) {
        int j = 0;
        for (auto it = s.begin_column(i); it != s.end_column(i); ++it, ++j) {
            ASSERT_EQ(*it, arr[j][i]);
        }
    }
}

TEST(Sudoku, iterator_column_oparrow) {
    Sudoku s = init_sudoku(arr);

    Sudoku::iterator_column it = s.begin_column(0);
    EXPECT_EQ(*(it.operator->()), arr[0][0]);
}

TEST(Sudoku, iterator_column_swap) {
    Sudoku s = init_sudoku(arr);

    Sudoku::iterator_column it = s.begin_column(0);
    Sudoku::iterator_column it2 = ++(s.begin_column(0));

    swap(it, it2);
    int j = 0;
    for (auto it = s.begin_column(0); it != s.end_column(0); ++it, ++j) {
        ASSERT_EQ(*it, arr[j][0]);
    }
    j = 0;
    for (auto it = s.begin_column(1); it != s.end_column(1); ++it, ++j) {
        ASSERT_EQ(*it, arr[j][1]);
    }
}

// iterator_square
TEST(Sudoku, iterator_square_inc) {
    Sudoku s = init_sudoku(arr);

    // prefix
    for (int i = 0; i < 9; ++i) {
        int j = 0;
        for (auto it = s.begin_square(i); it != s.end_square(i); ++it, ++j) {
            ASSERT_EQ(*it, arr_square[i][j]);
        }
    }

    // suffix
    for (int i = 0; i < 9; ++i) {
        int j = 0;
        for (auto it = s.begin_square(i); it != s.end_square(i); it++, ++j) {
            ASSERT_EQ(*it, arr_square[i][j]);
        }
    }
}

TEST(Sudoku, iterator_square_dec) {
    Sudoku s = init_sudoku(arr);

    // prefix
    for (int i = 8; i > -1; --i) {
        int j = 8;
        for (auto it = --(s.end_square(i)); it != --(s.begin_square(i)); --it, --j) {
            ASSERT_EQ(*it, arr_square[i][j]);
        }
    }

    // suffix
    for (int i = 8; i > -1; --i) {
        int j = 8;
        for (auto it = --(s.end_square(i)); it != --(s.begin_square(i)); it--, --j) {
            ASSERT_EQ(*it, arr_square[i][j]);
        }
    }
}

TEST(Sudoku, iterator_square_copy) {
    Sudoku s = init_sudoku(arr);

    Sudoku::iterator_square it = s.begin_square(0);
    Sudoku::iterator_square it2(it);
    EXPECT_TRUE(it == it2);
    EXPECT_FALSE(it != it2);

    for (int i = 0; i < 9; ++i) {
        int j = 0;
        for (auto it = s.begin_square(i); it != s.end_square(i); ++it, ++j) {
            ASSERT_EQ(*it, arr_square[i][j]);
        }
    }
}

TEST(Sudoku, iterator_square_assign) {
    Sudoku s = init_sudoku(arr);

    Sudoku::iterator_square it = s.begin_square(0);
    Sudoku::iterator_square it2 = it;
    EXPECT_TRUE(it == it2);
    EXPECT_FALSE(it != it2);

    for (int i = 0; i < 9; ++i) {
        int j = 0;
        for (auto it = s.begin_square(i); it != s.end_square(i); ++it, ++j) {
            ASSERT_EQ(*it, arr_square[i][j]);
        }
    }
}

TEST(Sudoku, iterator_square_oparrow) {
    Sudoku s = init_sudoku(arr);

    Sudoku::iterator_square it = s.begin_square(0);
    EXPECT_EQ(*(it.operator->()), arr_square[0][0]);
}

TEST(Sudoku, iterator_square_swap) {
    Sudoku s = init_sudoku(arr);

    Sudoku::iterator_square it = s.begin_square(0);
    Sudoku::iterator_square it2 = ++(s.begin_square(0));

    swap(it, it2);
    int j = 0;
    for (auto it = s.begin_square(0); it != s.end_square(0); ++it, ++j) {
        ASSERT_EQ(*it, arr_square[0][j]);
    }
    j = 0;
    for (auto it = s.begin_square(1); it != s.end_square(1); ++it, ++j) {
        ASSERT_EQ(*it, arr_square[1][j]);
    }
}

// iterator sudoku
TEST(Sudoku, iterator_sudoku_copy) {
    Sudoku s = init_sudoku(arr);

    Sudoku::iterator_sudoku it = s.get_it(0, 0);
    Sudoku::iterator_sudoku it2(it);
    EXPECT_TRUE(it == it2);
    EXPECT_FALSE(it != it2);

    it.inc_row();
    EXPECT_FALSE(it == it2);
    EXPECT_TRUE(it != it2);

    it2.inc_row();
    EXPECT_TRUE(it == it2);
    EXPECT_FALSE(it != it2);

    EXPECT_EQ(*it, arr[0][1]);
    EXPECT_EQ(*it2, arr[0][1]);

    *it = 0;
    EXPECT_EQ(*it, 0);
    EXPECT_EQ(*it2, 0);
}

TEST(Sudoku, iterator_sudoku_assign) {
    Sudoku s = init_sudoku(arr);

    Sudoku::iterator_sudoku it = s.get_it(0, 0);
    Sudoku::iterator_sudoku it2 = it;
    EXPECT_TRUE(it == it2);
    EXPECT_FALSE(it != it2);

    it.inc_row();
    EXPECT_FALSE(it == it2);
    EXPECT_TRUE(it != it2);

    it2.inc_row();
    EXPECT_TRUE(it == it2);
    EXPECT_FALSE(it != it2);

    EXPECT_EQ(*it, arr[0][1]);
    EXPECT_EQ(*it2, arr[0][1]);

    *it = 0;
    EXPECT_EQ(*it, 0);
    EXPECT_EQ(*it2, 0);
}

TEST(Sudoku, iterator_sudoku_oparrow) {
    Sudoku s = init_sudoku(arr);

    Sudoku::iterator_sudoku it = s.get_it(0, 0);
    EXPECT_EQ(*(it.operator->()), arr[0][0]);

    it.inc_row();
    EXPECT_EQ(*(it.operator->()), arr[0][1]);
}

TEST(Sudoku, iterator_sudoku_swap) {
    Sudoku s = init_sudoku(arr);

    Sudoku::iterator_sudoku it = s.get_it(5, 1);
    Sudoku::iterator_sudoku it2 = s.get_it(0, 2);
    Sudoku::iterator_sudoku tmp = it;
    Sudoku::iterator_sudoku tmp2 = it2;
    EXPECT_EQ(*it, arr[5][1]);
    EXPECT_EQ(*it2, arr[0][2]);
    EXPECT_EQ(it, tmp);
    EXPECT_EQ(it2, tmp2);

    swap(it, it2);
    EXPECT_EQ(*it, arr[0][2]);
    EXPECT_EQ(*it2, arr[5][1]);
    EXPECT_EQ(it, tmp2);
    EXPECT_EQ(it2, tmp);
}

TEST(Sudoku, iterator_sudoku_row_inc) {
    Sudoku s = init_sudoku(arr);

    for (int i = 0; i < 9; ++i) {
        int j = 0;
        for (auto it = s.get_it_row(i); !it.is_end(); it.inc_row(), ++j) {
            ASSERT_EQ(*it, arr[i][j]);
        }
    }
}

TEST(Sudoku, iterator_sudoku_row_dec) {
    Sudoku s = init_sudoku(arr);

    for (int i = 8; i > -1; --i) {
        int j = 8;
        for (auto it = s.get_it(i, j); !it.is_end(); it.dec_row(), --j) {
            ASSERT_EQ(*it, arr[i][j]);
        }
    }
}

TEST(Sudoku, iterator_sudoku_column_inc) {
    Sudoku s = init_sudoku(arr);

    for (int i = 0; i < 9; ++i) {
        int j = 0;
        for (auto it = s.get_it_column(i); !it.is_end(); it.inc_column(), ++j) {
            ASSERT_EQ(*it, arr[j][i]);
        }
    }
}

TEST(Sudoku, iterator_sudoku_column_dec) {
    Sudoku s = init_sudoku(arr);

    for (int i = 8; i > -1; --i) {
        int j = 8;
        for (auto it = s.get_it(j, i); !it.is_end(); it.dec_column(), --j) {
            ASSERT_EQ(*it, arr[j][i]);
        }
    }
}

TEST(Sudoku, iterator_sudoku_square_inc) {
    Sudoku s = init_sudoku(arr);

    for (int i = 0; i < 9; ++i) {
        int j = 0;
        for (auto it = s.get_it_square(i); !it.is_end(); it.inc_square(), ++j) {
            ASSERT_EQ(*it, arr_square[i][j]);
        }
    }
}

TEST(Sudoku, iterator_sudoku_square_dec) {
    Sudoku s = init_sudoku(arr);

    for (int i = 8; i > -1; --i) {
        int j = 8;
        auto it = s.get_it_square(i);
        for (int i = 0; i < 8; ++i)
            it.inc_square();
        for (; !it.is_end(); it.dec_square(), --j) {
            ASSERT_EQ(*it, arr_square[i][j]);
        }
    }
}

TEST(Sudoku, iterator_sudoku_ne) {
    Sudoku s = init_sudoku(arr);
    Sudoku s2 = init_sudoku(arr);
    Sudoku::iterator_sudoku it = s.get_it(0, 0);
    Sudoku::iterator_sudoku it2 = s2.get_it(0, 0);
    EXPECT_NE(it, it2);
}

TEST(Sudoku, generate) {
    for (int j = 0; j < 100; ++j) {
        Sudoku s = generateSudoku();
        for (int i = 0; i < 9; ++i) {
            std::set<int> numbers {1, 2, 3, 4, 5, 6, 7, 8, 9};
            for (auto it = s.get_it_row(i); !it.is_end(); it.inc_row()) {
                if (*it == 0)
                    continue;
                auto nit = numbers.find(*it);
                ASSERT_NE(nit, numbers.end());
                numbers.erase(nit);
            }
        }
        for (int i = 0; i < 9; ++i) {
            std::set<int> numbers {1, 2, 3, 4, 5, 6, 7, 8, 9};
            for (auto it = s.get_it_column(i); !it.is_end(); it.inc_column()) {
                if (*it == 0)
                    continue;
                auto nit = numbers.find(*it);
                ASSERT_NE(nit, numbers.end());
                numbers.erase(nit);
            }
        }
        for (int i = 0; i < 9; ++i) {
            std::set<int> numbers {1, 2, 3, 4, 5, 6, 7, 8, 9};
            for (auto it = s.get_it_square(i); !it.is_end(); it.inc_square()) {
                if (*it == 0)
                    continue;
                auto nit = numbers.find(*it);
                ASSERT_NE(nit, numbers.end());
                numbers.erase(nit);
            }
        }
    }
}

Sudoku init_sudoku(const int (&arr)[9][9]) {
    Sudoku s;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            s[i][j] = arr[i][j];
        }
    }
    return s;
}
