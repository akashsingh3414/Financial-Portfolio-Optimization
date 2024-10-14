#include "../include/knapsack.h"
#include "../include/dataTypes.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// ANSI color codes for better visuals
const string GREEN = "\033[32m"; // Green text
const string RESET = "\033[0m";  // Reset color
const string RED = "\033[31m";         // Red text

Knapsack::Knapsack() {}

Knapsack::~Knapsack() {}

vector<Investment> Knapsack::optimizeByKnapsack(const vector<Investment>& investments, double budget, int riskTolerance) {
    vector<Investment> filteredInvestments;

    // Filtering investments based on risk tolerance
    for (const auto& investment : investments) {
        if (riskTolerance == 1 && investment.getRisk() <= 0.10) {
            filteredInvestments.push_back(investment);  
        } else if (riskTolerance == 2 && investment.getRisk() <= 0.20) {
            filteredInvestments.push_back(investment);  
        } else if (riskTolerance == 3 && investment.getRisk() > 0.20) {
            filteredInvestments.push_back(investment);  
        }
    }

    // Sorting investments based on return-to-cost ratio
    sort(filteredInvestments.begin(), filteredInvestments.end(), [](const Investment& a, const Investment& b) {
        return (a.getExpectedReturn() / a.getCost()) > (b.getExpectedReturn() / b.getCost());
    });

    vector<Investment> selectedInvestments;
    double currentBudget = budget;
    double totalReturn = 0;

    // Selecting investments within the budget
    for (const auto& investment : filteredInvestments) {
        if (investment.getCost() <= currentBudget) {
            selectedInvestments.push_back(investment);
            totalReturn += investment.getExpectedReturn();
            currentBudget -= investment.getCost();
        }
    }

    // Optional: if totalReturn is negative, print warning
    if (totalReturn < 0) {
        cout << "\n\t\t\tWarning: Total return is negative (" << GREEN << totalReturn << RESET 
             << "). Consider reviewing your investment choices.\n";
    } else {
        cout << "\n\t\t\tMax Return using Knapsack & Greedy Algorithm could be " 
             << GREEN << totalReturn << RESET << " (with a budget of " 
             << RED << budget << RESET << ")\n";  // Max return and budget in green color
    }

    return selectedInvestments;
}
