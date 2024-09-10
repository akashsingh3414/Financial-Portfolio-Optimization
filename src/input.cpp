#include <iostream>
#include <vector>
#include "../include/input.h"
#include "../include/dataTypes.h"
#include "../include/greedy_knapsack_filterwise.h"
#include "../include/knapsack.h"
#include "../include/utils.h"

using namespace std;

void variousFilterMenu(const Constraints& constraints) {
    int choice;
    string filename = "../data/investments.csv";
    vector<Investment> investments = readInvestmentData(filename);
    Greedy Greedy;
    vector<Investment> optimizedInvestments;

    do {
        cout << "===== Select One Filter =====" << endl;
        cout << "1. High Return" << endl;
        cout << "2. Low Cost" << endl;
        cout << "3. Low Risk" << endl;
        cout << "4. High Return, Low Cost & Low Risk" << endl;
        cout << "5. Go Back to PREVIOUS MENU" << endl;
        cout << "Enter your choice (1-5): ";
        cin >> choice;

        switch (choice) {
            case 1:
                optimizedInvestments = Greedy.sortByHighReturn(investments, constraints.getBudget());
                cout << "Showing Results for High Return Investments\n";
                displaySelectedInvestments(optimizedInvestments);
                break;
            case 2:
                optimizedInvestments = Greedy.sortByLowCost(investments, constraints.getBudget());
                cout << "Showing Results for Low Cost Investments\n";
                displaySelectedInvestments(optimizedInvestments);
                break;
            case 3:
                optimizedInvestments = Greedy.sortByLowRisk(investments, constraints.getBudget());
                cout << "Showing Results for Low Risk Investments\n";
                displaySelectedInvestments(optimizedInvestments);
                break;
            case 4:
                optimizedInvestments = Greedy.sortByAllCombined(investments, constraints.getBudget());
                cout << "Showing Results for High Return, Low Cost & Low Risk\n";
                displaySelectedInvestments(optimizedInvestments);
                break;
            case 5:
                cout << "Exiting current menu.\n";
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 5.\n";
                break;
        }

        cout << endl;
    } while (choice != 5);
}

void getSuggestionsMenu(const Constraints& constraints) {
    int choice;
    string filename = "../data/investments.csv";
    vector<Investment> investments = readInvestmentData(filename);

    do {
        cout << "\n===== Investment Suggestions Menu =====\n" << endl;
        cout << "1. Single Period High Return to Cost Ratio" << endl;
        cout << "2. Multi Period Optimization" << endl;
        cout << "3. Various Filters" << endl;
        cout << "4. Plot Graphs" << endl;
        cout << "5. Go Back to MAIN MENU" << endl;
        cout << "Enter your choice (1-5): ";
        cin >> choice;

        switch (choice) {
            case 1:
                {
                    Knapsack knapsack;
                    vector<Investment> optimizedInvestments = knapsack.optimizeByKnapsack(investments, constraints.getBudget(), constraints.getRiskTolerance());
                    cout << "Showing Results for Single Period High Return to Cost Ratio\n";
                    displaySelectedInvestments(optimizedInvestments);
                }
                break;
            case 2:
                cout << "Multi Period Optimization is not yet implemented.\n";
                break;
            case 3:
                variousFilterMenu(constraints);
                break;
            case 4:
                cout << "Plotting Graph.\n";
                cout << "Feature Coming Soon.\n";
                break;
            case 5:
                cout << "Exiting the suggestions menu.\n";
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 5.\n";
                break;
        }

        cout << endl;
    } while (choice != 5);
}