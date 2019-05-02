// Jesse Runner
// February 28th, 2019
// This is the parallel  implementation for Conway's game of life
// It uses a series of test data files to create different patterns after a certain amount of generations
// using pthreads and barriers 
#include<iostream>
#include<vector>
#include<thread>
#include<future>
#include<pthread.h>
using namespace std;


// My class used to implement a parallel solution to Conway's game of life

class Gameoflife {

public:
// function used to launch my threads into SimulateLife2
vector<vector<int> > SimulateLife(vector<vector<int> > &board, int life_cycles);
// func tion used to calculate the cell's in parallel using threads sent from SimulateLife
static void SimulateLife2(vector<vector<int> > &board, int life_cycles, int thread_id, int num_threads, int index, vector<pthread_barrier_t>& Barrier, vector<pthread_barrier_t>& Barrier2, vector<vector<int> > &board1); // will be used to calculate the board in parallel
};


vector<vector<int> > Gameoflife::SimulateLife(vector<vector<int> > &board, int life_cycles){

int num_threads = 4; // variable set to the amount of threads we'll be using for this project
int thread_id = 0; // thread id one to pass into function simulate life 2
vector<pthread_barrier_t> Barrier;
vector<pthread_barrier_t> Barrier2;
int b = 0;
Barrier.resize(life_cycles);
Barrier2.resize(life_cycles);
for(int m = 0; m < life_cycles; m ++){ // for loop used to intialize our two barreirs
    pthread_barrier_init(&Barrier[m], NULL, num_threads);
    pthread_barrier_init(&Barrier2[m], NULL, num_threads);

}
vector<vector<int> > board1; // our second board we'll pass that will ultimately be returned to the main for printing
  int n = board.size();
  board1.resize(n);
  for (int i=0;i<n;i++){
    board1[i].resize(n);
  }

    future<void> one = async(launch::async, SimulateLife2, ref(board), life_cycles, thread_id, num_threads, b, ref(Barrier),  ref(Barrier2), ref(board1));
    thread_id++; // increment thread_id so it represents thread id 2
    future<void> two = async(launch::async, SimulateLife2, ref(board), life_cycles, thread_id, num_threads, b, ref(Barrier),  ref(Barrier2), ref(board1));
    thread_id++; // increment thread_id so it represents thread id 3
    future<void> three = async(launch::async, SimulateLife2, ref(board), life_cycles, thread_id, num_threads, b, ref(Barrier),  ref(Barrier2), ref(board1));
    thread_id++; // increment thread_id so it represents thread id 4
    future<void> four = async(launch::async, SimulateLife2, ref(board), life_cycles, thread_id, num_threads, b, ref(Barrier),  ref(Barrier2), ref(board1));

    return board1;
}
void Gameoflife::SimulateLife2(vector<vector<int> > &board, int life_cycles, int thread_id, int num_threads, int index,vector<pthread_barrier_t> &Barrier, vector<pthread_barrier_t>& Barrier2, vector<vector<int> > &board1){
  int n;
  n = board.size(); // sets variable n to the size of the board in one direction (rows)


  for(int x = 0; x < life_cycles; x++){ // for loop to run throug the generations
      for(int i = thread_id; i < n; i+= num_threads){ // loop that runs through the rows
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

            if(board[i][j] == 2){ // if cell value is equal to 2, it remains
                  board1[i][j] = 2;
            }
            else{
              if(board[i][j] == 1){ // if the cell is alive and two or three of its neighbors are alive, it remains alive
                  if(neighbors == 2 || neighbors == 3)
                      board1[i][j] = 1;
              }
              if(neighbors <= 1) // if zero or one of the cells neighbors are alive, set piece to 0
                board1[i][j] = 0;
              if(neighbors == 3) // if exactly three of the neighbors are alive, a cell is born
                board1[i][j] = 1;
              if(neighbors >= 4)  // if four or more of the neighbors are alive, the cell dies (set to 0)
                board1[i][j] = 0;
            }
        }
      }

      pthread_barrier_wait(&Barrier[x]); // barrier set up to wait for threads to synchronize before board is set to equal
      board = board1;
      pthread_barrier_wait(&Barrier2[x]); // barrier set up so once function goes through every generation
    }                                     // one of the threads doesnt exit out and trigger an incomplete return value in simulatelife
}
