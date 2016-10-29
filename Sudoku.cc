/************************************************************************
    File: sudoku.cc
    Author: Mitchel Herman
    Due Date: Febuary 26th 2016

    Main program for sudoku project
    Solves a sudoku puzzle

************************************************************************/

#include <iostream>
#include <cstdlib>
#include "sudokuboard.h"
#include "stack.h"

using namespace std;

size_t bSize = 9; //Global Variable to use instead of 9 for size of board

//Reads the input to fill the board.
void fill_board(sudokuBoard & board)
{
    for(size_t i = 0; i < bSize; i++){ //Cycles through row
        string input;
        cin >> input; //Gets input from user
        for(size_t j = 0; j < bSize; j++) //Cycles through Cols
            board.place(i,j,input[j]); //Places the index of input (j) on
                                        //index of col on board
    }
}

bool most_constrained(const sudokuBoard & board, 
                        size_t & row, size_t & col, char & numeral)
{
    size_t most_constrained = bSize + 1; //Every spot will be less than this
    size_t amount_free = 0; //Variable records number of numbers allowed at pos

    //Cycle through every row and col
    for(size_t r = 0; r < bSize; r++){
        for(size_t c = 0; c < bSize; c++){
            if(board.get(r,c) == '_'){ //If the spot is empty
                for(size_t x = 1; x <= bSize; x++){ //Cycle throgh moves (1-9)
                    if(board.canplace(x+'0',r,c))   //and see if its valid
                        amount_free++; //If its valid, increase temp var
                }
                //If the temp var is less than the prev most constrained spot
                if(amount_free < most_constrained){
                    row = r; //Set row and col
                    col = c; //Equal to the spot
                    //and change the comparison variable
                    most_constrained = amount_free;
                }
                amount_free = 0; //Reset amount free to 0
            }
        }
    }

    //After most constrained spot is found
    //If it has valid moves
    if(most_constrained != 0){
        for(size_t x = 1; x <= bSize; x++){ //Cycle through moves
            if(board.canplace(x+'0',row,col)){
                    numeral = x+'0'; //Find the lowest number that is valid
                    return true; //and return true
            }
        }
    }
    //If it has no valid moves,
    return false;
}

//Places num on board at cord (row,col) and records the move into the stack
void place_and_record(sudokuBoard & board, stack & moves, 
                        size_t row, size_t col, char num)
{
    board.place(row, col, num);
    moves.push(row);
    moves.push(col);
    moves.push(num - '0');
}

bool backtrack(sudokuBoard & board, stack & moves)
{
    //Set num col and row to the last move, and pop them from stack
    char num = moves.top() + '0'; moves.pop();
    size_t col = moves.top(); moves.pop();
    size_t row = moves.top(); moves.pop();

    //Remove the last move
    board.remove(row,col);

    //Check to see if same position has another valid move
    size_t n = (num - '0') + 1;
    while(n <= 9){ //Until n is 9
        if(board.canplace(n + '0', row, col)){ //If it finds a valid move
            place_and_record(board, moves, row, col, n+'0');
            return true;
        }
         n++;
    }
    //No valid moves found
    return false;
}

int main(){
    //Create Board
    sudokuBoard sboard;
    fill_board(sboard);
    //Create variables for row col and num used for checking
    size_t row;
    size_t col;
    char num;
    //Create stack to record moves
    stack moves;

    while(!sboard.solved()){ //Until the board is solved
        //Find most costrained spot on board
        if(most_constrained(sboard, row, col, num)){
            place_and_record(sboard, moves, row, col, num);
        }
        else{ //The most constrained spot has no valid moves
            bool backtrack_done = false;
            while(!backtrack_done) //Until it finishes backtracking
                backtrack_done = backtrack(sboard,moves);//Continue to backtrack
        }
    }
    sboard.print(); //Print finished sudoku board
}


