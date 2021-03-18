#include<stdio.h>
#include <stdbool.h>


#define N 9
#define UNASSIGNED 0


void print_board(int board[N][N]);
bool is_valid_num(int board[N][N], int *row, int *col, int num);
bool find_empty_cell(int board[N][N],int *row ,int *col);
bool solve(int board[N][N]);

int main(){

  int sudoku[N][N] = {
    {3,6,9,0,5,0,0,0,8},
    {0,4,7,0,8,0,0,0,0},
    {0,0,1,0,7,0,9,0,2},
    {0,8,2,1,0,5,4,0,0},
    {1,0,5,4,6,8,3,0,9},
    {4,0,0,0,0,9,0,0,0},
    {5,2,0,3,4,0,0,9,0},
    {7,0,0,0,1,2,8,0,4},
    {0,1,4,0,9,0,2,0,5}
    };
/* answer->
    3 6 9  2 5 4  7 1 8
    2 4 7  9 8 1  6 5 3
    8 5 1  6 7 3  9 4 2

    9 8 2  1 3 5  4 7 6
    1 7 5  4 6 8  3 2 9
    4 3 6  7 2 9  5 8 1

    5 2 8  3 4 6  1 9 7
    7 9 3  5 1 2  8 6 4
    6 1 4  8 9 7  2 3 5
*/

  printf("     _____           _       _          _____       _                       \n");
  printf("    /  ___|         | |     | |        /  ___|     | |                      \n");
  printf("    \\ `--. _   _  __| | ___ | | ___   _\\ `--.  ___ | |_   _____           \n");
  printf("     `--. \\ | | |/ _` |/ _ \\| |/ / | | |`--. \\/ _ \\| \\ \\ / / _ \\     \n");
  printf("    /\\__/ / |_| | (_| | (_) |   <| |_| /\\__/ / (_) | |\\ V /  __/         \n");
  printf("    \\____/ \\__,_|\\__,_|\\___/|_|\\_\\\\__,_\\____/ \\___/|_| \\_/ \\___|  \n");
  printf("                                                                            \n");
  printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");

  printf("_______________________________\n");
  print_board(sudoku);
  printf("-------------------------------\n");
  if(solve(sudoku) == true){
    print_board(sudoku);
  }
  else{
    printf("Sudoku cannot be solved...\n");
  }
  return 0;
}
//Loops through the sudoku grid and looks for empty cells ie. checks for completion of the sudoku
bool find_empty_cell(int board[N][N],int *row ,int *col){
    for(*row = 0;*row < N;row++){
       for(*col = 0;*col < N;col++){
         if(board[*row][*col] == UNASSIGNED){
           printf("Empty cell found..\n");
           return true;
         }
       }
     }
  //Returns false if no empty cells were found
  printf("No empty cells found, exiting...\n");
  return false;
}

//Checks that the number is valid and there will be no duplicates in the same grid,row,col
//the num and location of the num in the board(row,col) are given as parameters
bool is_valid_num(int board[N][N], int *row, int *col, int num){
    int r = *row - *row % 3;
    int c = *col - *col % 3;
    printf("%d and %d\n", r, c);
     //check the row, returns false if duplicate found
     for(int i = 0;i < N; i++){
       if(board[*row][i] == num){
         printf("Duplicate found in the same row!\n");
         return false;
       }
     }

     //check the columns, returns false if duplicate found
     for(int j = 0;j < N; j++){
       if(board[j][*col] == num){
         printf("Duplicate found in the same column!\n");
         return false;
       }
     }

     //check the 3x3 sub-grids for duplicates
     for(int a = r; a < r+3;a++){
       for(int b = c; b < c+3;b++){
         if(board[a][b] == num){
           printf("Duplicate found in the same 3x3 grid!\n");
           return false;
         }
       }
     }
printf("no duplicates found...\n");
return true;
}


bool solve(int board[N][N]){

  int row;
  int col;

  //If grid is full if means it's done and return true
  //if empty cell found, row and col are set on the location
  if(!find_empty_cell(board ,&row ,&col)){
    printf("Sudoku is finished!\n");
    return true;
  }

    for(int num = 1; num <= 9; num++){

      //If number is valid -> assign in cell and call solve on the new board...
      if(is_valid_num(board,&row,&col, num) == true){
        printf("Assigning value %d to grid location %d x %d\n", num, row, col);
        board[row][col] = num; //segmentation faultings?????
        //print_board(board);
        if(solve(board)){
          return true;
        }
        else{
          board[row][col] = UNASSIGNED;
          //print??
        }
      }
    }
  return false;
}


void print_board(int board[N][N]){

    for(int i = 0;i < 9;i++){
      if(i == 3 || i == 6){
        printf("+---------+---------+---------+\n");
      }
      printf("|");
      for(int j = 0;j < 9; j++){
        if(j == 2 || j == 5 || j == 8){
          printf(" %d |", board[i][j]);
        }
        else{
        printf(" %d ",board[i][j]);
        }
      }
      printf("\n");
    }

}
