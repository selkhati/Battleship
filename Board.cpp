//
// Created by Sherif Elkhatib on 8/8/20.
//
#include <iostream>
#include <fstream> // Used for file output
#include <iomanip> // Used for setw() function
#include <ctime>   // Used for time()
#include "Board.h"
using namespace std;

/** Default constructor
 *  In the default constructor, the board is set up to randomly/auto-generate the board.
 */
Board::Board() {
    randomSetup = true;
    placeShips();
}

/** Non-default constructor. The user gets to choose whether to randomly set up the baord or do it themselves
 *
 * @param placementType represents the user choice of which set-up style they want to use
 */
Board::Board(char placementType) {
    welcome();                  // Reminds the user of what valid entries look like.

    cout << "Let's set up your board. Enter any character to continue or enter 'R' to randomize: ";
    cin >> placementType;

    if (placementType == 'R') { // Player can choose to set the board up themselves or randomly
        randomSetup = true;
    } else {
        randomSetup = false;
    }

    placeShips();
}

/** welcome() function outputs a welcome message and lets the user know how to input values
 *
 */
void Board::welcome() {
    cout << "Thank you for playing Battleship!" << endl;
    cout << "Remember: When setting up the board, input your coordinates as integers from 0-9, separated by spaces." << endl << endl;
}

/** printBoard() function aligns the board with row and column headers.
 *  Cells in the output, which correspond a numeric value in the grid, output a character instead of the numeric one.
 *  Depending on the value within the grid, the printBoard() function outputs a unique character
 *  The output is aligned in a presentable format. This output does not affect the 2D grid array.
 *
 */
void Board::printBoard() {

    cout << endl;

    for (int i = 0; i < COLUMNS; i++) {            // Used to display column headers
        if (i == 0) {
            cout << setw (4) << right << i;
        } else {
            cout << setw (3) << right << i;
        }
    }
    cout << endl;

    for (int i = 0; i < ROWS; i++) {
        cout << setw(2) << left << i;          // Used to display the row header
        for (int j = 0; j < COLUMNS; j++) {
            char displayChar = '~';               // All "un-guessed" cells will be this by default
            if (grid[j][i] == 7) {                // 7 means that cell is a correct strike. j = X, i = Y
                displayChar = 'X';
            } else if (grid[j][i] == 9) {         // 9 means that cell is an incorrect shot
                displayChar = '*';
            }
            cout << " " << displayChar << " ";    // Displays the [i][j]th element in the array
        }
        cout << endl;                             // Ends the line to go to the next row
    }
}

/** placeShips() function sets up the board for an object of the Board class.
 *  There is a loop that follows placement for auto-placement and one for manual entry.
 *  Variables used to place the ships are only used within this function, so I left them out of the .h file
 *
 */
