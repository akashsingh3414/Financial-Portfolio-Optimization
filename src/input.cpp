#include <iostream>
#include <vector>
#include "../include/input.h"
#include "../include/dataTypes.h"
#include "../include/knapsack.h"
#include "../include/utils.h"

using namespace std;

void getSuggestionsMenu() {
    int choice;
    do {
        cout << "===== Investment Suggestions Menu =====" << endl;
        cout << "1. Single Period High Return to Cost Ratio" << endl;
        cout << "2. Multi Period Optimization" << endl;
        cout << "3. Various Filters" << endl;
        cout << "4. Go Back to MAIN MENU" << endl;
        cout << "Enter your choice (1-4): ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Constraints constraints = getUserConstraints();

                string filename = "../data/investments.csv";
                vector<Investment> investments = readInvestmentData(filename);

                Knapsack knapsack;
                vector<Investment> optimizedInvestments = knapsack.optimize(investments, constraints.getBudget(), constraints.getRiskTolerance());
                knapsack.displaySelectedInvestments(optimizedInvestments);
                break;
            }
            case 2:
                cout << "Multi Period Optimization is not yet implemented.\n";
                break;
            case 3:
                cout << "Various Filters are not yet implemented.\n";
                break;
            case 4:
                cout << "Exiting the suggestions menu.\n";
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 4.\n";
                break;
        }

        cout << endl;

    } while (choice != 4);
}
