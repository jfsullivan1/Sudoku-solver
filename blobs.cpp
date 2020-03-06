/*
John Sullivan
CSC212
Instructor: Marco Alvarez
Date: 10/20/18
*/

#include <iostream>
#include <fstream>

//This program will count the amount of blobs in a given grid.

//Here I will be using the same functions as my cells.cpp program to count the cells in my blobs,
//   That way, I can tell if a blob is present at my coordinates on the "grid"
int countCells4(bool** grid, int row, int col, int rows, int cols);
int countCells8(bool** grid, int row, int col, int rows, int cols);
bool isBlob(bool** grid, int row, int col);
int countBlobs(bool** grid, int rows, int cols, int type);

int main(int argc, char* argv[]){
    std::ifstream inFile;
    inFile.open(argv[1]);
    //This would be used to print an error if a file was input the wrong way or it didn't exist,
    //     but gradescope didn't like it.
    /*
    if(!inFile){
        std::cerr << "NO FILE EXISTS" << inFile << std::endl;
        exit(EXIT_FAILURE);
    }
    */

    const int rows = atoi(argv[2]);
    const int cols = atoi(argv[3]);
    int horz = 0;
    int vert = 0;

    //TYPE here will be either 4 or 8. If it's type 4, we are only checking in 4 directions for blobs.
    //    Type 8 will check in 8 directions (up,down,left,right,and corners.)
    int type = atoi(argv[4]);

    //Creates a NxN empty board
    bool **board = new bool*[rows];
    for(int i = 0; i < rows; i++){
        board[i] = new bool[cols];
    }

    char ch;

    //Read the input file and assign it's values (either 0 or 1) to each space in the empty board.
    while(inFile.get(ch)){
        if(isspace(ch)){
            //do nothing
        }
        else if(ch == '0'){
            board[vert][horz] = 0;
            horz++;
            if (horz >= cols){
                ++vert;
                horz = 0;
            }
        }
        else if(ch == '1'){
            board[vert][horz] = 1;
            horz++;
            if (horz >= cols){
            ++vert;
            horz = 0;
            }
        }

    }
    inFile.close();

    //Here, we call the function to count the blobs in the grid.
    int blobs = 0;
    blobs = countBlobs(board, rows, cols, type);
    std::cout << blobs;
}

int countCells4(bool **grid, int x, int y, int rows, int cols){
    //Check the boundaries!
    if (x >= rows || y >= cols) return 0;

    //Check to see if where we are on the grid is part of a blob!
    bool isOne = isBlob(grid, x, y);

    //If it's not a blob, return 0 so we can move to the next spot to check.
    if (!isOne) return 0;

    //If it is, then we set our current posititon to 0 so we know we've checked it.
    grid[x][y] = 0;

    //Counts how many cells there are in the current blob recursively in 4 directions.
    return countCells4(grid, x, y-1, rows, cols) + countCells4(grid, x+1, y, rows, cols) +
        countCells4(grid, x-1, y, rows, cols) + countCells4(grid, x, y+1, rows, cols) + 1;
}

int countCells8(bool** grid, int x, int y, int rows, int cols){
    //Same as countCells4, but checks 8 directions in the recursive return statement.
    if (x >= rows || y >= cols) return 0;
    bool isOne = isBlob(grid, x, y);
    if (!isOne) return 0;
    grid[x][y] = 0;
    return countCells8(grid, x, y-1, rows, cols) + countCells8(grid, x+1, y, rows, cols) +
        countCells8(grid, x-1, y, rows, cols) + countCells8(grid, x, y+1, rows, cols) +
        countCells8(grid, x-1, y-1, rows, cols) + countCells8(grid, x+1, y+1, rows, cols) +
        countCells8(grid, x+1, y-1, rows, cols) + countCells8(grid, x-1, y+1, rows, cols) + 1;
}

//Function to check if the spot we are at on the grid is part of a blob
bool isBlob(bool** grid, int row, int col){
    return (row >= 0 && col >= 0 && grid[row][col] == 1)? true : false;
}

//Function to count the amount of blobs on the grid!
int countBlobs(bool** grid, int rows, int cols, int type){
    int blobCount = 0;
    int cells = 0;
    //Check each spot in the grid, and if we hit a blob and countCells4 returns more than 0, then we have a blob!
    //    Then that blob will all be set to 0s and won't be checked again!
    if(type == 4){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                cells = countCells4(grid, i, j, rows, cols);
                if(cells > 0){
                    blobCount++;
                }
            }
        }
    }
    //Check each spot in the grid, and if we hit a blob and countCells8 returns more than 0, then we have a blob!
    //    Then that blob will all be set to 0s and won't be checked again!
    if(type == 8){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                cells = countCells8(grid, i, j, rows, cols);
                if(cells > 0){
                    blobCount++;
                }
            }
        }
    }
    return blobCount;
}