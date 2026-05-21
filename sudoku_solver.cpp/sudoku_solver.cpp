#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class SudokuSolver {
private:
    static const int SIZE = 9;
    static const int SUBGRID = 3;
    int grid[SIZE][SIZE];
    
    // Check if placing a number in a cell is valid
    bool isSafe(int row, int col, int num) {
        // Check row
        for (int x = 0; x < SIZE; x++) {
            if (grid[row][x] == num) {
                return false;
            }
        }
        
        // Check column
        for (int x = 0; x < SIZE; x++) {
            if (grid[x][col] == num) {
                return false;
            }
        }
        
        // Check 3x3 subgrid
        int startRow = row - row % SUBGRID;
        int startCol = col - col % SUBGRID;
        
        for (int i = 0; i < SUBGRID; i++) {
            for (int j = 0; j < SUBGRID; j++) {
                if (grid[i + startRow][j + startCol] == num) {
                    return false;
                }
            }
        }
        
        return true;
    }
    
    // Find empty cell in the grid
    bool findEmptyCell(int &row, int &col) {
        for (row = 0; row < SIZE; row++) {
            for (col = 0; col < SIZE; col++) {
                if (grid[row][col] == 0) {
                    return true;
                }
            }
        }
        return false;
    }
    
    // Backtracking algorithm to solve Sudoku
    bool solveSudoku() {
        int row, col;
        
        // If no empty cell found, puzzle is solved
        if (!findEmptyCell(row, col)) {
            return true;
        }
        
        // Try numbers 1-9
        for (int num = 1; num <= 9; num++) {
            if (isSafe(row, col, num)) {
                // Place number
                grid[row][col] = num;
                
                // Recursively solve rest of the puzzle
                if (solveSudoku()) {
                    return true;
                }
                
                // Backtrack if solution not found
                grid[row][col] = 0;
            }
        }
        
        return false;
    }

public:
    // Constructor
    SudokuSolver() {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                grid[i][j] = 0;
            }
        }
    }
    
    // Input Sudoku puzzle
    void inputPuzzle() {
        cout << "Enter Sudoku puzzle (use 0 for empty cells):\n";
        cout << "Enter 9 numbers per row, separated by spaces:\n\n";
        
        for (int i = 0; i < SIZE; i++) {
            cout << "Row " << (i + 1) << ": ";
            for (int j = 0; j < SIZE; j++) {
                cin >> grid[i][j];
                
                // Validate input
                if (grid[i][j] < 0 || grid[i][j] > 9) {
                    cout << "Invalid input! Use numbers 0-9 only.\n";
                    j--;
                }
            }
        }
    }
    
    // Load a predefined puzzle for testing
    void loadSamplePuzzle() {
        int sample[SIZE][SIZE] = {
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
        
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                grid[i][j] = sample[i][j];
            }
        }
    }
    
    // Display the Sudoku grid
    void displayGrid() {
        cout << "\n";
        cout << "  ╔═══════╦═══════╦═══════╗\n";
        
        for (int i = 0; i < SIZE; i++) {
            if (i == 3 || i == 6) {
                cout << "  ╠═══════╬═══════╬═══════╣\n";
            }
            
            cout << "  ║ ";
            for (int j = 0; j < SIZE; j++) {
                if (grid[i][j] == 0) {
                    cout << "· ";
                } else {
                    cout << grid[i][j] << " ";
                }
                
                if (j == 2 || j == 5) {
                    cout << "║ ";
                }
            }
            cout << "║\n";
        }
        
        cout << "  ╚═══════╩═══════╩═══════╝\n";
    }
    
    // Solve and display solution
    void solve() {
        cout << "\n╔════════════════════════════╗\n";
        cout << "║   ORIGINAL PUZZLE          ║\n";
        cout << "╚════════════════════════════╝\n";
        displayGrid();
        
        cout << "\nSolving";
        for (int i = 0; i < 3; i++) {
            cout << ".";
            cout.flush();
        }
        cout << "\n";
        
        if (solveSudoku()) {
            cout << "\n╔════════════════════════════╗\n";
            cout << "║   SOLUTION FOUND! ✓        ║\n";
            cout << "╚════════════════════════════╝\n";
            displayGrid();
        } else {
            cout << "\n╔════════════════════════════╗\n";
            cout << "║   NO SOLUTION EXISTS ✗     ║\n";
            cout << "╚════════════════════════════╝\n";
        }
    }
    
    // Validate if current grid state is valid
    bool validatePuzzle() {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (grid[i][j] != 0) {
                    int temp = grid[i][j];
                    grid[i][j] = 0;
                    
                    if (!isSafe(i, j, temp)) {
                        grid[i][j] = temp;
                        return false;
                    }
                    
                    grid[i][j] = temp;
                }
            }
        }
        return true;
    }
};

void displayMenu() {
    cout << "\n╔════════════════════════════════════╗\n";
    cout << "║     SUDOKU SOLVER - MAIN MENU      ║\n";
    cout << "╚════════════════════════════════════╝\n";
    cout << "  1. Enter your own puzzle\n";
    cout << "  2. Solve sample puzzle\n";
    cout << "  3. Exit\n";
    cout << "────────────────────────────────────\n";
    cout << "  Enter choice: ";
}

int main() {
    SudokuSolver solver;
    int choice;
    
    cout << "\n╔════════════════════════════════════╗\n";
    cout << "║   SUDOKU SOLVER USING BACKTRACKING ║\n";
    cout << "╚════════════════════════════════════╝\n";
    
    while (true) {
        displayMenu();
        cin >> choice;
        
        switch (choice) {
            case 1: {
                solver.inputPuzzle();
                
                if (solver.validatePuzzle()) {
                    solver.solve();
                } else {
                    cout << "\n✗ Invalid puzzle! Check your input.\n";
                }
                break;
            }
            
            case 2: {
                solver.loadSamplePuzzle();
                solver.solve();
                break;
            }
            
            case 3: {
                cout << "\n╔════════════════════════════════════╗\n";
                cout << "║   Thank you for using the solver!  ║\n";
                cout << "╚════════════════════════════════════╝\n\n";
                return 0;
            }
            
            default: {
                cout << "\n✗ Invalid choice! Please try again.\n";
            }
        }
    }
    
    return 0;
}