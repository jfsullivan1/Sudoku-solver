/*
John Sullivan
CSC212
Instructor: Marco Alvarez
Date: 10/25/18
*/

#include <iostream>
#include <fstream>

//This program is going to solve any given sudoku board instantly! (I know, cool right?)
bool rSolve(int **board);

//I have to check in each recursive call if there are any unfilled spots in the board
bool isNotFilled(int **board, int &x, int &y);

//I have to check that the number I'm trying to place in the sudoku board does not conflict with any row/col
bool rowColCheck(int **board, int num, int x, int y);

//I ALSO have to check that the number I'm trying to place in the sudoku board does not conflict with a 3x3 box.
bool boxCheck(int **board, int num, int x, int y);

int main(int argc, char* argv[]){
    std::ifstream inFile;
    inFile.open(argv[1]);
    //This would be used to print an error if a file was input the wrong way or it didn't exist,
    //     but gradescope didn't like it.
    /*if(!inFile){
        std::cerr << "Input Error. Sudoku board file not found." << inFile << std::endl;
        exit(EXIT_FAILURE);
    }
    */

    int vert = 0;
    int horz = 0;

    //This makes an empty board of ints with row and col size of 9 because a sudoku board is always 9x9!
    int **board = new int*[9];
    for(int i = 0; i < 9; i++){
        board[i] = new int[9];
    }

    char ch;
    int num = 0;

    //I have to check if the numbers entered are 1 - 9 and if they are, fill the sudoku board (our array) with
    //   the correct numbers at the correct indicies.
    while(inFile.get(ch)){
        if(isspace(ch)){
            //do nothing
        }
        if((int)ch >= 48 && (int)ch <= 57){

            num = ch - '0';
            board[vert][horz] = num;
            horz++;
            if(horz>=9){
                ++vert;
                horz = 0;
            }
        }
    }
    inFile.close();

    //We solve the sudoku board, and if there is no possible solution, it doesn't print the board.
    //    if we do solve it, we will print the solved board.
    bool solved = rSolve(board);
    if(solved == true){
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                std::cout << board[i][j];
                if(j < 8) std::cout << ",";
            }
            std::cout << std::endl;
        }
    }
}

//This function solves sudoku in it's entirety!
bool rSolve(int **board){
    //This will be assigned a value once we check if there's any unfilled spots in the sudoku board.
    //   if there is an unfilled spot, (x, y) will be the first unfilled spot.
    int x, y;

    //If there are unfilled spots on the array, we skip this line. If not, then we finished!
    if(!isNotFilled(board,x,y)) return true;

    //Try filling each spot with 1-9, after we make sure that it's a valid space (doesn't conflict with ...
    //    rows or cols, or a box!)
    for(int i = 1; i <= 9; i++){
        if(rowColCheck(board, i, x, y) && boxCheck(board, i, x, y)){
            //Set the current position to (i) (the number we are at in the for loop 1 - 9)
            board[x][y] = i;
            //Keep doing this, and if it works, keep going
            if(rSolve(board)) return true;
            //If we found out that the number eventually doesn't work, we backtrack and try a different number!
            //  (this will go to the next iteration in the for loop 1-9)
            board[x][y] = 0;
        }
    }
    return false;
}

//This function will check if the array is filled all the way or not.
bool isNotFilled(int **board, int &x, int &y){
    for(x = 0; x < 9; x++){
        for(y = 0; y < 9; y++){
            if(board[x][y] == 0) return true;
        }
    }
    return false;
}

//This function checks if the rows or columns conflict with where we're trying to put the number (i)(1-9)
bool rowColCheck(int **board, int num, int x, int y){
    bool canPlace = true;
    for(int i = 0; i < 9; i++){
        if(board[x][i] == num) canPlace = false;
    }
    for(int i = 0; i < 9; i++){
        if(board[i][y] == num) canPlace = false;
    }
    return canPlace;
}

//This checks the 3x3 box that we are located in.
//    There are a couple ways this could have been accomplished, but this will check an index, say
//       (4, 4) and subtract 4%3 from each. This will give us 3,3 and we only want to check the first
//          three rows/cols (the box) of wherever we are located. Will return true (safe) if nothing conflicts.
bool boxCheck(int **board, int num, int x, int y){
    x = x - x%3;
    y = y - y%3;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(board[i+x][j+y] == num) return false;
        }
    }
    return true;
}
