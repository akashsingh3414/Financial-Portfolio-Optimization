#ifndef KNAPSACK_H
#define KNAPSACK_H

#include "dataTypes.h"
#include <vector>

class Knapsack {
public:
    Knapsack();
    ~Knapsack();
    
    std::vector<Investment> optimize(const std::vector<Investment>& investments, double budget, int riskTolerance);

    void displaySelectedInvestments(const std::vector<Investment>& selectedInvestments);
};

#endif // KNAPSACK_H
