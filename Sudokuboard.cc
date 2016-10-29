/************************************************************************
    File: sudokuboard.cc
    Author: Mitchel Herman
    Due Date: Febuary 8th 2016

    Implementation of a sudokuboard

************************************************************************/
#include <iostream>
#include "sudokuboard.h"

using namespace std;

size_t boardSize = 9; //Golbal variable to reduce use of magic numbers in loops

//Constructor
sudokuBoard::sudokuBoard(){
	string fill = "_________";
	for(size_t x = 0; x < boardSize ; x++){
        _board[x] = fill; //Sets every row to all blank spaces
    }
}

//Prints Board
void sudokuBoard::print() const{
    //cycles through the rows and prints them
	for(size_t pRow = 0; pRow < boardSize; pRow++){
		cout << _board[pRow] << endl;
	}
}

//Places a char n at cords (r,c) on the board
void sudokuBoard::place(size_t r, size_t c, char n){
    _board[r][c] = n;
}

//removes the char at cords (r,c)
void sudokuBoard::remove(size_t r, size_t c){
    _board[r][c] = '_';
}

//Returns the char at cords (r,c)
char sudokuBoard::get(size_t r, size_t c) const{
    return _board[r][c];
}

//Returns true if the board is solved
bool sudokuBoard::solved() const{
    for(size_t x = 0; x < boardSize; x++){
        for(size_t y = 0; y < boardSize; y++){
            if(_board[x][y] == '_')
                return false;
        }
    }
    return true;
}

//Checks if char n is a valid move at cord (r,c)
bool sudokuBoard::canplace(char num, size_t r, size_t c) const
{
    if(_board[r][c] == '_'){
        //Check all in the same row to see if num is already there
        for(size_t i = 0; i < boardSize; i++){
            if(_board[r][i] == num){
                return false;
            }
        }
        //Check all in the same col to see if num is already there
        for(size_t s = 0; s < boardSize; s++){
            if(_board[s][c] == num)
                return false;
        }

        //check all in the same 3x3 grid
        size_t startGridRow = r / 3 * 3;
        size_t startGridCol = c / 3 * 3;

        for(size_t gr = startGridRow; gr < startGridRow + 3; gr++){
           for(size_t gc = startGridCol; gc < startGridCol + 3; gc++){
                if(_board[gr][gc] == num){
                    return false;
                }
            } 
        }
    }
    else
        return false;

    return true;
}
