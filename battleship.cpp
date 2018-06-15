/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			battleship.c
 * Author(s):		Peter Bauer
 * Due Date:		#due#
 *-----------------------------------------------------------------------------
 * Description:
 * <your description here>
 *-----------------------------------------------------------------------------
*/
#include <stdio.h>
#include "battleship.h"

CellContent my_field[FIELDSIZE][FIELDSIZE];
CellContent opposite_field[FIELDSIZE][FIELDSIZE];
CellContent guesses[FIELDSIZE][FIELDSIZE];

void load_game(){
FILE* file_me = fopen("battleship.my", "r");
FILE* file_enemy = fopen("battleship.op", "r");

for (int i = 0; i < FIELDSIZE; i++) {
  for (int j = 0; j < FIELDSIZE; j++) {
    guesses[i][j] = Unknown;
    fread(&my_field[i][j], 1, sizeof(CellContent), file_me);
    fread(&opposite_field[i][j], 1,sizeof(CellContent), file_enemy);
  }
}
fclose(file_me);
fclose(file_enemy);
}

CellContent get_shot(int row, int col){
  if (check_if_out_of_range(row,col)) {return OutOfRange;}
  else{return my_field[row][col];}
}

bool shoot(int row, int col){
  CellContent my_guess = get_my_guess(row, col);
  if (my_guess == OutOfRange || check_if_out_of_range(row,col)) {
    return false;
  }
  else if (opposite_field[row][col] == Water || opposite_field[row][col] == Boat ){
    guesses[row][col] = opposite_field[row][col];
    if (guesses[row][col] == Boat) {
      for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
          my_guess = get_my_guess(i+row, j+col);
          if (my_guess == Unknown) {
            guesses[i+row][j+col] = Water;
          }
        }
      }
    }
  }
return true;
}

CellContent get_my_guess(int row, int col){
  if (check_if_out_of_range(row,col)){return OutOfRange;}
  else{return guesses[row][col];}
}

bool check_if_out_of_range(int row,int col){
  if(row< 0 || row >= FIELDSIZE || col < 0 || col >= FIELDSIZE){return true;}
  return false;
  }
