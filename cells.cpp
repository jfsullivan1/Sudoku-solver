/*
John Sullivan
CSC212
Instructor: Marco Alvarez
Date: 10/19/18
*/

#include <iostream>
#include <fstream>

int countCells4(bool** grid, int row, int col, int rows, int cols);
int countCells8(bool** grid, int row, int col, int rows, int cols);
bool isBlob(bool** grid, int row, int col);

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

    int x = atoi(argv[4]);
    int y = atoi(argv[5]);

    int horz = 0;
    int vert = 0;
    int type = atoi(argv[6]);
    int cells = 0;

    //THIS is important: the inputs are in HUMAN readable numbers. So that means if I want my coordinates on an
    //  array, it wouldn't be 0, 1 but rather input as 1, 2! So that means in order to work with the array
    //     like I normally would, I take away 1 from the inputs.
    x = (x == 0)? 0 : x-1;
    y = (y == 0)? 0 : y-1;

    //Fills an empty NxN board
    bool **board = new bool*[rows];
    for(int i = 0; i < rows; i++){
        board[i] = new bool[cols];
    }

    char ch;

    //Read the file, and fill our NxN array with 0's and 1's (whatever is on the file)
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

    //If the type input was 4, we check to count cells in only four directions (up, down, left, right)
    if(type == 4){
        cells = countCells4(board, x, y, rows, cols);
    }
    //If the type input was 8, we check to count cells in all eight directions(includes corners!)
    if(type == 8){
        cells = countCells8(board, x, y, rows, cols);
    }
    std::cout << cells;
}

int countCells4(bool **grid, int x, int y, int rows, int cols){
    if (x >= rows || y >= cols) return 0;
    bool isOne = isBlob(grid, x, y);
    if (!isOne) return 0;
    grid[x][y] = 0;
    //This keeps a count of how many cells are in each blob.
    return countCells4(grid, x, y-1, rows, cols) + countCells4(grid, x+1, y, rows, cols) +
        countCells4(grid, x-1, y, rows, cols) + countCells4(grid, x, y+1, rows, cols) + 1;
}

int countCells8(bool** grid, int x, int y, int rows, int cols){
    if (x >= rows || y >= cols) return 0;
    bool isOne = isBlob(grid, x, y);
    if (!isOne) return 0;
    grid[x][y] = 0;
    //This keeps a count of how many cells are in each blob.
    //    as you can see, as mentioned above this checks all eight directions which include the first four
    //       (up, left, down, right) and the corners.
    return countCells8(grid, x, y-1, rows, cols) + countCells8(grid, x+1, y, rows, cols) +
        countCells8(grid, x-1, y, rows, cols) + countCells8(grid, x, y+1, rows, cols) +
        countCells8(grid, x-1, y-1, rows, cols) + countCells8(grid, x+1, y+1, rows, cols) +
        countCells8(grid, x+1, y-1, rows, cols) + countCells8(grid, x-1, y+1, rows, cols) + 1;
}

//Checks if the current cell is part of a blob (is a 1)
bool isBlob(bool** grid, int row, int col){
    return (row >= 0 && col >= 0 && grid[row][col] == 1)? true : false;
}



