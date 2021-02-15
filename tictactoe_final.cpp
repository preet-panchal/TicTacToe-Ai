// Preet Panchal
// 100707094
// CSCI1060U - LAB06
// CRN:43916
// November 01, 2020

//TIC-TAC-TOE [game]

#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>

using namespace std;

const int SIZE = 3;

void displayBoard(string b[][SIZE]);
bool userFirst();
bool currentPlayerWon(string b[][SIZE], string symbol);
void generateComputerMove(string gBoard[SIZE][SIZE], int &row, int &col); 

int main() {
  //construct board
  string board[SIZE][SIZE];

  int position_id = 1;
  for (int i=0; i< SIZE; i++) {
    for (int j=0; j < SIZE; j++) {
        board[i][j] = to_string(position_id);
      /*  stringstream ss;
        ss << position_id;
        board[i][j] = ss.str();
        */position_id++;
    }
  }

  //Initial game output
  cout << "Welcome to Tic-Tac-Toe" << endl;

  bool userTurn = userFirst();
  if (userTurn == true) {
    cout << "Player goes first!" << endl;
  } else {
    cout << "Computer goes first!" << endl;
  }

  //Loop for turn taking in game
  int positionsRemaining = SIZE * SIZE;
  bool userWon = false;
  bool computerWon = false;

  int sum_turns = 0; 
  while ((positionsRemaining > 0)
        && (!userWon) && (!computerWon)) {
      displayBoard(board);

      //User's turn
      if (userTurn) {
        bool validMove = false;
        while (!validMove) {
          int position_id;
          cout << "Enter a position: ";
          cin >> position_id;
          if ((position_id <= (SIZE*SIZE))
              && (position_id > 0)) {
            int row = (position_id-1)/SIZE;
            int col = (position_id-1)%SIZE;
            //cout << "row = " << row << " col = " << col << endl;
            if ((board[row][col] != "X")
                && (board[row][col] != "O")) {
                  board[row][col] = "X";
                  validMove = true;
            } else {
              cout << "Position already used. Try again." << endl;
            }

          } else {
            cout << "Position invalid. Try again." << endl;
          }
        }
        sum_turns++; 
        positionsRemaining--;
        userWon = currentPlayerWon(board, "X");
        userTurn = false;
      }

      //Computer's turn
      else {
        //bool validMove = false;
        //while (!validMove) {
            //int row = rand()%SIZE;
            //int col = rand()%SIZE;
            //if ((board[row][col] != "X")
                //&& (board[row][col] != "O")) {
                  //board[row][col] = "O";
                  //validMove = true;
            //}
        //}
        int row, col; 
        //if (sum_turns == 0) {
          //board[1][1] = "O"; 
        //}
        //else{
        generateComputerMove(board, row, col);
        //}
        sum_turns++; 
        positionsRemaining--;
        computerWon = currentPlayerWon(board, "O");
        userTurn = true;
      }
  }

  //Display game result
  displayBoard(board);
  if (userWon) {
    cout << "Congratulations! You have won!" << endl;
  } else if (computerWon) {
    cout << "The computer has won. Try again." << endl;
  } else {
    cout << "Out of moves. Try again." << endl;
  }
  return 0;
}

void displayBoard(string b[][SIZE]) {
  cout << "Tic-tac-toe board:" << endl << endl;
  for (int i=0; i < SIZE; i++) {
    for (int j=0; j < SIZE; j++) {
        cout << b[i][j] << "\t";
    }
    cout << endl;
  }
  cout << endl;
}

bool userFirst() {
  //set seed for random number generation
  srand(time(NULL));

  //generate a random number
  //0 for computer
  //1 for user
  int num = rand()%2;
  if (num == 0) {
    return false;
  }
  return true;
}

