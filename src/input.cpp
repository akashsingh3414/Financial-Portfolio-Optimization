#include <iostream>
#include <vector>
#include "../include/input.h"
#include "../include/dataTypes.h"
#include "../include/filterwise.h"
#include "../include/knapsack.h"
#include "../include/utils.h"
#include "../include/dp.h"
#include <limits>

using namespace std;

// ANSI color codes for better visuals
const string RED = "\033[31m";        // Red text
const string GREEN = "\033[32m";      // Green text
const string YELLOW = "\033[33m";     // Yellow text
const string BLUE = "\033[34m";       // Blue text
const string SKY_BLUE = "\033[36m";    // Sky Blue text
const string MAGENTA = "\033[35m";    // Magenta text
const string RESET = "\033[0m";       // Reset color

void variousFilterMenu(const Constraints& constraints) {
    int choice;
    string filename = "data\\investments.csv";    
    vector<Investment> investments = readInvestmentData(filename);
    Greedy Greedy;
    vector<Investment> optimizedInvestments;

    do {
        cout << "\n\t\t\t" << BLUE << "--------------------------------------------------------------\n" << RESET;
        cout << "\t\t\t" << ".....................Select One Filter......................" << "\n";
        cout << "\t\t\t" << BLUE << "--------------------------------------------------------------\n" << RESET << "\n";
        
        cout << "\t\t\t\t" << YELLOW << "1. High Return" << RESET << endl;
        cout << "\t\t\t\t" << YELLOW << "2. Low Cost" << RESET << endl;
        cout << "\t\t\t\t" << YELLOW << "3. Low Risk" << RESET << endl;
        cout << "\t\t\t\t" << YELLOW << "4. Go Back to PREVIOUS MENU" << RESET << endl;
        cout << "\n\t\t\t\t" << BLUE << "Enter your choice (1-4): " << RESET;

        // Input validation
        while (!(cin >> choice) || choice < 1 || choice > 4) {
            cin.clear();  // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
            cout << "\n\t\t\t\t" << RED << "Invalid choice. Please enter a number between 1 and 4: " << RESET;
        }

        switch (choice) {
            case 1:
                optimizedInvestments = Greedy.sortByHighReturn(investments, constraints.getBudget());
                cout << "\n\t\t\t\tShowing Results for High Return Investments\n";
                displaySelectedInvestments(optimizedInvestments);
                break;
            case 2:
                optimizedInvestments = Greedy.sortByLowCost(investments, constraints.getBudget());
                cout << "\n\t\t\t\tShowing Results for Low Cost Investments\n";
                displaySelectedInvestments(optimizedInvestments);
                break;
            case 3:
                optimizedInvestments = Greedy.sortByLowRisk(investments, constraints.getBudget());
                cout << "\n\t\t\t\tShowing Results for Low Risk Investments\n";
                displaySelectedInvestments(optimizedInvestments);
                break;
            case 4:
                cout << "\n\t\t\t\t" << RED << "Exiting current menu" << RESET << "\n";
                break;
        }

        cout << endl;
    } while (choice != 4);
}

void getSuggestionsMenu(const Constraints& constraints) {
    int choice;
    string filename = "data\\investments.csv";    
    vector<Investment> investments = readInvestmentData(filename);

    do {
        cout << "\n\t\t\t" << "--------------------------------------------------------------\n";
        cout << "\t\t\t" << ".................Investment Suggestions Menu.................." << "\n";
        cout << "\t\t\t" << "--------------------------------------------------------------\n" << "\n";
        
        cout << "\t\t\t\t" << YELLOW << "1. High Return to Cost Ratio-Wise investments" << RESET << endl;
        cout << "\t\t\t\t" << YELLOW << "2. Optimized Solution" << RESET << endl;
        cout << "\t\t\t\t" << YELLOW << "3. Various Filters" << RESET << endl;
        cout << "\t\t\t\t" << YELLOW << "4. Go Back to MAIN MENU" << RESET << endl;

        cout << "\n\t\t\t\t" << BLUE << "Enter your choice (1-4): " << RESET;

        // Input validation
        while (!(cin >> choice) || choice < 1 || choice > 4) {
            cin.clear();  // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
            cout << "\n\t\t\t\t" << RED << "Invalid choice. Please enter a number between 1 and 4: " << RESET;
        }

        switch (choice) {
            case 1: {
                Knapsack knapsack;
                vector<Investment> optimizedInvestments = knapsack.optimizeByKnapsack(investments, constraints.getBudget(), constraints.getRiskTolerance());
                cout << "\n\t\t\t\tShowing Results for High Return to Cost Ratio within budget\n";
                displaySelectedInvestments(optimizedInvestments);
                break;
            }
            case 2: {
                dynamicProgramming dynamicProgramming;
                vector<Investment> optimizedInvestments = dynamicProgramming.maximizeReturns(investments, constraints);
                cout << "\n\t\t\t\tShowing Optimized result for max returns within budget\n";
                displaySelectedInvestments(optimizedInvestments);
                break;
            }
            case 3:
                variousFilterMenu(constraints);
                break;
            case 4:
                cout << "\n\t\t\t\t" << RED << "Exiting the suggestions menu." << RESET << "\n";
                break;
        }
        cout << endl;
    } while (choice != 4);
}
