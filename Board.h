//
// Created by Sherif Elkhatib on 8/8/20.
//
#include <string>
using namespace std;

#ifndef BATTLESHIPPROJECT_BOARD_H
#define BATTLESHIPPROJECT_BOARD_H


class Board {
public:
    Board();                        // Default constructor
    Board(char);                    // Non-default constructor, takes in string to say whether or not board is set up randomly
    void printBoard();              // Prints the state of the board with cover-up characters
    void placeShips();              // Prompts the placement of (5) ships on the board
    void shootSomeStuff(Board&);    // Starts gameplay. Callee is prompted to guess target's board
    bool isGameOver();              // Evaluates if the game is over
    void writeAnswerKey(string);    // Outputs the location of all the ships in a formatted .txt file

private:
    void welcome();                     // Introduction function to the game
    static const int ROWS = 10;
    static const int COLUMNS = 10;
    int grid [ROWS] [COLUMNS] = {0,0};  // Initialized grid to alter through the placeShips() function

    // Constant arrays that represent the ship names and ship sizes used in various functions
    const string ships[5] = {"Cruiser", "Battleship", "Destroyer", "Submarine", "Patrol Boat"};
    const int shipSize[5] = {5, 4, 3, 3, 2};
    int numHits[5] = {0};               // Initialized array representing the number of hits on each ship

    bool validateCoordinates (int, int);
    bool validatePlacement(const string&, int, int, int, char);

    bool randomSetup;
    string shipName;
    int xGuess;
    int yGuess;

    };


#endif //BATTLESHIPPROJECT_BOARD_H