void Board::placeShips() {

    int startX;         // Corresponds to the row the ship's bow is located
    int startY;         // Corresponds to the column the ship's bow is located
    char direction;     // Does the ship lay vertically or horizontally
    int length;         // Relates to how many units each ship takes up
    srand(time(0));     // Seed random to time
    rand();             // Throw away first value assigned to time

    for (int numShip = 0; numShip < 5; numShip++) { // Execute loop for each ship
        length = shipSize[numShip];     // Length is not user-defined. It corresponds to the index of shipSize array
        shipName = ships[numShip];      // Name is not user-defined. It corresponds to the index of ships array

        do {
            if (randomSetup) {
                startX = rand() % 10;   // Starting point [X,Y] is a random number between 0 and 9
                startY = rand() % 10;

                int dir = rand() % 2;   // Direction can be either VERT/down or HZ/right
                switch (dir) {          // Switch case where 0 = VERT/down & 1 = HZ/right
                    case 0:
                        direction = 'D';
                        break;
                    case 1:
                        direction = 'R';
                        break;
                    // Did not include a default case. Only 0 and 1 are possible outcomes
                }
            } else { // Manual entry of the ship placement
                cout << "Assign the " << shipName << " a starting [X,Y] coordinate: "; // Take in the ship's coordinates
                cin >> startX >> startY;
                while (!validateCoordinates(startX,startY)) { // Verify these coordinates
                    cout << "That is not a valid strike zone. Try again: ";
                    cin >> startX >> startY;
                }

                // Determine whether or not the ship will be aligned vertically or horizontally
                cout << "Will the ship be vertical or horizontal? Enter 'D' for DOWN or 'R' for RIGHT: ";
                cin >> direction;
                while ((direction != 'D') && (direction != 'R')) { // Make sure only valid entries are taken
                    cout << "Invalid. Choose 'R' for HZ/right or 'D' for VERT/down: ";
                    cin >> direction;
                }
            }
        // Validate the placement of the ship (whether auto or user-placed) before altering the grid.
        } while (!validatePlacement(shipName, startX, startY, length, direction));

        // Alter the grid by reassigning the values of the grid with the corresponding numerical value of the ship
        // A for loop increments each ship segment using the grid index and increment of the X or Y (direction-dependent)
        // The Placement Coordinates have been validated already so they won't overlap or run off the board
        if (direction == 'D') {
            for (int segment = 0; segment < length; segment++) {
                grid[startX][startY + segment] = (numShip + 1);
            }
        }

        // Same function but increments the X value if a horizontal orientation is chosen
        if (direction == 'R') {
            for (int segment = 0; segment < length; segment++) {
                grid[startX + segment][startY] = (numShip + 1);
            }
        }
    }
}

/** validatePlacement() function tests two important fail points of the coordinates chosen.
 *  1. Does the ship run off the board? Confirm that X (or Y, depending on orientation) + length <= 9
 *  2. Does the ship intersect with another ship? Confirm that all prospective cells are assigned 0.
 *
 * @param shipName is passed in to give the user feedback which ship is being placed incorecttly
 * @param startX is passed as the chosen X coordinate to evaluate
 * @param startY is passed as the chosen Y coordinate to evaluate
 * @param length is passed as the length of the ship being evaluated
 * @param direction is passed as the orientation of the ship
 * @return True if the coordinates chosen are valid given the size and orientation of the ship
 *         False if the coordinates chosen are invalid given the size and orientation of the ship
 */
bool Board::validatePlacement(const string& shipName, int startX, int startY, int length, char direction) {

    // Check: Does the ship run off the board given the starting point and orientation?
    if ((direction == 'D') && ((length + startY) > 9)) {
        if (!randomSetup) { // Skips the error message if random placement is chosen
            cout << "The " << shipName << " won't fit on the board there. Pick again." << endl;
        }
        return false;
    }

    if ((direction == 'R') && ((length + startX) > 9)) {
        if (!randomSetup) { // Skips the error message if random placement is chosen
            cout << "The " << shipName << " won't fit on the board there. Pick again." << endl;
        }
        return false;
    }

    // Check: Does placing the ship on the board run into any other ships?
    if (direction == 'D') {
        for (int segment = 0; segment < length; segment++) {
            if (grid[startX][startY + segment] != 0) {
                if (!randomSetup) { // Skips the error message if random placement is chosen
                    cout << "The " << shipName << "can't go there. There's already a ship there" << endl;
                }
                return false;
            }
        }
    }

    if (direction == 'R') {
        for (int segment = 0; segment < length; segment++) {
            if (grid[startX + segment][startY] != 0) {
                if (!randomSetup) { // Skips the error message if random placement is chosen
                    cout << "The " << shipName << "can't go there. There's already a ship there" << endl;
                }
                return false;
            }
        }
    }

    return true; // If it doesn't fail these validation tests, the placement is valid.
}

/** printKey() function opens up an output file named "answerKey.txt"
 *  where the grid will be output as assigned (no cover up characters),
 *  with values 1-5 corresponding to each ship along it's length
 *
 */
