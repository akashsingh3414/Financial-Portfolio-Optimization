#ifndef FILTERWISE_H
#define FILTERWISE_H

#include "dataTypes.h"
#include <vector>

class filter {
public:
    filter();
    ~filter();
    
    std::vector<Investment> sortByHighReturn(const std::vector<Investment>& investments, double budget);
    std::vector<Investment> sortByLowCost(const std::vector<Investment>& investments, double budget);
    std::vector<Investment> sortByLowRisk(const std::vector<Investment>& investments, double budget);
};

#endif // FILTERWISE_H
