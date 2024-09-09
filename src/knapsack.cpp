#include "../include/knapsack.h"
#include "../include/input.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

Knapsack::Knapsack() {}

Knapsack::~Knapsack() {}

vector<Investment> Knapsack::optimize(const vector<Investment>& investments, double budget, int riskTolerance) {
    vector<Investment> filteredInvestments;

    for (const auto& investment : investments) {
        if (riskTolerance == 1 && investment.getRisk() <= 0.10) {
            filteredInvestments.push_back(investment);
        } else if (riskTolerance == 2 && investment.getRisk() <= 0.25) {
            filteredInvestments.push_back(investment);
        } else if (riskTolerance == 3) {
            filteredInvestments.push_back(investment);
        }
    }

    sort(filteredInvestments.begin(), filteredInvestments.end(), [](const Investment& a, const Investment& b) {
        return (a.getExpectedReturn() / a.getCost()) > (b.getExpectedReturn() / b.getCost());
    });

    vector<Investment> selectedInvestments;
    double currentBudget = budget;

    for (const auto& investment : filteredInvestments) {
        if (investment.getCost() <= currentBudget) {
            selectedInvestments.push_back(investment);
            currentBudget -= investment.getCost();
        }
    }

    return selectedInvestments;
}

void Knapsack::displaySelectedInvestments(const vector<Investment>& selectedInvestments) {
    cout << "\n\nSelected Investments for Maximum Return to Cost Ratio:\n\n";
    if (!selectedInvestments.empty()) {
        for (const auto& investment : selectedInvestments) {
            investment.display();
        }
    } else {
        cout << "No suitable investments found within the budget." << endl;
    }
    cout<<endl;
}
