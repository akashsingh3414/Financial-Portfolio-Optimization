#include <vector>
#include <iostream>
#include <algorithm>
#include "../include/dataTypes.h"
#include "../include/dp.h"

using namespace std;

dynamicProgramming::dynamicProgramming() {}

dynamicProgramming::~dynamicProgramming() {}

vector<Investment> dynamicProgramming::maximizeReturns(const vector<Investment>& investments, const Constraints& constraints) {
    int n = investments.size();
    int budget = constraints.getBudget();

    vector<double> dp(budget + 1, 0);
    vector<vector<int>> selected((budget + 1));

    // DP to maximize return without repeating the same investment in the same period
    for (int b = 0; b <= budget; b++) {
        for (int j = 0; j < n; j++) {
            int cost = investments[j].getCost();
            double returnVal = investments[j].getExpectedReturn();
            
            if (b >= cost) {
                // If this investment improves the return and has not been picked in this period already
                if (dp[b] < dp[b - cost] + returnVal && find(selected[b - cost].begin(), selected[b - cost].end(), j) == selected[b - cost].end()) {
                    dp[b] = dp[b - cost] + returnVal;
                    selected[b] = selected[b - cost];  // Carry forward the selected investments
                    selected[b].push_back(j);  // Add the current investment
                }
            }
        }
    }

    vector<Investment> result;
    int maxBudget = budget;
    for (int j : selected[maxBudget]) {
        result.push_back(investments[j]);
    }

    cout << "\n\t\t\t\tThis Algorithm Provides maximum return investments for without\n\t\t\t\trepeating the same investment within budget and ignoring risk factor\n";
    cout << "\n\t\t\t\tMaximum return for " << " years and " << constraints.getBudget() << " budget could be: " << dp[budget] << "\n\n";

    return result;
}
