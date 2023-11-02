/**------------------------------------------
    Program 2: Great 13

    Course: CS 141, Spring 2023.
    System: macOs
    Author: Afsah Ahmed
 ---------------------------------------------**/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <map>
#include <string>
#include <vector>

/* Everything below this comment is starter code, and you are not
allowed to modify */

using namespace std;

// Function that displays the instructions to the user

void display_instructions()
{
    cout << "Class: CS 141" << endl
         << "Program 2: Great 13" << endl << endl
         << "Make a series of jumps until there is a single piece left" << endl
         << "anywhere on board. On each move you must jump an adjacent" << endl
         << "piece   into   an  empty  square,  jumping  horizontally," << endl
         << "vertically, or diagonally." << endl << endl
         << "Input of 'R' resets the board back to the beginning, and " << endl
         << "'X' exits the game." << endl;
}

// The internal representation of the board as an array. Do not modify directly.

char board[13]{};

/* These two functions are how you will get and set elements on the board. Only
use these two when changing, or reading the board. */

char get_element(char position)
{
    if ((position < 'A') || (position > 'M')) {
        cout << "Failed to get element at position " << position << endl
             << "Make sure the given position is an uppercase letter " << endl
             << "between A-M." << endl;
        exit(1);
    }
    return board[position - 'A'];
}

void set_element(char position, char value)
{
    if ((position < 'A') || (position > 'M')) {
        cout << "Failed to set element at postion " << position << endl
             << "Make sure the given position is an uppercase letter " << endl
             << "between A-M." << endl;
        exit(1);
    }
    board[position - 'A'] = value;
}

// print out the board with the legend on the right

void display_board()
{
    cout << endl;
    cout << setw(7) << "Board" << setw(12) << "Position" << endl;
    cout << setw(5) << board[0] << setw(11) << 'A' << endl
         << setw(3) << board[1] << ' ' << board[2] << ' ' << board[3]
         << setw(11) << "B C D" << endl
         << board[4] << ' ' << board[5] << ' ' << board[6] << ' '
         << board[7] << ' ' << board[8] << ' '
         << " E F G H I" << endl
         << setw(3) << board[9] << ' ' << board[10] << ' ' << board[11]
         << setw(11) << "J K L" << endl
         << setw(5) << board[12] << setw(11) << 'M' << endl;
    cout << endl;
}

/* This is the end of the starter code, and below is where you can
add your own code. Feel free to add helper functions or variables.
*/

/* forward declarations for the functions you will write later. This
is so the order of the function definitions, in this file,  does not
matter. */

void make_move();
void initialize_board();
bool game_over(string s);


int main()
{
    initialize_board();
    display_instructions();
    display_board();
    make_move();
    return 0;
}

//Function to see if the sequence they put is valid.
//Will output true if the sequence is possible (horizontal, vertical or diagonal)
bool checkValidInput(string s){
  char fromElement = get_element(s[0]), jumpElement = get_element(s[1]), toElement = get_element(s[2]);

  bool validMove = false;
  //List of possible moves
  string possibleValidMoves[32] = { "ACG", "ADI", "ABE",  "BCD", "BFJ", "BGL", "CGK", "DCB", "DHL", "DGJ", "EBA", "EJM", "EFG", "FGH", "GHI", "GFE", "GKM", "GCA", "HGF", "IHG", "IDA", "ILM", "JKL", "JFB", "JGD", "KGC", "LKJ", "LGB", "LHD", "MJE", "MKG", "MLI"};

  //Checking to see if the string is in the list of possible valid moves
  for(auto i : possibleValidMoves){
    if(i == s){
      validMove = true; //return true if string is valid
    }
  }
  if(!validMove){
    cout<<"*** Invalid sequence. Please retry."<<endl;
    return false;
  }

  //Checking to see if the source, jump and destination positions are possible
  if(fromElement != '#'){
    cout<<"*** Source needs a piece. Please retry."<<endl;
    return false;
  }
  if(jumpElement != '#'){
    cout<<"*** Must jump a piece. Please retry."<<endl;
    return false;
  }
  if(toElement != '.'){
    cout<<"*** Destination must be empty. Please retry."<<endl;
    return false;
  }
  //return true if all conditions for failure are avoided.
  return true;
}

void pieceJump(string s){
  char fromInput = s[0], jumpInput = s[1], toInput = s[2];

  //Setting the position of elements after move has been made
  set_element(fromInput, '.');
  set_element(jumpInput, '.');
  set_element(toInput, '#');
}

void make_move()
{
  string user_input;
  cout<<"Enter positions from, jump, and to (e.g. EFG): ";
  cin>> user_input;
  // Making the string all upper case
  for (auto & c: user_input) c = toupper(c); 

  // Game is in a loop
  while(true){
    
    //Checking for input 'X'
    if(game_over(user_input)){
      break;
    }
    
    //Checking to see how many letters are in input string.
    //Different lengths have different conditions.
    if(user_input.size() == 1){
      if (user_input == "R"){
        cout<<"Restarting game."<< endl;
        initialize_board();
        display_board();
      }
      else{
        cout<<"*** Invalid sequence. Please retry."<<endl;
        display_board();
      }
    }

    // If the length is 3, then we know that input is a sequence.
    else if(user_input.size() == 3){
      //Checking to see if all letters in the string are valid positions on the board
      if(user_input[0] < 'A' || user_input[0] > 'M' || user_input[1] < 'A' || user_input[1] > 'M' || user_input[2] < 'A' || user_input[2] > 'M'){
        cout<<"*** Given move has positions not on the board! Please retry."<<endl;
        display_board();
      }
        
      else{
          //Checking to see if the sequence is valid
          if(checkValidInput(user_input)){
            // If it is valid, then move the piece
            pieceJump(user_input);

            // Checking for if game is won
            if(game_over(user_input)){
              break;
            }
          }
          display_board();
        }
      }
    else {
      cout<<"*** Invalid sequence. Please retry."<<endl;
      display_board();
    }
    
    
    cout<<"Enter positions from, jump, and to (e.g. EFG): ";
    cin>>user_input;
    for (auto & c: user_input) c = toupper(c);
  }
  
}
   
  

bool game_over(string s)
{
    /* TODO: Write a function that returns true only if there is one
    one peg left, or if the user gives up by entering 'X' (or 'x')*/
    if(s == "X")
    {
      cout<<"Exiting."<<endl;
      return true;
    }

    // Counting the amount of pegs on the board, if there is one left then game is won.
    int countPeg = 0;
    for(auto& i:board){
      if(i == '#'){
        countPeg++;
      }
    }
  
    if(countPeg == 1){
      cout<<"Congrats you win!"<<endl;
      return true;
    }
  
    return false;
}

void initialize_board()
{
  int i;
  for (i = 0; i < 13; i++){
    set_element('A'+i,'#');
  }
  set_element('G','.');
}


