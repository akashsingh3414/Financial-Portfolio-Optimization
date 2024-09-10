#include <vector>
#include <algorithm>
#include "../include/greedy_knapsack_filterwise.h"
#include "../include/dataTypes.h"

using namespace std;

Greedy::Greedy() {}

Greedy::~Greedy() {}

vector<Investment> selectInvestments(const vector<Investment>& sortedInvestments, double budget) {
    vector<Investment> selectedInvestments;
    double currentBudget = budget;

    for (const auto& investment : sortedInvestments) {
        if (investment.getCost() <= currentBudget) {
            selectedInvestments.push_back(investment);
            currentBudget -= investment.getCost();
        }
    }

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

vector<Investment> Greedy::sortByAllCombined(const vector<Investment>& investments, double budget) {
    vector<Investment> filteredInvestments = investments;

    sort(filteredInvestments.begin(), filteredInvestments.end(), [](const Investment& a, const Investment& b) {
        // Prioritizing high return per unit cost and low risk
        double scoreA = (a.getExpectedReturn() / a.getCost()) - a.getRisk();
        double scoreB = (b.getExpectedReturn() / b.getCost()) - b.getRisk();
        return scoreA > scoreB;
    });

    return selectInvestments(filteredInvestments, budget);
}