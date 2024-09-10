#include <iostream>
#include "../include/utils.h"
#include "../include/input.h"

using namespace std;

int main() {
    int choice;
    string filename = "../data/investments.csv";

    do {
        cout << "-----------------------------------\n";
        cout << "  Welcome to Financial Portfolio Optimization\n";
        cout << "-----------------------------------\n";
        cout << "Please choose an option:\n";
        cout << "1. Insert new data into investments\n";
        cout << "2. Get investment suggestions\n";
        cout << "3. Check all available investments\n";
        cout << "4. Exit\n";
        cout << "Enter your choice (1-4): ";
        cin >> choice;

        switch (choice) {
            case 1:
                insertDataIntoCSV(filename);
                break;
            case 2:
                getSuggestionsMenu();
                break;
            case 3:
                displayAllInvestments(filename);
                break;
            case 4:
                cout << "Exiting the program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 4.\n";
        }
        cout << endl;
    } while (choice != 4);

    return 0;
}
