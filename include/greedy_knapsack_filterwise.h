#ifndef GREEDY_KNAPSACK_FILTERWISE_H
#define GREEDY_KNAPSACK_FILTERWISE_H

#include "dataTypes.h"
#include <vector>

class Greedy {
public:
    Greedy();
    ~Greedy();
    
    std::vector<Investment> sortByHighReturn(const std::vector<Investment>& investments, double budget);
    std::vector<Investment> sortByLowCost(const std::vector<Investment>& investments, double budget);
    std::vector<Investment> sortByLowRisk(const std::vector<Investment>& investments, double budget);
};

#endif // GREEDY_KNAPSACK_FILTERWISE_H
