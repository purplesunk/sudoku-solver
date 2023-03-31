#include <stdio.h>

void solver(int grid[9][9]);
void print_grid(int grid[9][9]);
int solve_only_possibility(int grid[9][9]);
int possible(int grid[9][9], int row, int col, int num);

int main(void) {
    int sudoku[9][9] = {{ 2, 6, 0, 3, 0, 0, 0, 1, 0 },
                        { 5, 8, 0, 4, 0, 0, 7, 0, 0 },
                        { 0, 0, 0, 0, 6, 0, 0, 2, 8 },
                        { 0, 0, 0, 8, 3, 0, 0, 0, 7 },
                        { 0, 1, 2, 7, 0, 5, 3, 0, 0 },
                        { 0, 5, 0, 0, 0, 0, 0, 0, 0 },
                        { 0, 4, 6, 0, 0, 0, 0, 0, 1 },
                        { 7, 0, 0, 0, 0, 0, 0, 4, 0 },
                        { 0, 3, 5, 0, 0, 0, 6, 0, 0 }};
    
    while (solve_only_possibility(sudoku));
    solver(sudoku);
}

void solver(int grid[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (grid[i][j] == 0) {
                for (int num = 1; num < 10; num++) {
                    if (possible(grid, i, j, num)) {
                        grid[i][j] = num;
                        solver(grid);
                        grid[i][j] = 0;
                    }
                }
                // if there is no possible number to use, go back.
                return;
            }
        }
    }
    // when the grid is full print the result
    print_grid(grid);
}

int possible(int grid[9][9], int row, int col, int num) {
    // check possible number on the col:
    for (int i = 0; i < 9; i++) {
        if (grid[row][i] == num) {
            return 0;
        }
    }
    // check possible number on the row:
    for (int i = 0; i < 9; i++) {
        if (grid[i][col] == num) {
            return 0;
        }
    }
    // check possible number on the 3x3 box:
    int row0 = (row / 3) * 3; 
    int col0 = (col / 3) * 3;

    for (int i = row0; i < row0 + 3; i++) {
        for (int j = col0; j < col0 + 3; j++) {
            if (grid[i][j] == num) {
                return 0;
            }
        }
    }
    return 1;
}

int solve_only_possibility(int grid[9][9]) {
    int worked = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (grid[i][j] == 0) {
                int quantity = 0;
                int last_number = 0;
                for (int num = 1; num < 10; num++) {
                    if (possible(grid, i, j, num)) {
                        quantity++;
                        last_number = num;
                    }
                }
                if (quantity == 1) {
                    grid[i][j] = last_number;
                    worked = 1;
                }
            }
        }
    }
    return worked;
}

void print_grid(int grid[9][9]) {
    printf("-------------------------------\n");
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (j == 8) {
                printf(" %i |\n", grid[i][j]);
            } else if (j % 3 == 2) {
                printf(" %i |", grid[i][j]);
            } else if (j == 0) {
                printf("| %i ", grid[i][j]);
            } else {
                printf(" %i ", grid[i][j]);
            }
        }
        if (i % 3 == 2) {
            printf("-------------------------------\n");
        }
    }
}