void Board::writeAnswerKey(string filename) {
    ofstream answerKey;                 // outfile file type named answerKey
    answerKey.open(filename); // opens the answerKey text file
    if (!answerKey.is_open()) {         // Error out if file cannot open
        cerr << "The output file could not open.";
        exit(0);
    }

    for (int i = 0; i < COLUMNS; i++) {            // Used to display column headers
        if (i == 0) {
            answerKey << setw (4) << right << i;
        } else {
            answerKey << setw (3) << right << i;
        }
    }
    answerKey << endl;

    for (int i = 0; i < ROWS; i++) {
        answerKey << setw(2) << left << i;           // Used to display the row header
        for (int j = 0; j < COLUMNS; j++) {
            answerKey << " " << grid[j][i] << " ";    // Displays the [i][j]th element in the array
        }
        answerKey << endl;                              // Ends the line to go to the next row
    }

    answerKey.close(); // close the output file
}

/** someSomeStuff() function is the actual gameplay of Battleship.
 *  It prompts the user for a [X][Y] coordinate to guess, then validates the coordinates are in the strike zone.
 *  The function evaluates if the shot has been fired on those coordinates before.
 *  If hit did not strike, report a miss. If hit struck, report a hit.
 *  If all the segments of the ship have been hit, report that ship as sunk.
 *  Print the board out
 *
 * @param opponent is an object of class type Board representing the board that is being altered
 */
void Board::shootSomeStuff(Board& opponent) {

    cout << "Input the [X,Y] coordinates you want to fire upon: ";
    cin >> xGuess >> yGuess;
    while (!validateCoordinates(xGuess, yGuess)) { // Checks for valid coordinate
        cin >> xGuess >> yGuess;
    }

    if (opponent.grid[xGuess][yGuess] == 0) {        // A '0' means that there is nothing there. The user missed.
        cout << "Sorry, that was a miss." << endl;
        opponent.grid[xGuess][yGuess] = 9;           // Reassign cell the value 9, signifying it is a previously-guessed miss
    } else if (opponent.grid[xGuess][yGuess] >= 1 || opponent.grid[xGuess][yGuess] <= 5) { // Values 1-5 correspond to a new ship hit
        cout << "Affirmative strike!" << endl;

        for (int numShip = 0; numShip < 5; numShip++) { // Check the cell to see which shit was hit
            if (opponent.grid[xGuess][yGuess] == (numShip + 1)) {
                opponent.numHits[numShip]++; // Increments the value in the numHits array corresponding with the ship hit
                if (opponent.numHits[numShip] == opponent.shipSize[numShip]) { // Once the value in numHits = shipSize, that ship is sunk
                    cout << "You've sunk the " << opponent.ships[numShip] << "!" << endl;
                }
            }
        }
        opponent.grid[xGuess][yGuess] = 7; // The hit cell is reassigned 7, signifying it is a previously-struck hit
    }
    opponent.printBoard(); // prints the board with cover-up characters
}

bool Board::validateCoordinates(int xGuess, int yGuess) {

    if (xGuess < 0 || xGuess > 9 || yGuess < 0 || yGuess > 9) {
        cout << "That is not a valid strike zone. Try again:  ";
        return false;
    }

    if (grid[xGuess][yGuess] == 9) { // used for values that have been incorrectly guessed already
        cout << "You've guessed that coordinate already. Try again: ";
        return false;
    }

    if (grid[xGuess][yGuess] == 7) { // used for cells that have marked as hits before
        cout << "You've already struck there before. Try again: ";
        return false;
    }

    return true;
}

/** isGameOver() is a boolean function to help determine if the game has ended
 *
 * @return True if all the ships have been sunk
 *         False if not
 */
bool Board::isGameOver() {

    for (int numShip = 0; numShip < 5; numShip++) {     // Evaluate each ship
        if (numHits[numShip] == shipSize[numShip]) {    // If numHits = shipSize (AKA "is sunk"), continue the loop
            continue;
        } else {
            return false;                               // If any of the ships aren't sunk, return false
        }
    }
    // Congratulates the winner if all the ships have been sunk and return true
    cout << "You've sunk all the ships and won the game! Congratulation!" << endl;
    return true;

}