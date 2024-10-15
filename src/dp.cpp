#include <vector>
#include <iostream>
#include <algorithm>
#include "../include/dataTypes.h"
#include "../include/dp.h"

using namespace std;

// ANSI color codes for better visuals
const string RED = "\033[31m";   // Red text
const string GREEN = "\033[32m"; // Green text
const string RESET = "\033[0m";  // Reset color

dynamicProgramming::dynamicProgramming() {}

dynamicProgramming::~dynamicProgramming() {}

vector<Investment> dynamicProgramming::maximizeReturns(const vector<Investment>& investments, double givenBudget, int givenRiskTolerance, char considerRisk) {
    int n = investments.size();
    int budget = givenBudget;
    double riskTolerance = givenRiskTolerance;

    vector<Investment> filteredInvestments;

    // Filter investments based on risk tolerance
    if (considerRisk == 'Y' || considerRisk == 'y') {
        for (const auto& investment : investments) {
            if (riskTolerance == 1 && investment.getRisk() <= 0.10) {
                filteredInvestments.push_back(investment);
            } else if (riskTolerance == 2 && investment.getRisk() <= 0.20) {
                filteredInvestments.push_back(investment);
            } else if (riskTolerance == 3 && investment.getRisk() > 0.20) {
                filteredInvestments.push_back(investment);
            }
        }
    } else {
        filteredInvestments = investments;
    }
    
    n = filteredInvestments.size();
    
    // Dynamic programming array to store maximum returns
    vector<double> dp(budget + 1, 0);
    vector<vector<int>> selected(budget + 1);

    // Build the DP table
    for (int j = 0; j < n; ++j) {
        int cost = filteredInvestments[j].getCost();
        int returnVal = filteredInvestments[j].getExpectedReturn();

        for (int b = budget; b >= cost; --b) {
            if (dp[b] < dp[b - cost] + returnVal) {
                dp[b] = dp[b - cost] + returnVal;
                selected[b] = selected[b - cost];
                selected[b].push_back(j);
            }
        }
    }

    // Prepare the result investments
    vector<Investment> result;
    for (int idx : selected[budget]) {
        result.push_back(filteredInvestments[idx]);
    }

    cout << "\n\t\t\tMax Return using Dynamic Programming could be " 
         << GREEN << dp[budget] << RESET << " (with a budget of " 
         << RED << givenBudget  << RESET << ")\n";  // Max return and budget in green color

    return result;
}
