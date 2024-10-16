#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
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
const string SKY_BLUE = "\033[36m";   // Sky Blue text
const string MAGENTA = "\033[35m";    // Magenta text
const string RESET = "\033[0m";       // Reset color

void variousFilterMenu(const Constraints& constraints) {
    int choice;
    string filename = "data\\investments.csv"; //for windows
    //string filename = "data/investments.csv";  //for linux
    vector<Investment> investments = readInvestmentData(filename);
    filter filter;
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
                optimizedInvestments = filter.sortByHighReturn(investments, constraints.getBudget());
                cout << "\n\t\t\t\tShowing Results for High Return Investments\n";
                displaySelectedInvestments(optimizedInvestments);
                break;
            case 2:
                optimizedInvestments = filter.sortByLowCost(investments, constraints.getBudget());
                cout << "\n\t\t\t\tShowing Results for Low Cost Investments\n";
                displaySelectedInvestments(optimizedInvestments);
                break;
            case 3:
                optimizedInvestments = filter.sortByLowRisk(investments, constraints.getBudget());
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

void plotReturnsGraph(const vector<double>& returns) {

    ofstream dataFile("data/returnsComparison.dat");
    if (dataFile.is_open()) {
        dataFile << "1 " << returns[0] << "\n";  
        dataFile << "2 " << returns[1] << "\n";  
        dataFile << "3 " << returns[2] << "\n";  
        dataFile.close();
    } else {
        cerr << "Error: Unable to open file to write data.\n";
        return;
    }

    ofstream scriptFile("data/plotReturnComparison.gp");
    if (scriptFile.is_open()) {
        scriptFile << "set terminal png size 800,600\n";
        scriptFile << "set output 'data/imageReturnComparison.png'\n";
        scriptFile << "set title 'Maximum Returns Comparison'\n";
        scriptFile << "set xlabel 'Algorithm'\n";
        scriptFile << "set ylabel 'Maximum Return'\n";
        scriptFile << "set xtics ('Knapsack' 1, 'DP with Risk' 2, 'DP without Risk' 3)\n";
        scriptFile << "set style fill solid\n";
        scriptFile << "set boxwidth 0.5\n";
        scriptFile << "set key outside right\n";
        scriptFile << "plot 'data/returnsComparison.dat' using 1:2 with boxes title 'Maximum Return'\n";
        scriptFile.close();
    } else {
        cerr << "Error: Unable to open file to write Gnuplot script.\n";
        return;
    }

    system("gnuplot data/plotReturnComparison.gp");
    system("start data/imageReturnComparison.png");

    cout << "\n\t\t\tGraph has been generated as 'data/imageReturnComparison.png'.\n";
}

void plotAndCompare(const vector<Investment>& investments, const Constraints& constraints) {
    vector<double> returns;

    Knapsack knapsack;
    vector<Investment> knapsackInvestments = knapsack.optimizeByKnapsack(investments, constraints.getBudget(), constraints.getRiskTolerance());
    double knapsackReturn = 0;
    for (const auto& inv : knapsackInvestments) {
        knapsackReturn += inv.getExpectedReturn();
    }
    returns.push_back(knapsackReturn);

    dynamicProgramming dynamicProgramming;
    vector<Investment> dpWithRisk = dynamicProgramming.maximizeReturns(investments, constraints.getBudget(), constraints.getRiskTolerance(), 'Y');
    double dpWithRiskReturn = 0;
    for (const auto& inv : dpWithRisk) {
        dpWithRiskReturn += inv.getExpectedReturn();
    }
    returns.push_back(dpWithRiskReturn);

    vector<Investment> dpNoRisk = dynamicProgramming.maximizeReturns(investments, constraints.getBudget(), constraints.getRiskTolerance(), 'N');
    double dpNoRiskReturn = 0;
    for (const auto& inv : dpNoRisk) {
        dpNoRiskReturn += inv.getExpectedReturn();
    }
    returns.push_back(dpNoRiskReturn);

    plotReturnsGraph(returns);

    return ;
}

void getSuggestionsMenu(const Constraints& constraints) {
    int choice;
    string filename = "data\\investments.csv"; // for Windows
    // string filename = "data/investments.csv";  // for Linux
    vector<Investment> investments = readInvestmentData(filename);

    do {
        cout << "\n\t\t\t" << "--------------------------------------------------------------\n";
        cout << "\t\t\t" << ".................Investment Suggestions Menu.................." << "\n";
        cout << "\t\t\t" << "--------------------------------------------------------------\n" << "\n";
        
        cout << "\t\t\t\t" << YELLOW << "1. High Return to Cost Ratio-Wise investments" << RESET << endl;
        cout << "\t\t\t\t" << YELLOW << "2. Optimized Maximum Returns" << RESET << endl;
        cout << "\t\t\t\t" << YELLOW << "3. Various Filters" << RESET << endl;
        cout << "\t\t\t\t" << YELLOW << "4. Plot returns and Compare" << RESET << endl;
        cout << "\t\t\t\t" << YELLOW << "5. Go Back to MAIN MENU" << RESET << endl;

        cout << "\n\t\t\t\t" << BLUE << "Enter your choice (1-5): " << RESET;

        // Input validation
        while (!(cin >> choice) || choice < 1 || choice > 6) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n\t\t\t\t" << RED << "Invalid choice. Please enter a number between 1 and 5: " << RESET;
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
                char considerRisk='N';
                cout << "\n\t\t\t\tDo you want to consider the risk factor? (Y/N): ";
                cin >> considerRisk;
                dynamicProgramming dynamicProgramming;
                vector<Investment> optimizedInvestments = dynamicProgramming.maximizeReturns(investments, constraints.getBudget(), constraints.getRiskTolerance(), considerRisk);
                cout << "\n\t\t\t\tShowing Optimized result for max returns within budget\n";
                displaySelectedInvestments(optimizedInvestments);
                break;
            }
            case 3: {
                variousFilterMenu(constraints);
                break;
            }
            case 4: {
                plotAndCompare(investments, constraints);
                break;
            }
            case 5: {
                cout << "\n\t\t\t\t" << RED << "Exiting the suggestions menu." << RESET << "\n";
                break;
            }
        }
        cout << endl;
    } while (choice != 5);
}