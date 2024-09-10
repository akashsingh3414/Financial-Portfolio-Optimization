#ifndef KNAPSACK_H
#define KNAPSACK_H

#include "dataTypes.h"
#include <vector>

class Knapsack {
public:
    Knapsack();
    ~Knapsack();
    
    std::vector<Investment> optimizeByKnapsack(const std::vector<Investment>& investments, double budget, int riskTolerance);
};

#endif // KNAPSACK_H
