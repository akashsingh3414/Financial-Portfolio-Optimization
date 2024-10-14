#include <iostream>
#include "../include/utils.h"
#include "../include/input.h"
#include "../include/output.h"
#include "../include/dataTypes.h"
#include <limits>

using namespace std;

// ANSI color codes for vibrant visuals
const string RED = "\033[31m";         // Red text
const string GREEN = "\033[32m";       // Green text
const string YELLOW = "\033[33m";      // Yellow text
const string BLUE = "\033[34m";        // Blue text
const string CYAN = "\033[36m";        // Cyan text
const string WHITE = "\033[37m";       // White text
const string RESET = "\033[0m";        // Reset color

Constraints inputMenu() {
    Constraints constraints = getUserConstraints();
    return constraints;
}

int main() {
    int choice;
    string filename = "data\\investments.csv";

    do {
        cout << "\n";
        cout << "\t\t\t--------------------------------------------------------------\n";
        cout << "\t\t\t" << ".......Welcome to Financial Portfolio Optimization Tool......." << "\n";
        cout << "\t\t\t--------------------------------------------------------------\n\n";
        cout << "\t\t\t\t" << CYAN << "Please choose an option:" << RESET << "\n\n";
        cout << "\t\t\t\t" << YELLOW << "1. Insert new data into investments" << RESET << "\n";
        cout << "\t\t\t\t" << YELLOW << "2. Get investment suggestions" << RESET << "\n";
        cout << "\t\t\t\t" << YELLOW << "3. Check all available investments" << RESET << "\n";
        cout << "\t\t\t\t" << YELLOW << "4. Plot Average Return, Average Cost & Profit Graph" << RESET << endl;
        cout << "\t\t\t\t" << YELLOW << "5. EXIT" << RESET << "\n";
        cout << "\n\t\t\t\t" << BLUE << "Enter your choice (1-5): " << RESET;

        // Input validation
        while (!(cin >> choice) || choice < 1 || choice > 5) {
            // Clear the error flag set by invalid input
            cin.clear();
            // Ignore invalid input
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n\t\t\t\t" << RED << "Invalid choice. Please enter a valid number between 1 and 5: " << RESET;
        }
        
        cout << endl;

        switch (choice) {
            case 1:
                insertDataIntoCSV(filename);
                break;
            case 2: {
                Constraints inputConstraints = inputMenu();
                getSuggestionsMenu(inputConstraints);
                break;
            }
            case 3:
                displayAllInvestments(filename);
                break;
            case 4:
                plotInvestmentsVsReturn();
                break;
            case 5:
                cout << "\t\t\t\t" << RED << "Exiting the program. Goodbye!" << RESET << "\n";
                break;
            default:
                cout << "\t\t\t\t" << RED << "Invalid choice. Please enter a number between 1 and 5." << RESET << "\n";
        }
        cout << endl;
    } while (choice != 5);

    return 0;
}
