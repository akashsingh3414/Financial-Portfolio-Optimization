#include <vector>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include "../include/filterwise.h"
#include "../include/dataTypes.h"

using namespace std;

// ANSI color codes for better visuals
const string GREEN = "\033[32m"; // Green text
const string RESET = "\033[0m";  // Reset color

Greedy::Greedy() {}

Greedy::~Greedy() {}

string toLowercase(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

vector<Investment> selectInvestments(const vector<Investment>& sortedInvestments, double budget) {
    vector<Investment> selectedInvestments;
    double currentBudget = budget;
    double totalReturn = 0;

    for (const auto& investment : sortedInvestments) {
        if (investment.getCost() <= currentBudget) {
            selectedInvestments.push_back(investment);
            totalReturn += investment.getExpectedReturn();
            currentBudget -= investment.getCost();
        }
    }

    // Outputting the total return and budget
    if (totalReturn < 0) {
        cout << "\n\t\t\t\tWarning: Total return is negative (" 
             << GREEN << totalReturn << RESET << "). Consider reviewing your investment choices.\n";
    } else {
        cout << "\n\t\t\t\tMax Return using current filter could be " 
             << GREEN << totalReturn << RESET << " (with a budget of " 
             << GREEN << budget << RESET << ")\n";
    }

    return selectedInvestments;
}

vector<Investment> Greedy::sortByHighReturn(const vector<Investment>& investments, double budget) {
    vector<Investment> filteredInvestments = investments;

    // Sort by expected return in descending order
    sort(filteredInvestments.begin(), filteredInvestments.end(), [](const Investment& a, const Investment& b) {
        return a.getExpectedReturn() > b.getExpectedReturn();
    });

    return selectInvestments(filteredInvestments, budget);
}

vector<Investment> Greedy::sortByLowCost(const vector<Investment>& investments, double budget) {
    vector<Investment> filteredInvestments = investments;

    // Sort by cost in ascending order
    sort(filteredInvestments.begin(), filteredInvestments.end(), [](const Investment& a, const Investment& b) {
        return a.getCost() < b.getCost();
    });

    return selectInvestments(filteredInvestments, budget);
}

vector<Investment> Greedy::sortByLowRisk(const vector<Investment>& investments, double budget) {
    vector<Investment> filteredInvestments = investments;

    // Sort by risk in ascending order
    sort(filteredInvestments.begin(), filteredInvestments.end(), [](const Investment& a, const Investment& b) {
        return a.getRisk() < b.getRisk();
    });

    return selectInvestments(filteredInvestments, budget);
}
