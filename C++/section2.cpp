/*
  Remember that you can compile and run your program with the following:
  To compile, use the following command: g++ main.cpp
  To run, use: ./a.out
*/



// read from file:

#include <fstream>
#include <iostream>
#include <string>

int main()
{
    std::ifstream my_file;
    my_file.open("files/1.board");

    if (my_file) {
      std::cout << "The file stream has been created!" << "\n";
      std::string line;
      while (getline(my_file, line)) { std::cout << line << "\n"; }
    }    
}



// string manipulation:
#include <vector>
#include <iostream>
using std::vector;
using std::cout;

int main() {
    // Initial Vector
    vector v {1, 2, 3};
    
    // Print the contents of the vector
    for (int i=0; i < v.size(); i++) {
      cout << v[i] << "\n";
    }
    
    // Push 4 to the back of the vector
    v.push_back(4);

    // Print the contents again
    for (int i=0; i < v.size(); i++) {
      cout << v[i] << "\n";
    }
    
}




/* Enums: 
C++ allows you to define a custom type which has values limited to a specific range you list or "enumerate". This custom type is called an "enum".

Suppose you were writing a program that stores information about each user's car, including the color. You could define a Color enum in your program, with a fixed range of all the acceptable values:

white
black
blue
red
This way, you can be sure that each color is restricted to the acceptable set of values.

Here is an example:
*/

#include <iostream>
using std::cout;

int main() 
{
    // Create the enum Color with fixed values.
    enum class Color {white, black, blue, red};

    // Create a Color variable and set it to Color::blue.
    Color my_color = Color::blue;

    // Test to see if my car is red.
    if (my_color == Color::red) {
        cout << "The color of my car is red!" << "\n";
    } else {
        cout << "The color of my car is not red." << "\n";
    }
}

/*
Example with a switch
Below is another example of an enum being used. Here, 
a custom type Direction is created with four possible values: kUp, kDown, kLeft, kRight. 
One of these values is then stored in a variable and used in the switch statement.
Using a prefix like k in enum constants is a common convention in C++ to indicate 
that the identifier is a constant. It stands for "constant" or "constant expression." 
This helps improve code readability and maintainability, making it clear that 
these values are not meant to be changed during the program's execution.
*/

#include <iostream>
using std::cout;

int main()
{
    enum class Direction {kUp, kDown, kLeft, kRight};

    Direction a = Direction::kUp;

    switch (a) {
      case Direction::kUp : cout << "Going up!" << "\n";
        break;
      case Direction::kDown : cout << "Going down!" << "\n";
        break;
      case Direction::kLeft : cout << "Going left!" << "\n";
        break;
      case Direction::kRight : cout << "Going right!" << "\n";
        break;
    }
}




/* 
Store the Board Using the State Enum
0   ⛰️   0   0   0   0
0   ⛰️   0   0   0   0
0   ⛰️   0   0   0   0
0   ⛰️   0   0   0   0
0   0    0   0  ⛰️   0
*/

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using std::cout;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;

enum class State {kEmpty, kObstacle};

// TODO: Change the return type to use auto or
// explicitly indicate vector<State>
vector<State> ParseLine(string line) {
    istringstream sline(line);
    int n;
    char c;
    // Change the variable type for row to be a vector<State>
    vector<State> row;
    while (sline >> n >> c && c == ',') {
        // Push back State::kEmpty if n is 0, and State::kObstacle otherwise
        row.push_back(n == 0 ? State::kEmpty : State::kObstacle);
    }
    return row;
}

// TODO: Modify the return type here as well. Just
// as above, the board will contain State objects
// instead of ints.
vector<vector<State>> ReadBoardFile(string path) {
    ifstream myfile(path);
    // Modify the board declaration to store State objects
    vector<vector<State>> board{};
    if (myfile) {
        string line;
        while (getline(myfile, line)) {
            // Parse each line into a vector<State>
            vector<State> row = ParseLine(line);
            board.push_back(row);
        }
    }
    return board;
}


// TODO: Modify the function signature below to accept
// cells with State type instead of int type.
string CellString(State cell) {
    switch(cell) {
        case State::kObstacle: return "⛰️   ";
        default: return "0   "; 
    }
}

void PrintBoard(const vector<vector<State>> board) {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            // Call CellString on each element of the board before streaming to cout
            cout << CellString(board[i][j]);
        }
        cout << "\n";
    }
}

int main() {
  auto board = ReadBoardFile("1.board");
  PrintBoard(board);
}

