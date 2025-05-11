#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to display the welcome message
void displayWelcomeMessage() {
    cout << "\n***************************************\n";
    cout << "*                                     *\n";
    cout << "*    WELCOME TO THE NUMBER GUESSING   *\n";
    cout << "*              GAME!                  *\n";
    cout << "*                                     *\n";
    cout << "***************************************\n";
    cout << "\nI have selected a random number between 1 and 100.\n";
    cout << "Your goal is to guess the number. I'll provide hints like 'Too High!' or 'Too Low!' to guide you.\n";
    cout << "Good luck!\n";
    cout << "***************************************\n\n";
}

// Function to display the congratulations message
void displayCongratsMessage(int attempts, int numberToGuess) {
    cout << "\n***************************************\n";
    cout << "*                                     *\n";
    cout << "*      CONGRATULATIONS! YOU WON!      *\n";
    cout << "*                                     *\n";
    cout << "***************************************\n";
    cout << "\nYou've successfully guessed the correct number: " << numberToGuess << "!\n";
    cout << "It took you " << attempts << " attempts.\n";
    cout << "\nGreat job! Thanks for playing!\n";
    cout << "***************************************\n";
}

int main() {
    char playAgain; // Variable to store user's choice to play again

    do {
        // Initialize random seed
        srand(time(0));

        int numberToGuess = rand() % 100 + 1; // Random number between 1 and 100
        int playerGuess = 0;
        int attempts = 0;

        // Display welcome message
        displayWelcomeMessage();

        // Game loop
        while (playerGuess != numberToGuess) {
            cout << "-----------------------------------------\n";
            cout << "Enter your guess: ";
            
            // Check if input is valid (an integer)
            while (!(cin >> playerGuess)) {
                cout << "Invalid input! Please enter a valid number.\n";
                // Ignore the incorrect input
                cout << "Enter your guess: ";
            }

            attempts++;

            // Check the player's guess and give feedback
            if (playerGuess < numberToGuess) {
                cout << "Too low! Try again.\n";
            } else if (playerGuess > numberToGuess) {
                cout << "Too high! Try again.\n";
            } else {
                // Display congratulations message when guessed correctly
                displayCongratsMessage(attempts, numberToGuess);
            }
        }

        // Ask the player if they want to play again
        cout << "\nWould you like to play again? (y/n): ";
        cin >> playAgain;

        // Handle invalid input for play-again choice
        while (playAgain != 'y' && playAgain != 'n') {
            cout << "Invalid input! Please enter 'y' to play again or 'n' to quit: ";
            cin >> playAgain;
        }

    } while (playAgain == 'y'); // Repeat the game if player chooses 'y'

    cout << "Thanks for playing! Goodbye!" << endl;

    return 0;
}
