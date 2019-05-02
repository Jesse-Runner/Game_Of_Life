// Jesse Runner
// February 28th, 2019
// This is the sequential implementation for Conway's game of life
// It uses a series of test data files to create different patterns after a certain amount of generations

#include<iostream>
#include<vector>
using namespace std;

class Gameoflife {

public:
vector<vector<int> > SimulateLife(vector<vector<int> > &board, int life_cycles); // used to run the game for as many generations as specified
};


vector<vector<int> > Gameoflife::SimulateLife(vector<vector<int> > &board, int life_cycles){

  int n;
  n = board.size(); // variable used to store the size of the board in one direction
  vector<vector<int> > board1; // vector used to workr with board to store neighboring cells for next generation
  board1.resize(n);
  for (int i=0;i<n;i++)
    board1[i].resize(n);

  for(int x = 0; x < life_cycles; x++){ // for loop to run through the individual generations
      for(int i = 0; i < n; i++){ // loop that runs through the rows
        for(int j = 0; j < n; j++){ // loop that runs through the coloumns
            int neighbors = 0; // value used to store amount of neighbors near a cell
            if(board[(i + 1) % n][j] == 1 || board[(i + 1) % n][j] == 2) // one down
                neighbors++;
            if(board[(i + 1) % n][(j + 1) % n] == 1 || board[(i + 1) % n][(j + 1) % n] == 2)  // down and to the right
                neighbors++;
            if(board[i][(j + 1) % n] == 1 || board[i][(j + 1) % n] == 2) //  one to the right
                neighbors++;
            ///// now to values that can be negative

            // this is number 2 from homework
            if(i - 1 == -1){
                if(board[(n - 1) % n][j] == 1 || board[(n - 1) % n][j] == 2) // checks one up if i would be negative after subtracting 1
                    neighbors++;
            }
            else{
                if(board[(i - 1) % n][j] == 1 || board[(i - 1) % n][j] == 2) // checks one up if i would not be negative after subtracting 1
                    neighbors++;
            }
            // end of number 2 from homework

            // this is number 3 from the homework
            if(i - 1 == -1){
                if(board[(n - 1) % n][(j + 1) % n] == 1 || board[(n - 1) % n][(j + 1) % n] == 2) // checks one up and one to the right if i would be negative after subtracting 1
                    neighbors++;
            }
            else{
                if(board[(i - 1)% n][(j + 1) % n] == 1 || board[(i - 1)% n][(j + 1) % n] == 2) // checks one up and one to the right (diagonal up right) if i - 1 isnt negative
                    neighbors++;
            }
            // end of number 3 from the Homework

            // this is number 4 from homework sheet
            if(i - 1 == -1){
              if(j - 1 == -1){
                    if(board[(n - 1) % n][(n - 1) % n] == 1 || board[(n - 1) % n][(n - 1) % n] == 2){ // if both i - 1 and j - 1 are -1, this checks one up and one to the left
                        neighbors++;
                      }
              }
              else{
                    if(board[(n - 1) % n][(j - 1)% n] == 1 || board[(n - 1) % n][(j - 1)% n] == 2)  // if i - 1 is negative 1 but j - 1 isnt, check one up and one to the left
                        neighbors++;
              }
            }
            else{
                if(j - 1 == -1){
                      if(board[(i - 1) % n][(n - 1) % n] == 1 || board[(i - 1) % n][(n - 1) % n] == 2) // if i - 1 isnt negative but j - 1 is negative, check one up and one the the left
                          neighbors++;
                }
                else{
                      if(board[(i - 1) % n][(j - 1) % n] == 1 || board[(i - 1) % n][(j - 1) % n] == 2) // if neither i - 1 or j - 1 is a negative value, check one up and one to the left
                          neighbors++;
                }
            }
            // end of number 4

            // this is number 6 from homework
            if( j - 1 == -1){
                if(board[(i + 1) % n][(n - 1) % n] == 1 || board[(i + 1) % n][(n - 1) % n] == 2) // checks one down and one to the left if j - 1 is a negative value
                    neighbors++;
            }
            else{
                if(board[(i + 1) % n][(j - 1) % n] == 1 || board[(i + 1) % n][(j - 1) % n] == 2)      // checks one down and one to the left is j - 1 is not a negative value
                    neighbors++;
            }
            // end of number 6 from homework

            // this is number 8 from the homework
            if(j - 1 == -1){
                if(board[i][(n - 1) % n] == 1 || board[i][(n - 1) % n] == 2)
                    neighbors++;
            }
            else{
                if(board[i][(j - 1) %n] == 1 || board[i][(j - 1) %n] == 2)
                    neighbors++;
            }
            // this is the end of number 8 from the homework

            if(board[i][j] == 2){ // checks to see if the value of a cell is 2, if it is then it remains 2
                  board1[i][j] = 2;
            }
            else{
              if(board[i][j] == 1){ // checks to see if a cell is alive and it remains alive if it has 2 or 3 neighbors
                  if(neighbors == 2 || neighbors == 3){
                      board1[i][j] = 1;
                  }
              }
              if(neighbors <= 1) // if zero or one of the cells neighbors are alive, set piece to 0
                board1[i][j] = 0;
              if (neighbors == 3) // if a cell has exactly three neighbors it is born
                board1[i][j] = 1;
              if(neighbors >= 4)  // if four or more of the neighbors are alive, the cell dies (set to 0)
                board1[i][j] = 0;
            }
        }
      }
      board = board1; // sets board equal to board1 for the next generation
    }
  if(life_cycles == 0)
  return board;
  else
  return board1;
}