//Return true if player/computer with symbol (X or O) has won
bool currentPlayerWon(string b[][SIZE], string symbol) {
  //Horizontal case
  //Loop through each row
  for (int i=0; i < SIZE; i++) {
    bool rowWinDetected = true;
    //Check all positions in row and see if they are the same symbol
    for (int j = 0; j < SIZE; j++) {
      if (b[i][j] != symbol) {
        rowWinDetected = false;
      }
    }
    if (rowWinDetected) {
      return true;
    }
  }

  //Vertical case
  //Loop through each column
  for (int i=0; i < SIZE; i++) {
    bool colWinDetected = true;
    //Check all positions in column and see if they are the same symbol
    for (int j = 0; j < SIZE; j++) {
      if (b[j][i] != symbol) {
        colWinDetected = false;
      }
    }
    if (colWinDetected) {
      return true;
    }
  }

  //Diagonal case #1
  bool diagonal1WinDetected = true;
  for (int i=0; i < SIZE; i++) {
    if (b[i][i] != symbol) {
      diagonal1WinDetected = false;
    }
  }
  if (diagonal1WinDetected) {
    return true;
  }

  //Diagonal case #2
  bool diagonal2WinDetected = true;
  for (int i=0; i < SIZE; i++) {
    if (b[(SIZE-1)-i][i] != symbol) {
      diagonal2WinDetected = false;
    }
  }
  if (diagonal2WinDetected) {
    return true;
  }

  //otherwise win not diagonal2WinDetected
  return false;

}

