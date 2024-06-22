#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>   // For numeric_limits
#include <cctype>   // For isdigit

using namespace std;

// Function to get a valid integer input from the user
int getUserInput(string prompt) {
    int input;
    while (true) {
        cout << prompt;
        cin >> input;

        // Check if input is a valid integer
        if (cin.fail()) {
            cin.clear();    // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
            cout << "Invalid input. Please enter a valid integer." << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear input buffer
            break;
        }
    }
    return input;
}

// Function to play one round of the game
bool playGame(int difficulty) {
    srand(static_cast<unsigned int>(time(0)));  // Seed for random number generator
    int secretNumber = rand() % (difficulty * 10) + 1;  // Generate a random number based on difficulty
    int guess;
    int attempts = 0;

    cout << "I have chosen a number between 1 and " << difficulty * 10 << ". Guess what it is." << endl;

    while (true) {
        guess = getUserInput("Enter your guess: ");
        attempts++;

        if (guess == secretNumber) {
            cout << "Congratulations! You guessed the number " << secretNumber << " in " << attempts << " attempts." << endl;
            return true;  // Player guessed correctly
        } else if (guess < secretNumber) {
            cout << "Too low! Try again." << endl;
        } else {
            cout << "Too high! Try again." << endl;
        }
    }
}

// Function to display game results and handle replay
void displayResults(int score) {
    cout << "Game Over!" << endl;
    cout << "Your final score is: " << score << " points." << endl;
}

int main() {
    int difficulty;
    int score = 0;
    bool playAgain = true;

    cout << "Welcome to the Guess the Number game!" << endl;

    while (playAgain) {
        difficulty = getUserInput("Choose difficulty level (1 - 5): ");
        if (difficulty < 1 || difficulty > 5) {
            cout << "Invalid difficulty level. Please choose between 1 and 5." << endl;
            continue;
        }

        if (playGame(difficulty)) {
            score += difficulty * 10;  // Increase score based on difficulty level
        }

        char choice;
        while (true) {
            cout << "Do you want to play again? (Y/N): ";
            cin >> choice;
            choice = toupper(choice);

            if (choice == 'Y') {
                playAgain = true;
                break;
            } else if (choice == 'N') {
                playAgain = false;
                break;
            } else {
                cout << "Invalid choice. Please enter Y or N." << endl;
            }
        }
    }

    displayResults(score);

    return 0;
}

