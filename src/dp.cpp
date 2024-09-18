#include <vector>
#include <iostream>
#include <algorithm>
#include "../include/dataTypes.h"
#include "../include/dp.h"

using namespace std;

dynamicProgramming::dynamicProgramming() {}

dynamicProgramming::~dynamicProgramming() {}

vector<Investment> dynamicProgramming::maximizeReturns(const vector<Investment>& investments, const Constraints& constraints) {
    char considerRisk;
    cout << "\n\t\t\t\tDo you want to consider the risk factor? (Y/N): ";
    cin >> considerRisk;

    int n = investments.size();
    int budget = constraints.getBudget();
    double riskTolerance = constraints.getRiskTolerance();

    vector<Investment> filteredInvestments;

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

    vector<double> dp(budget + 1, 0);
    vector<vector<int>> selected(budget + 1);

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

    vector<Investment> result;
    for (int idx : selected[budget]) {
        result.push_back(filteredInvestments[idx]);
    }

    cout << "\n\t\t\t\tMaximum return using Dynamic Programming for budget " << constraints.getBudget() << " could be: " << dp[budget] << "\n\n";

    return result;
}
