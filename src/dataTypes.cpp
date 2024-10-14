#include "../include/dataTypes.h"
#include <limits>

// ANSI color codes for better visuals
const string RED = "\033[31m";        // Red text
const string GREEN = "\033[32m";      // Green text
const string YELLOW = "\033[33m";     // Yellow text
const string BLUE = "\033[34m";       // Blue text
const string SKY_BLUE = "\033[36m";    // Sky Blue text
const string MAGENTA = "\033[35m";    // Magenta text
const string RESET = "\033[0m";       // Reset color

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

string Investment::getName() const {
    return name;
}

Constraints::Constraints(double budget, int riskTolerance)
    : budget(budget), riskTolerance(riskTolerance) {}

double Constraints::getBudget() const {
    return budget;
}

int Constraints::getRiskTolerance() const {
    return riskTolerance;
}

Constraints getUserConstraints() {
    double budget;
    int riskTolerance;

    cout << "\n\t\t\t\tIt requires some data before proceeding further. Please provide them.\n\n";

    // Input validation for budget
    while (true) {
        cout << "\n\t\t\t\t" << SKY_BLUE << "Enter total budget for investment: " << RESET;
        cin >> budget;

        // Check if the input is valid (a positive number)
        if (cin.fail() || budget <= 0) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            cout << "\t\t\t\t" << RED << "Invalid input. Please enter a positive number for the budget." << RESET << "\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            break;
        }
    }

    // Input validation for risk tolerance
    while (true) {
        cout << "\t\t\t\t" << SKY_BLUE << "Enter risk tolerance (1 = Low, 2 = Medium, 3 = High): " << RESET;
        cin >> riskTolerance;

        // Check if the input is valid (1, 2, or 3)
        if (cin.fail() || riskTolerance < 1 || riskTolerance > 3) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            cout << "\t\t\t\t" << RED << "Invalid input. Please enter 1, 2, or 3 for risk tolerance." << RESET << "\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            break;
        }
    }

    return Constraints(budget, riskTolerance);
}

