#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <iostream>
#include <vector>

class Investment {
public:
    Investment(const std::string& name, double cost, double expectedReturn, double risk, const std::string& type);
    
    double getCost() const;
    double getExpectedReturn() const;
    double getRisk() const;
    std::string getType() const;
    void display() const;

private:
    std::string name;
    double cost;
    double expectedReturn;
    double risk;
    std::string type;
};

class Constraints {
public:
    Constraints(double budget, int periods, int riskTolerance);

    double getBudget() const;
    int getPeriods() const;
    int getRiskTolerance() const;
    void display() const;

private:
    double budget;
    int periods;
    int riskTolerance;
};

Constraints getUserConstraints();
std::vector<Investment> readInvestmentData(const std::string& filename);

#endif // INPUT_H
