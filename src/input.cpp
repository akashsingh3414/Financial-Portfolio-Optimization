#include <iostream>
#include <vector>
#include "../include/input.h"
#include "../include/dataTypes.h"
#include "../include/filterwise.h"
#include "../include/knapsack.h"
#include "../include/utils.h"
#include "../include/output.h"
#include "../include/dp.h"

using namespace std;

void variousFilterMenu(const Constraints& constraints) {
    int choice;
    string filename = "../data/investments.csv";
    vector<Investment> investments = readInvestmentData(filename);
    Greedy Greedy;
    vector<Investment> optimizedInvestments;

    do {
        cout << "\n\t\t\t\t--------------------------------------------------------------\n";
        cout << "\t\t\t\t.....................Select One Filter......................\n";
        cout << "\t\t\t\t--------------------------------------------------------------\n\n";
        cout << "\t\t\t\t\t1. High Return" << endl;
        cout << "\t\t\t\t\t2. Low Cost" << endl;
        cout << "\t\t\t\t\t3. Low Risk" << endl;
        cout << "\t\t\t\t\t4. Investment Type" << endl;
        cout << "\t\t\t\t\t5. Go Back to PREVIOUS MENU" << endl;
        cout << "\n\t\t\t\t\tEnter your choice (1-5): ";
        cin >> choice;

        switch (choice) {
            case 1:
                optimizedInvestments = Greedy.sortByHighReturn(investments, constraints.getBudget());
                cout << "\n\t\t\t\tShowing Results for High Return Investments\n\n";
                displaySelectedInvestments(optimizedInvestments);
                break;
            case 2:
                optimizedInvestments = Greedy.sortByLowCost(investments, constraints.getBudget());
                cout << "\n\t\t\t\tShowing Results for Low Cost Investments\n\n";
                displaySelectedInvestments(optimizedInvestments);
                break;
            case 3:
                optimizedInvestments = Greedy.sortByLowRisk(investments, constraints.getBudget());
                cout << "\n\t\t\t\tShowing Results for Low Risk Investments\n\n";
                displaySelectedInvestments(optimizedInvestments);
                break;
            case 4: {
                    string investmentType;
                    cout << "\n\t\t\t\tType of Investments you are looking for? ";
                    cin >> investmentType ;
                    optimizedInvestments = Greedy.filterByType(investments, investmentType, constraints.getBudget());
                    cout << "\n\t\t\t\tShowing Results for "<< investmentType <<" investments\n\n";
                    displaySelectedInvestments(optimizedInvestments);
                }
                break;
            case 5:
                cout << "\n\t\t\t\t\tExiting current menu.\n";
                break;
            default:
                cout << "\n\t\t\t\t\tInvalid choice. Please enter a number between 1 and 4.\n";
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
        cout << "\n\t\t\t\t--------------------------------------------------------------\n";
        cout << "\t\t\t\t.................Investment Suggestions Menu..................\n";
        cout << "\t\t\t\t--------------------------------------------------------------\n\n";
        cout << "\t\t\t\t\t1. High Return to Cost Ratio-Wise investments" << endl;
        cout << "\t\t\t\t\t2. Optimized Solution" << endl;
        cout << "\t\t\t\t\t3. Various Filters" << endl;
        cout << "\t\t\t\t\t4. Plot Average Return, Average Cost & Profit Graph" << endl;
        cout << "\t\t\t\t\t5. Go Back to MAIN MENU" << endl;
        cout << "\n\t\t\t\t\tEnter your choice (1-5): ";
        cin >> choice;

        switch (choice) {
            case 1:
                {
                    Knapsack knapsack;
                    vector<Investment> optimizedInvestments = knapsack.optimizeByKnapsack(investments, constraints.getBudget(), constraints.getRiskTolerance());
                    cout << "\n\t\t\t\tShowing Results for High Return to Cost Ratio within budget\n\n";
                    displaySelectedInvestments(optimizedInvestments);
                }
                break;
            case 2:
                {
                    dynamicProgramming dynamicProgramming;
                    vector<Investment> optimizedInvestments = dynamicProgramming.maximizeReturns(investments, constraints);
                    displaySelectedInvestments(optimizedInvestments);
                }
                break;
            case 3:
                variousFilterMenu(constraints);
                break;
            case 4:
                plotInvestmentsVsReturn(constraints);
                break;
            case 5:
                cout << "\n\t\t\t\t\tExiting the suggestions menu.\n";
                break;
            default:
                cout << "\t\t\t\t\tInvalid choice. Please enter a number between 1 and 5.\n";
                break;
        }
        cout << endl;
    } while (choice != 5);
}
