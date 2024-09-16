#include "../include/knapsack.h"
#include "../include/dataTypes.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

Knapsack::Knapsack() {}

Knapsack::~Knapsack() {}

vector<Investment> Knapsack::optimizeByKnapsack(const vector<Investment>& investments, double budget, int riskTolerance) {
    vector<Investment> filteredInvestments;

    for (const auto& investment : investments) {
        if (riskTolerance == 1 && investment.getRisk() <= 0.10) {
            filteredInvestments.push_back(investment);  
        } else if (riskTolerance == 2 && investment.getRisk() <= 0.20 && investment.getRisk() > 0.10) {
            filteredInvestments.push_back(investment);  
        } else if (riskTolerance == 3 && investment.getRisk() > 0.20) {
            filteredInvestments.push_back(investment);  
        }
    }

    sort(filteredInvestments.begin(), filteredInvestments.end(), [](const Investment& a, const Investment& b) {
        return (a.getExpectedReturn() / a.getCost()) > (b.getExpectedReturn() / b.getCost());
    });

    vector<Investment> selectedInvestments;
    double currentBudget = budget;
    double maxReturn = 0;

    for (const auto& investment : filteredInvestments) {
        if (investment.getCost() <= currentBudget) {
            selectedInvestments.push_back(investment);
            maxReturn += investment.getExpectedReturn();
            currentBudget -= investment.getCost();
        }
    }

    cout << "\n\t\t\t\tMax Return using Knapsack & Greedy Algorithm could be " << maxReturn << "\n";
    return selectedInvestments;
}
