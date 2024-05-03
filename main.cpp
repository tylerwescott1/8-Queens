#include <iostream>

using namespace std;

bool findQueenSpot(int[8][8], int, int, int);
void print2DArray(int[8][8]);

int main()
{
    int firstQueenRow = 0;
    int firstQueenColumn = 0;

    int chessBoardArray[8][8] = {0};

    //Taking first queen input
    cout << "Enter initial coordinates of the first queen: ";
    
    //get two int inputs
    cin >> firstQueenRow;
    cin >> firstQueenColumn;

    cout << firstQueenRow << " " << firstQueenColumn << endl << endl;

    firstQueenRow--;
    firstQueenColumn--;
 
    chessBoardArray[firstQueenRow][firstQueenColumn] = 1;   //set first queen pos in array

    //Recursive calls
    findQueenSpot(chessBoardArray, 0, 0, firstQueenRow); //start at [0,0]

    return 0;
}

bool findQueenSpot(int arr[8][8], int row, int col, int userQueen)
{
    if (row == userQueen)   //if current row is the user placed queen, go next row
    {
        if (row == 7)   //if the user queen row is the last row, prevented printing multiple times.
        {
            print2DArray(arr);
            return 1;
        }
        findQueenSpot(arr, row+1, 0, userQueen);  //next row call
    }

    if (row >= 8)    //if the row passed is >= 8, that means all rows were filled with queen, therefore can print and return 
    {
        print2DArray(arr);
        return 1;
    }

    columnCheck:
    //check if there is already a queen in the column
    int colCheckInt = 0;
    while (colCheckInt < 8)
    {
        if (col >= 8)   //if theres no where to place, failed. 
        {
            return 0;  
        }
        if (arr[colCheckInt][col] == 1)     //if there is a queen
        {
            //Column is complete, go next column
            col++;
            colCheckInt = 0;
        }
        else
        {
            colCheckInt++;
        }
    }

    //check for diagonals
    int rowDiagonalCheck = row;
    int colDiagonalCheck = col;
    rowDiagonalCheck--;
    colDiagonalCheck--;
    while (rowDiagonalCheck >= 0 && colDiagonalCheck >= 0)
    {
        if (arr[rowDiagonalCheck][colDiagonalCheck] == 1)   //if theres a queen on the neg neg diagonal, invalid space
        {
            col++;
            goto columnCheck;
        }
        rowDiagonalCheck--;
        colDiagonalCheck--;
    }

    rowDiagonalCheck = row;
    colDiagonalCheck = col;
    rowDiagonalCheck--;
    colDiagonalCheck++;
    while (rowDiagonalCheck >= 0 && colDiagonalCheck < 8)
    {
        if (arr[rowDiagonalCheck][colDiagonalCheck] == 1)   //if theres a queen on the neg pos diagonal, invalid space
        {
            col++;
            goto columnCheck;
        }
        rowDiagonalCheck--;
        colDiagonalCheck++;
    }

    rowDiagonalCheck = row;
    colDiagonalCheck = col;
    rowDiagonalCheck++;
    colDiagonalCheck--;
    while (rowDiagonalCheck < 8 && colDiagonalCheck >= 0)
    {
        if (arr[rowDiagonalCheck][colDiagonalCheck] == 1)   //if theres a queen on the pos neg diagonal, invalid space
        {
            col++;
            goto columnCheck;
        }
        rowDiagonalCheck++;
        colDiagonalCheck--;
    }

    rowDiagonalCheck = row;
    colDiagonalCheck = col;
    rowDiagonalCheck++;
    colDiagonalCheck++;
    while (rowDiagonalCheck < 8 && colDiagonalCheck < 8)
    {
        if (arr[rowDiagonalCheck][colDiagonalCheck] == 1)   //if theres a queen on the pos pos diagonal, invalid space
        {
            col++;
            goto columnCheck;
        }
        rowDiagonalCheck++;
        colDiagonalCheck++;
    }

    //no queens in row, column, or diagonals, can place queen here.
    arr[row][col] = 1;
    //findQueenSpot(arr, row+1, 0, userQueen, queenCount);
    if (findQueenSpot(arr, row+1, 0, userQueen) == 0) //if the call returned false, remove the just placed queen and try next column
    {
        arr[row][col] = 0;
        col++;
        goto columnCheck;
    }

    return 1;
}

void print2DArray(int arr[8][8])
{
    int colCounter = 1;
    int tmpRow = 0;
    cout << "   1  2  3  4  5  6  7  8" << endl; //first row
    for (int i = 0; i < 8; i++) //for every row that you need to print
    {
        int j = 0;  //column counter
        cout << colCounter << "  ";     //print the row#
        while (j < 8)    // in each column, check if queen is in spot & print, otherwise print '-'
        {
            if (arr[i][j] == 1) //if value in array is 1, its a queen
                cout << "Q";
            else                            //otherwise, its an empty space
                cout << "-";
            cout << "  ";                   //spacing
            j++;                            //increment col counter
        }
        cout << endl;
        colCounter++;
    }
}