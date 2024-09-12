#ifndef DATATYPES_H
#define DATATYPES_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Investment {
public:
    Investment(const string& name, double cost, double expectedReturn, double risk, const string& type);
    
    double getCost() const;
    double getExpectedReturn() const;
    double getRisk() const;
    string getType() const;
    void display() const;

private:
    string name;
    double cost;
    double expectedReturn;
    double risk;
    string type;
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

#endif // DATATYPES_H
