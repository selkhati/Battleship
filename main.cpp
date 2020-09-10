/* CSCI 261 Final Project Source Code: Battleship
 * Author: Sherif Elkhatib
 *
 * Battleship is a tactical turn-by-turn guessing game where the player analyzes a 10x10 grid
 * in search of enemy ships hidden beneath the surface. Player will guess where on the grid
 * the enemy’s ships are located. In the hidden grid, there are (1) 1x5 ship, (1) 1x4 ship,
 * (2) 3 x 1 ships, and (1) 2x1 ship. If a player/Computer guess is incorrect, the grid spot
 * is marked with an “*”. If the player/Computer guesses correctly, the grid spot is marked
 * with an “X.” First one to sink all the enemy ships wins.
 * */

#include <iostream>
#include "Board.h"
using namespace std;

int main() {
    Board Player1 ('!');
    Board Computer;

    Player1.writeAnswerKey("player1AnswerKey.txt");    // Computer grid is printed to answerKey file
    Computer.writeAnswerKey("computerAnswerKey.txt");    // Computer grid is printed to answerKey file

    cout << endl << "Now that the boards are set, let's blow some s*** up!" << endl;

    do {
        Player1.shootSomeStuff(Computer);
    } while (!Player1.isGameOver());

    return 0;
}
/* Procedural Description
 * Name all the ships - DONE
	Store the ship names as strings - DONE
	Store the ship sizes as integers - DONE
Set-up the board
	Create a 10x10 2D array to represent the board - DONE
	Assign the array all zeroes (prior to placing the ships) - DONE

Place the ships
	f(X,Y,length,direction) - DONE
What is the starting point for this ship? [X,Y] - DONE
How many unit spaces does the ship take up (length)? - DONE
Is the ship aligned horizontally (right, or +X) or vertically (down, or +Y)? - DONE
Check: Does the ship run off the board? (if X or Y is <0 or >9) - DONE
Check: Does the ship run into another ship? (if [X][Y] != 0) - DONE
Store the spots covered by the ship in the 2D array using for loop - DONE

Begin the game
	User will enter coordinates on the grid to “fire” on [X,Y] - DONE
		Are these valid coordinates? - DONE
Has user entered these coordinates before? - DONE
	Create a bool function to tell us if a certain spot [X,Y] on the board contains a ship - DONE
Does this register as a hit? - DONE
		No? Update the mark on the board as a miss - DONE
Yes? Update the mark on the board and count a hit - DONE
			Is that the last hit to register for that ship? - DONE
				If so, “you sunk [this] ship” - DONE
			Once all ships are sunk, game won. - DONE

 */



/*
Your program must use at least one original class, written specifically for this project. - DONE
Your custom class must encapsulate some important data/functionality of your program. - DONE
Your custom class must have some data/functions that are private. - DONE
Your custom class must have a well-defined public interface. - DONE
Your custom class must be defined and declared in separate files. - DONE
Your program must use at least one array (one-dimensional or two-dimensional). - DONE

Your program must make use of File I/O Data may either be read from or written to a file, or both. - DONE
Please place your data file in the same directory as your main.cpp. - DONE

Your program must use functions where appropriate. - DONE

Your program must use constants where appropriate. - DONE

Your project must make use of ample commenting. - DONE

Your program must adhere to our CSCI 261 style guidelines. - DONE

Create a text file called final.txt - DONE

 */