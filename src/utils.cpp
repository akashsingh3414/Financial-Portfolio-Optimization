#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include "../include/utils.h"
#include "../include/dataTypes.h"
#include <limits> // For numeric_limits
#include <algorithm>  // For max

using namespace std;

const string RED = "\033[31m";        // Red text
const string RESET = "\033[0m";       // Reset color
const string GREEN = "\033[32m";       // Green text

double getPositiveDouble(const string& prompt) {
    double value;
    while (true) {
        cout << "\t\t\t\t" << prompt;
        cin >> value;

        // Check if input is valid
        if (cin.fail() || value <= 0.0) {
            cin.clear(); // Clear the fail state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            cout << RED << "\t\t\t\tInvalid input. Please enter a positive number." << RESET << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            return value; // Return valid input
        }
    }
}

double getAnyDouble(const string& prompt) {
    double value;
    while (true) {
        cout << "\t\t\t\t" << prompt;
        cin >> value;

        // Check if input is valid
        if (cin.fail()) {
            cin.clear(); // Clear the fail state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            cout << RED << "\t\t\t\tInvalid input. Please enter a valid number." << RESET << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            return value; // Return valid input
        }
    }
}

double getRisk() {
    double risk;
    while (true) {
        cout << "\t\t\t\tEnter risk (between 0 and 1): ";
        cin >> risk;

        // Check if input is valid
        if (cin.fail() || risk < 0.0 || risk > 1.0) {
            cin.clear(); // Clear the fail state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            cout << RED << "\t\t\t\tInvalid input. Please enter a risk value between 0 and 1." << RESET << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            return risk; // Return valid input
        }
    }
}

void insertDataIntoCSV(const string& filename) {
    ofstream file(filename, ios::app);

    if (!file.is_open()) {
        cerr << "\t\t\t\t" << RED << "Error opening file: " << filename << RESET << "\n";
        return;
    }

    file.seekp(0, ios::end);
    if (file.tellp() > 0) {
        file << '\n';
    }

    string name, type;
    double cost, expectedReturn, risk;

    // Add a line to clear any previous input before asking for name
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer before getline

    cout << "\t\t\t\tEnter investment name: ";
    getline(cin, name);

    cost = getPositiveDouble("Enter investment cost: ");
    expectedReturn = getAnyDouble("Enter expected return (can be negative): ");
    risk = getRisk(); // Use the new function to get risk

    cout << "\t\t\t\tEnter investment type: ";
    getline(cin, type);

    file << name << "," << cost << "," << expectedReturn << "," << risk << "," << type;

    cout << "\n\t\t\t\tInvestment data added successfully!" << endl;

    file.close();
}

vector<Investment> readInvestmentData(const string& filename) {
    vector<Investment> investments;
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cerr << "\t\t\t\t" << RED << "Error opening file: " << filename << RESET << "\n";
        return investments;
    }

    while (getline(file, line)) {
        size_t pos = 0;
        string token;
        vector<string> tokens;

        while ((pos = line.find(',')) != string::npos) {
            token = line.substr(0, pos);
            tokens.push_back(token);
            line.erase(0, pos + 1);
        }
        tokens.push_back(line);

        if (tokens.size() != 5) {
            cerr << "\t\t\t\t" << RED << "Error parsing line: " << line << RESET << "\n";
            continue;
        }

        try {
            string name = tokens[0];
            double cost = stod(tokens[1]);
            double expectedReturn = stod(tokens[2]);
            double risk = stod(tokens[3]);
            string type = tokens[4];

            investments.emplace_back(name, cost, expectedReturn, risk, type);
        } catch (const invalid_argument& e) {
            cerr << "\t\t\t\t" << RED << "Error parsing line: " << e.what() << RESET << "\n";
        }
    }

    file.close();
    return investments;
}

