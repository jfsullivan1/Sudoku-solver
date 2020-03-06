/*
John Sullivan
CSC212
Instructor: Marco Alvarez
Date: 10/26/18
*/

#include <iostream>
#include <fstream>
#include <string>

//This function will return whether a given maze with NxN dimensions has a solution, and
//   where the start and end of the maze is (coordinates).
bool maze(int** grid, bool** checked, int rows, int cols, int maxVal, int idxMinX, int idxMinY);

int main(int argc, char* argv[]){
    std::ifstream inFile;
    inFile.open(argv[1]);
    //This would return an error if the input file didn't exist. Gradescope didn't like it.
    /*
    if(!inFile){
        std::cerr << "NO FILE EXISTS" << inFile << std::endl;
        exit(EXIT_FAILURE);
    }
    */
    //RowsXCols are the dimensions of the maze, given as command line input.
    const int rows = atoi(argv[2]);
    const int cols = atoi(argv[3]);
    int vert = 0;
    int horz = 0;

    //This piece of code creates a 2D array.
    int **board = new int*[rows];
    for(int i = 0; i < rows; i++){
        board[i] = new int[cols];
    }

    //Here the program will read the file, and each number separated by spaces will be placed into our 2D array,
    //   so we can work with it.
    int num = 0;
    std::string str = "";
    while(inFile >> str){
        if(str == "\n" || str == " "){
            //do nothing
        }
        else
        {
            num = stoi(str);
            board[vert][horz] = num;
            horz++;
            if(horz>=cols){
                ++vert;
                horz = 0;
            }
        }
    }
    inFile.close();

    //These values will be used to find the start and end of the maze.
    int maxVal = 0;
    int minVal = board[0][0];

    //These are coordinates for the start and end of the maze.
    int idxMaxX = 0;
    int idxMaxY = 0;
    int idxMinX = 0;
    int idxMinY = 0;

    //This creates a 2D array to keep track of the spots we've already been on the maze.
    bool **checked = new bool*[rows];
    for(int i = 0; i < rows; i++){
        checked[i] = new bool[cols];
    }

    //This nested for loop fills the "checked" array with 0's, indicating none of the spots have been visited.
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            checked[i][j] = 0;
        }
    }

    //This finds the minimum and maximum values in the "maze" given, and takes note of their coordinates.
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(board[i][j] > maxVal){
                maxVal = board[i][j];
                idxMaxX = i;
                idxMaxY = j;
            }
            if(board[i][j] < minVal){
                minVal = board[i][j];
                idxMinX = i;
                idxMinY = j;
            }
        }
    }

    //Call the function to try to solve the maze. If it finds a solution, it prints yes, otherwise it prints no.
    //   It also prints the coordinates of the start(x,y) and finish(x,y) positions.
    bool found = false;
    found = maze(board, checked, rows, cols, maxVal, idxMinX, idxMinY);
    if(found){
        std::cout << idxMinX + 1 << " " << idxMinY + 1 << " " << idxMaxX + 1 << " " << idxMaxY + 1 << " " << "yes";
    }
    else
    {
        std::cout << idxMinX + 1 << " " << idxMinY + 1 << " " << idxMaxX + 1 << " " << idxMaxY + 1 << " " << "no";
    }
}

//The maze function to find a good path to travel along the given board!
// This function uses recursion and backtracking to find if a path exists.
bool maze(int** grid, bool** checked, int rows, int cols, int maxVal, int x, int y){
    //If out of bounds, go back to the previous function in the stack!
    if(x > rows || y > cols || x < 0 || y < 0) return false;

    //If we found the end of the maze, we are finished!
    if(grid[x][y] == maxVal) return true;

    //If it's not found yet, mark the checked array so we don't revisit this spot.
    checked[x][y] = true;

    //Make a variable for the recursion to return to!
    bool move = false;
    int currVal = grid[x][y];

    //If the (up) spot is OK to move to, then recursively call the function and move.
    if((x - 1 >= 0) && (checked[x - 1][y] == false)){
        if(grid[x - 1][y] >= currVal){
            move = maze(grid, checked, rows, cols, maxVal, x - 1, y);
            if(move) return true;
        }
    }
    //If the (left) spot is OK to move to, then recursively call the function and move.
    if((y - 1 >= 0) && (checked[x][y - 1] == false)){
        if(grid[x][y - 1] >= currVal){
            move = maze(grid, checked, rows, cols, maxVal, x, y - 1);
            if(move) return true;
        }
    }
    //If the (down) spot is OK to move to, then recursively call the function and move.
    if((x + 1 < rows) && (checked[x + 1][y] == false)){
        if(grid[x + 1][y] >= currVal){
            move = maze(grid, checked, rows, cols, maxVal, x + 1, y);
            if(move) return true;

        }
    }
    //If the (right) spot is OK to move to, then recursively call the function and move.
    if((y + 1 < cols) && (checked[x][y + 1] == false)){
        if(grid[x][y + 1] >= currVal){
            move = maze(grid, checked, rows, cols, maxVal, x, y + 1);
            if(move) return true;
        }
    }
    //If there is no where else to travel, then we have to go back!
    return false;
}
