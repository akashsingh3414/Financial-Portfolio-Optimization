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
    int periods = constraints.getPeriods();

    vector<vector<double>> dp(periods + 1, vector<double>(budget + 1, 0));
    vector<vector<vector<int>>> selected(periods + 1, vector<vector<int>>(budget + 1));

    // DP to maximize return without repeating the same investment in the same period
    for (int t = 1; t <= periods; t++) {
        for (int b = 0; b <= budget; b++) {
            for (int j = 0; j < n; j++) {
                int cost = investments[j].getCost();
                double returnVal = investments[j].getExpectedReturn();
                
                if (b >= cost) {
                    // If this investment improves the return and has not been picked in this period already
                    if (dp[t][b] < dp[t][b - cost] + returnVal && find(selected[t][b - cost].begin(), selected[t][b - cost].end(), j) == selected[t][b - cost].end()) {
                        dp[t][b] = dp[t][b - cost] + returnVal;
                        selected[t][b] = selected[t][b - cost];  // Carry forward the selected investments
                        selected[t][b].push_back(j);  // Add the current investment
                    }
                }
            }
        }
    }

    vector<Investment> result;
    int maxPeriod = periods;
    int maxBudget = budget;
    for (int j : selected[maxPeriod][maxBudget]) {
        result.push_back(investments[j]);
    }

    cout << "\n\t\t\t\tThis Algorithm Provides maximum return investments for multiple\n\t\t\t\tperiods without repeating the same investment in the same period\n";
    cout << "\n\t\t\t\tMaximum return for " << constraints.getPeriods() << " years and " << constraints.getBudget() << " budget could be: " << dp[periods][budget] << "\n\n";

    
    return result;
}