void generateComputerMove(string gBoard[SIZE][SIZE], int &row, int &col) {
  
  //initalizes number of turns to 1 (first turn)
  int numTurns = 1; 
  //counts how many Xs and Os on table to determine nunber of turns taken place
  for (int i=0; i < SIZE; i++) {
    for (int j=0; j < SIZE; j++) {
      if ((gBoard[i][j] == "X") || (gBoard[i][j] == "O")) {
        numTurns++; 
      }
    }
  }

  //if computer goes first, play position (1,1) for best possible first move
  if (numTurns == 1) {
    gBoard[1][1] = "O"; 
  }

  //for second turn, check if user plays  (1,1) 
  //if user does not play (1,1), computer plays (1,1)
  else if (numTurns == 2) {
    if (gBoard[1][1] != "X") {
      gBoard[1][1] = "O";
      return; 
    }
    //or the computer plays a random move if user already played (1,1)
    else {
      int ranRow = rand()%SIZE;
      int ranCol = rand()%SIZE;
      if ((gBoard[ranRow][ranCol] != "X") && (gBoard[ranRow][ranCol] != "O")) {
        gBoard[ranRow][ranCol] = "O";
        return; 
      }
    }
  }

  else {
    //horizontal block case
    for (int i=0; i < SIZE; i++) {
      //initializing number of Xs and Os to zero on horizontal 
      int numXH = 0; 
      int numOH = 0; 
      for (int j=0; j < SIZE; j++) { 
        if (gBoard[i][j] == "X") {
          numXH++; 

          //if there are 2 Xs on horizontal, computer blocks the user
          if (numXH == 2) { 
            for (int k=0; k < SIZE; k++) {
              for (int l=0; l < SIZE; l++) {
                if ((gBoard[i][l] != "X") && (gBoard[i][l] != "O")) {
                  gBoard[i][l] = "O";
                  return;  
                }
              }
            }
          }
        }

        //horizontal win case 
        else if (gBoard[i][j] == "O") {
          numOH++; 

          //if there are 2 Os on horizontal, computer plays the winning move on horizontal
          if (numOH == 2) {
            for (int k=0; k < SIZE; k++) {
              for (int l=0; l < SIZE; l++) {
                if ((gBoard[i][l] != "X") && (gBoard[i][l] != "O")) {
                  gBoard[i][l] = "O"; 
                  return; 
                }
              }
            }
          }
        }

      }
      if (numXH == 1) {

        //vertical block case 
        for (int i=0; i < SIZE; i++) {
          //initializing number of Xs and Os to zero on vertical
          int numXV = 0; 
          int numOV = 0; 
          for (int j=0; j < SIZE; j++) {
            if (gBoard[j][i] == "X") {
              numXV++; 

              //if there are 2 Xs on vertical, computer blocks the user
              if (numXV == 2) { 
                for (int k=0; k < SIZE; k++) {
                  for (int l=0; l < SIZE; l++) {
                    if ((gBoard[l][i] != "X") && (gBoard[l][i] != "O")) {
                      gBoard[l][i] = "O"; 
                      return; 
                    }
                  }
                }
              }
            }

            //vertical win case 
            else if (gBoard[j][i] == "O") {
              numOV++; 

              //if there are 2 Os on vertical, computer plays the winning move on vertical
              if (numOV == 2) {
                for (int k=0; k < SIZE; k++) {
                  for (int l=0; l < SIZE; l++) {
                    if ((gBoard[l][i] != "X") && (gBoard[l][i] != "O")) {
                      gBoard[l][i] = "O"; 
                      return; 
                    }
                  }
                }
              }
            }
          }

          if (numXV == 1) {

            //diagonal case #1 (1, 5, 9)
            //initializing number of Xs and Os to zero on diagonal case #1
            int numXD1 = 0; 
            int numOD1 = 0; 
            for (int i=0; i < SIZE; i++) {
              if (gBoard[i][i] == "X") {
                numXD1++; 

                //if there are 2 Xs on diagonal #1, computer blocks the user
                if (numXD1 == 2) {
                  for (int k=0; k < SIZE; k++) {
                    if ((gBoard[k][k] != "X") && (gBoard[k][k] != "O")) {
                      gBoard[k][k] = "O";   
                      return;                 
                    }
                  }
                }
              }
              //diagonal case #1 (1, 5, 9) win case 
              else if (gBoard[i][i] == "O") {
                numOD1++; 

                //if there are 2 Os on diagonal #1, computer plays the winning move on diagonal #1
                if (numOD1 == 2) {
                  for (int k=0; k < SIZE; k++) {
                    if ((gBoard[k][k] != "X") && (gBoard[k][k] != "O")) {
                      gBoard[k][k] = "O"; 
                      return; 
                    }
                    
                  }
                }
              }
            }

            if (numXD1 == 1) {

              //diagonal case #2 (7, 5, 3)
              //initializing number of Xs and Os to zero on diagonal case #2
              int numXD2 = 0; 
              int numOD2 = 0; 
              for (int i=0; i < SIZE; i++) {
                if (gBoard[(SIZE-1)-i][i] == "X") {
                  numXD2++;

                  //if there are 2 Xs on diagonal #2, computer blocks the user
                  if (numXD2 == 2) {
                    for (int k=0; k < SIZE; k++) {
                      if ((gBoard[(SIZE-1)-k][k] != "X") && (gBoard[(SIZE-1)-k][k] != "O")) {
                        gBoard[(SIZE-1)-k][k] = "O"; 
                        return; 
                      }
                    }
                  }
                }

                //diagonal case #2 (7, 5, 3) win case 
                else if (gBoard[(SIZE-1)-i][i] == "O") {
                  numOD2++; 

                  //if there are 2 Os on diagonal #2, computer plays the winning move on diagonal #2
                  if (numOD2 == 2) {
                    for (int k=0; k < SIZE; k++) {
                      if ((gBoard[(SIZE-1)-k][k] != "X") && (gBoard[(SIZE-1)-k][k] != "O")) {
                        gBoard[(SIZE-1)-k][k] = "O"; 
                        return; 
                      } 
                    }
                  }
                }
              } 
            }

          }

        }
      }

    }

    //if the computer checks all cases above and none are applicable, it plays random move
    bool validMove = false;
    while (!validMove) {
      int frow = rand()%SIZE;
      int fcol = rand()%SIZE;
      if ((gBoard[frow][fcol] != "X") && (gBoard[frow][fcol] != "O")) {
        gBoard[frow][fcol] = "O";
        validMove = true;
      }
    }
  }

  return;  
}