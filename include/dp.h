#ifndef DP_H
#define DP_H

#include <vector>
#include "dataTypes.h"

using namespace std;

class dynamicProgramming {
public:
    dynamicProgramming();
    ~dynamicProgramming();
    
    vector<Investment> maximizeReturns(const vector<Investment>& investments, double budget, int riskTolerance, char considerRisk);
};

#endif // DP_H