#include <iostream>
#include "../include/utils.h"
#include "../include/input.h"

using namespace std;

Constraints inputMenu() {
    Constraints constraints = getUserConstraints();
    return constraints;
}

int main() {
    int choice;
    string filename = "../data/investments.csv";

    do {
        cout << "\n\t\t\t\t--------------------------------------------------------------\n";
        cout << "\t\t\t\t..........Welcome to Financial Portfolio Optimization.........\n";
        cout << "\t\t\t\t--------------------------------------------------------------\n\n";
        cout << "\t\t\t\t\tPlease choose an option:\n";
        cout << "\t\t\t\t\t1. Insert new data into investments\n";
        cout << "\t\t\t\t\t2. Get investment suggestions\n";
        cout << "\t\t\t\t\t3. Check all available investments\n";
        cout << "\t\t\t\t\t4. EXIT\n";
        cout << "\n\t\t\t\t\tEnter your choice (1-4): ";
        cin >> choice;

        switch (choice) {
            case 1:
                insertDataIntoCSV(filename);
                break;
            case 2:{
                Constraints inputConstraints = inputMenu();
                getSuggestionsMenu(inputConstraints);}
                break;
            case 3:
                displayAllInvestments(filename);
                break;
            case 4:
                cout << "\n\t\t\t\t\tExiting the program. Goodbye!\n";
                break;
            default:
                cout << "\n\t\t\t\t\tInvalid choice. Please enter a number between 1 and 4.\n";
        }
        cout << endl;
    } while (choice != 4);

    return 0;
}
