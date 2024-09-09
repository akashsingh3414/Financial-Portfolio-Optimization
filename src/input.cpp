#include "../include/input.h"
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
    cout << "Name: " << name << ", Cost: " << cost << ", Expected Return: " << expectedReturn 
              << ", Risk: " << risk << ", Type: " << type << endl;
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
    cout << "Budget: " << budget << ", Periods: " << periods
              << ", Risk Tolerance: " << riskTolerance << endl;
}

Constraints getUserConstraints() {
    double budget;
    int periods;
    int riskTolerance;

    cout << "Enter total budget for investment: ";
    cin >> budget;
    cout << "Enter number of periods for optimization: ";
    cin >> periods;
    cout << "Enter risk tolerance (1 = Low, 2 = Medium, 3 = High): ";
    cin >> riskTolerance;

    return Constraints(budget, periods, riskTolerance);
}

vector<Investment> readInvestmentData(const string& filename) {
    vector<Investment> investments;
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return investments;
    }

    while (getline(file, line)) {
        istringstream iss(line);
        string name, type;
        double cost, expectedReturn, risk;

        string costStr, returnStr, riskStr;

        if (getline(iss, name, ',') &&
            getline(iss, costStr, ',') &&
            getline(iss, returnStr, ',') &&
            getline(iss, riskStr, ',') &&
            getline(iss, type)) {
            
            cost = stod(costStr);
            expectedReturn = stod(returnStr);
            risk = stod(riskStr);

            investments.emplace_back(name, cost, expectedReturn, risk, type);
        }
    }

    file.close();
    return investments;
}

