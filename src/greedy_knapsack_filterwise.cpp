#include <vector>
#include <algorithm>
#include "../include/greedy_knapsack_filterwise.h"
#include "../include/dataTypes.h"

using namespace std;

Greedy::Greedy() {}

Greedy::~Greedy() {}

vector<Investment> selectInvestments(const vector<Investment>& sortedInvestments, double budget) {
    vector<Investment> selectedInvestments;
    double currentBudget = budget, maxReturn = 0;

    for (const auto& investment : sortedInvestments) {
        if (investment.getCost() <= currentBudget) {
            selectedInvestments.push_back(investment);
            maxReturn += investment.getExpectedReturn();
            currentBudget -= investment.getCost();
        }
    }

    cout << "\n\t\t\t\tMaximum return for " << "budget " << budget << " could be: " << maxReturn << "\n\n";

    return selectedInvestments;
}

vector<Investment> Greedy::sortByHighReturn(const vector<Investment>& investments, double budget) {
    vector<Investment> filteredInvestments = investments;

    sort(filteredInvestments.begin(), filteredInvestments.end(), [](const Investment& a, const Investment& b) {
        return a.getExpectedReturn() > b.getExpectedReturn();
    });

    return selectInvestments(filteredInvestments, budget);
}

vector<Investment> Greedy::sortByLowCost(const vector<Investment>& investments, double budget) {
    vector<Investment> filteredInvestments = investments;

    sort(filteredInvestments.begin(), filteredInvestments.end(), [](const Investment& a, const Investment& b) {
        return a.getCost() < b.getCost();
    });

    return selectInvestments(filteredInvestments, budget);
}

vector<Investment> Greedy::sortByLowRisk(const vector<Investment>& investments, double budget) {
    vector<Investment> filteredInvestments = investments;

    sort(filteredInvestments.begin(), filteredInvestments.end(), [](const Investment& a, const Investment& b) {
        return a.getRisk() < b.getRisk();
    });

    return selectInvestments(filteredInvestments, budget);
}