#include "../include/dataTypes.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

Investment::Investment(const string& name, double cost, double expectedReturn, double risk, const string& type)
    : name(name), cost(cost), expectedReturn(expectedReturn), risk(risk), type(type) {}

double Investment::getCost() const {
    return cost;
}

double Investment::getExpectedReturn() const {
    return expectedReturn;
}

double Investment::getRisk() const {
    return risk;
}

string Investment::getType() const {
    return type;
}

void Investment::display() const {
    cout << "\n\t\t\t\tName: " << name << ", Cost: " << cost << ", Expected Return: " << expectedReturn << ", Risk: " << risk << ", Type: " << type << "\n";
}

Constraints::Constraints(double budget, int periods, int riskTolerance)
    : budget(budget), periods(periods), riskTolerance(riskTolerance) {}

double Constraints::getBudget() const {
    return budget;
}

int Constraints::getPeriods() const {
    return periods;
}

int Constraints::getRiskTolerance() const {
    return riskTolerance;
}

void Constraints::display() const {
    cout << "\n\t\t\t\tBudget: " << budget << ", Periods: " << periods << ", Risk Tolerance: " << riskTolerance << "\n";
}

Constraints getUserConstraints() {
    double budget;
    int periods;
    int riskTolerance;

    cout << "\n\t\t\t\t\tWe'll require some data before proceeding further. Please provide them.\n\n";
    cout << "\n\t\t\t\t\tEnter total budget for investment: ";
    cin >> budget;
    cout << "\t\t\t\t\tEnter number of periods for optimization: ";
    cin >> periods;
    cout << "\t\t\t\t\tEnter risk tolerance (1 = Low, 2 = Medium, 3 = High): ";
    cin >> riskTolerance;

    return Constraints(budget, periods, riskTolerance);
}