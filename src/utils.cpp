#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include "../include/utils.h"
#include "../include/dataTypes.h"
#include <limits> // For std::numeric_limits

using namespace std;

const string RED = "\033[31m";        // Red text
const string RESET = "\033[0m";       // Reset color

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
    vector<Investment> investments = readInvestmentData(filename);

    if (investments.empty()) {
        cout << "\t\t\t\t" << RED << "No investments found in the file." << RESET << endl;
        return;
    }

    // Define fixed maximum widths for the columns
    const int nameWidth = 30;
    const int costWidth = 10;
    const int expectedReturnWidth = 15;
    const int riskWidth = 6;
    const int typeWidth = 25;

    // Print header for the table
    cout << "\n\n\t\t\t\t.......................All Investments........................\n";
    cout << "\t\t" << string(102, '-') << "\n";  // Adjusted line width
    cout << "\t\t| " << std::setw(nameWidth) << "Name" 
         << " | " << std::setw(costWidth) << "Cost" 
         << " | " << std::setw(expectedReturnWidth) << "Expected Return" 
         << " | " << std::setw(riskWidth) << "Risk" 
         << " | " << std::setw(typeWidth) << "Type" << " |\n";
    cout << "\t\t" << string(102, '-') << "\n";  // Adjusted line width

    // Print investment details in a table format
    for (const auto& investment : investments) {
        cout << "\t\t| " << std::setw(nameWidth) << investment.getName() << " | "
             << std::fixed << std::setprecision(2) << std::setw(costWidth) << investment.getCost() << " | "
             << std::setw(expectedReturnWidth) << investment.getExpectedReturn() << " | "
             << std::setw(riskWidth) << investment.getRisk() << " | "
             << std::setw(typeWidth) << investment.getType() << " |\n";
    }
    cout << "\t\t" << string(102, '-') << "\n";
}

void displaySelectedInvestments(const vector<Investment>& selectedInvestments) {
    if (!selectedInvestments.empty()) {
        // Define fixed maximum widths for the columns
        const int nameWidth = 25;
        const int costWidth = 10;
        const int expectedReturnWidth = 15;
        const int riskWidth = 6;
        const int typeWidth = 20;

        // Print header for the table
        cout << "\n\n\t\t\t\t.......................Selected Investments....................\n";
        cout << "\t\t" << string(102, '-') << "\n";
        cout << "\t\t| " << std::setw(nameWidth) << "Name" 
             << " | " << std::setw(costWidth) << "Cost" 
             << " | " << std::setw(expectedReturnWidth) << "Expected Return" 
             << " | " << std::setw(riskWidth) << "Risk" 
             << " | " << std::setw(typeWidth) << "Type" << " |\n";
        cout << "\t\t" << string(102, '-') << "\n";  // Adjusted line width

        // Print selected investment details in a table format
        for (const auto& investment : selectedInvestments) {
            cout << "\t\t| " << std::setw(nameWidth) << investment.getName() << " | "
                 << std::fixed << std::setprecision(2) << std::setw(costWidth) << investment.getCost() << " | "
                 << std::setw(expectedReturnWidth) << investment.getExpectedReturn() << " | "
                 << std::setw(riskWidth) << investment.getRisk() << " | "
                 << std::setw(typeWidth) << investment.getType() << " |\n";
        }
        cout << "\t\t" << string(102, '-') << "\n";  // Adjusted line width
    } else {
        cout << "\t\t\t\t" << RED << "No suitable investments found within the budget." << RESET << endl;
    }
}
