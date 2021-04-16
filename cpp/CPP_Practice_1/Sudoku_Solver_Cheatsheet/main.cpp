// https://www.pramp.com/challenge/O5PGrqGEyKtq9wpgw6XP

#include <iostream>
#include <vector>
#include <windows.h>

using namespace std;

// Print the sudoku
void print(vector<vector<char>> board){
    for(int i = 0; i < board.size(); i++){
        for(int j = 0; j < board[i].size(); j++){
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Check if sudoku is all filled up
bool checkIfFilled(vector<vector<char>> board){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(board[i][j] == '.')
                return false;
        }
    }
    return true;
}

// Check if a given number can be inserted at a given position
bool checkIfInsertOkay(vector<vector<char>> board, int x, int y, char num){
    // Check row if num already exists
    for(int j = 0; j < 9; j++){
        if(board[x][j] == num)
            return false;
    }
    // Check column if num already exists
    for(int i = 0; i < 9; i++){
        if(board[i][y] == num)
            return false;
    }
    // Check 3x3 gird if num already exists
    // Find the corners
    // Find i
    if(x < 3)
        x = 0;
    else if(x < 6)
        x = 3;
    else
        x = 6;
    // Find j
    if(y < 3)
        y = 0;
    else if(y < 6)
        y = 3;
    else
        y = 6;
    // Check the 3x3 box
    for(int i = x; i < x+3; i++){
        for(int j = y; j < y+3; j++){
            if(board[i][j] == num)
                return false;
        }
    }
    return true;
}

// Helper function because of const issues
bool sudokuSolveHelper(vector<vector<char>> &board){
    // Base condition - if sudoku gets completely filled
    if(checkIfFilled(board))
        return true;

    // Iterate through the sudoku
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            // If empty space
            if(board[i][j] == '.'){
                for(int k = 1; k <= 9; k++){
                    // Check if char(k) can be inserted at this empty location
                    char ch = '0' + k;
                    if(checkIfInsertOkay(board, i, j, ch)){
                        // Put k in this empty location and check
                        board[i][j] = ch;
                        // Check if done
                        bool flag = sudokuSolveHelper(board);
                        if(flag)
                            return true;
                        else
                            // Else, backtrack by making it empty again
                            board[i][j] = '.';
                    }
                }
                return false;
            }
        }
    }
    return true;
}

// Return true if a correct sudoku can be formed
// Apply backtracking
// Time complexity = O(9^empty spaces)
bool sudokuSolve(vector<vector<char>> &board){
    return sudokuSolveHelper(board);
}

int main() {

    vector<vector<char>> board = {
        {'.','.','.','7','.','.','3','.','1'},
        {'3','.','.','9','.','.','.','.','.'},
        {'.','4','.','3','1','.','2','.','.'},
        {'.','6','.','4','.','.','5','.','.'},
        {'.','.','.','.','.','.','.','.','.'},
        {'.','.','1','.','.','8','.','4','.'},
        {'.','.','6','.','2','1','.','5','.'},
        {'.','.','.','.','.','9','.','.','8'},
        {'8','.','5','.','.','4','.','.','.'}
    };
    print(board);
    bool flag = sudokuSolve(board);
    if(flag){
        cout << "A solution exists as below\n";
        print(board);
    }
    else
        cout << "No solution exists!\n";
    return 0;
}