void displayAllInvestments(const string& filename) {
    vector<Investment> investments = readInvestmentData(filename);  // Assuming you have this function

    if (investments.empty()) {
        cout << "\t\t\t\t" << RED << "No investments found in the file." << RESET << endl;
        return;
    }

    // Calculate maximum lengths for dynamic column widths
    int nameWidth = 4; // "Name"
    int costWidth = 4; // "Cost"
    int expectedReturnWidth = 15; // "Expected Return"
    int riskWidth = 4; // "Risk"
    int typeWidth = 4; // "Type"

    int totalInvestments = 0;

    for (const auto& investment : investments) {
        nameWidth = max(nameWidth, static_cast<int>(investment.getName().size()));
        costWidth = max(costWidth, static_cast<int>(to_string(static_cast<int>(investment.getCost())).size() + 3));  // account for decimals
        expectedReturnWidth = max(expectedReturnWidth, static_cast<int>(to_string(static_cast<int>(investment.getExpectedReturn())).size() + 3));  // account for decimals
        riskWidth = max(riskWidth, static_cast<int>(to_string(static_cast<int>(investment.getRisk() * 100)).size() + 3));  // account for decimals
        typeWidth = max(typeWidth, static_cast<int>(investment.getType().size()));

        totalInvestments++;
    }

    // Print header for the table
    cout << "\n\n\t\t\t" << string((nameWidth + costWidth + expectedReturnWidth + riskWidth + typeWidth + 2) / 2, '.') 
     << "All Investments" 
     << string((nameWidth + costWidth + expectedReturnWidth + riskWidth + typeWidth + 2) / 2, '.') << "\n";    cout << "\t\t\t" << string(nameWidth + costWidth + expectedReturnWidth + riskWidth + typeWidth + 16, '-') << "\n";
    cout << "\t\t\t| " << left << setw(nameWidth) << "Name" 
              << " | " << setw(costWidth) << "Cost" 
              << " | " << setw(expectedReturnWidth) << "Expected Return" 
              << " | " << setw(riskWidth) << "Risk" 
              << " | " << setw(typeWidth) << "Type" << " |\n";
    cout << "\t\t\t" << string(nameWidth + costWidth + expectedReturnWidth + riskWidth + typeWidth + 16, '-') << "\n";

    // Print investment details in a table format
    for (const auto& investment : investments) {
        cout << "\t\t\t| " << left << setw(nameWidth) << investment.getName() << " | "
                  << fixed << setprecision(2) << setw(costWidth) << investment.getCost() << " | "
                  << setw(expectedReturnWidth) << investment.getExpectedReturn() << " | "
                  << setw(riskWidth) << investment.getRisk() << " | "
                  << setw(typeWidth) << investment.getType() << " |\n";
    }
    cout << "\t\t\t" << string(nameWidth + costWidth + expectedReturnWidth + riskWidth + typeWidth + 16, '-') << "\n";

    cout << "\n\t\t\t\t" << GREEN << totalInvestments << " investment(s) available" << RESET << endl;
}

void displaySelectedInvestments(const vector<Investment>& selectedInvestments) {
    if (!selectedInvestments.empty()) {
        
        // Calculate maximum lengths for dynamic column widths
        int nameWidth = 4; // "Name"
        int costWidth = 4; // "Cost"
        int expectedReturnWidth = 15; // "Expected Return"
        int riskWidth = 4; // "Risk"
        int typeWidth = 4; // "Type"

        int totalInvestments = 0;

        for (const auto& investment : selectedInvestments) {
            nameWidth = max(nameWidth, static_cast<int>(investment.getName().size()));
            costWidth = max(costWidth, static_cast<int>(to_string(static_cast<int>(investment.getCost())).size() + 3));  // account for decimals
            expectedReturnWidth = max(expectedReturnWidth, static_cast<int>(to_string(static_cast<int>(investment.getExpectedReturn())).size() + 3));  // account for decimals
            riskWidth = max(riskWidth, static_cast<int>(to_string(static_cast<int>(investment.getRisk() * 100)).size() + 3));  // account for decimals
            typeWidth = max(typeWidth, static_cast<int>(investment.getType().size()));
            
            totalInvestments++;
        }

        // Print header for the table
        cout << "\n\n\t\t\t" << string((nameWidth + costWidth + expectedReturnWidth + riskWidth + typeWidth - 4) / 2, '.') 
        << "Selected Investments" 
        << string((nameWidth + costWidth + expectedReturnWidth + riskWidth + typeWidth - 4) / 2, '.') << "\n";
        cout << "\t\t\t" << string(nameWidth + costWidth + expectedReturnWidth + riskWidth + typeWidth + 16, '-') << "\n";
        cout << "\t\t\t| " << left << setw(nameWidth) << "Name" 
                  << " | " << setw(costWidth) << "Cost" 
                  << " | " << setw(expectedReturnWidth) << "Expected Return" 
                  << " | " << setw(riskWidth) << "Risk" 
                  << " | " << setw(typeWidth) << "Type" << " |\n";
        cout << "\t\t\t" << string(nameWidth + costWidth + expectedReturnWidth + riskWidth + typeWidth + 16, '-') << "\n";

        // Print selected investment details in a table format
        for (const auto& investment : selectedInvestments) {
            cout << "\t\t\t| " << left << setw(nameWidth) << investment.getName() << " | "
                      << fixed << setprecision(2) << setw(costWidth) << investment.getCost() << " | "
                      << setw(expectedReturnWidth) << investment.getExpectedReturn() << " | "
                      << setw(riskWidth) << investment.getRisk() << " | "
                      << setw(typeWidth) << investment.getType() << " |\n";
        }
        cout << "\t\t\t" << string(nameWidth + costWidth + expectedReturnWidth + riskWidth + typeWidth + 16, '-') << "\n";
        cout << "\n\t\t\t\t" << GREEN << totalInvestments << " investment(s) selected" << RESET << endl;
    } else {
        cout << "\t\t\t\t" << RED << "No suitable investments found within the budget." << RESET << endl;
    }
}
