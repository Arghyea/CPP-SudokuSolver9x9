#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

class SudokuSolver {
private:
    vector<vector<int>> grid;
    static const int SIZE = 9;

    bool isSafe(int row, int col, int num) {
        for (int x = 0; x < SIZE; x++) {
            if (grid[row][x] == num || grid[x][col] == num) return false;
        }

        
        int startRow = row - row % 3, startCol = col - col % 3;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (grid[i + startRow][j + startCol] == num) return false;
            }
        }
        return true;
    }

    bool solveSudoku() {
        int row, col;

        if (!findUnassignedLocation(row, col)) return true; 

        for (int num = 1; num <= SIZE; num++) {
            if (isSafe(row, col, num)) {
                grid[row][col] = num;

                if (solveSudoku()) return true;

                grid[row][col] = 0; 
            }
        }
        return false;
    }

    bool findUnassignedLocation(int& row, int& col) {
        for (row = 0; row < SIZE; row++) {
            for (col = 0; col < SIZE; col++) {
                if (grid[row][col] == 0) return true;
            }
        }
        return false;
    }

    void printGrid() {
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                cout << grid[row][col] << " ";
                if ((col + 1) % 3 == 0 && col != SIZE - 1) cout << "| ";
            }
            cout << endl;
            if ((row + 1) % 3 == 0 && row != SIZE - 1) {
                cout << "---------------------" << endl;
            }
        }
    }

public:
    SudokuSolver(const vector<vector<int>>& initialGrid) : grid(initialGrid) {}

    void solve() {
        auto start = chrono::high_resolution_clock::now();
        if (solveSudoku()) {
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> elapsed = end - start;
            cout << "\nSudoku solved in " << elapsed.count() << " seconds.\n";
            printGrid();
        } else {
            cout << "No solution exists." << endl;
        }
    }
};

int main() {
    vector<vector<int>> grid = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    SudokuSolver solver(grid);
    solver.solve();

    return 0;
}
