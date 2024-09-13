#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../include/utils.h"
#include "../include/dataTypes.h"

using namespace std;

void insertDataIntoCSV(const string& filename) {
    ofstream file(filename, ios::app);

    if (!file.is_open()) {
        cerr << "\t\t\t\t\tError opening file: " << filename << endl;
        return;
    }

    file.seekp(0, ios::end);
    if (file.tellp() > 0) {
        file << '\n';
    }

    string name, type;
    double cost, expectedReturn, risk;

    cin.ignore();

    cout << "\t\t\t\t\tEnter investment name: ";
    getline(cin, name);

    cout << "\t\t\t\t\tEnter investment cost: ";
    cin >> cost;

    cout << "\t\t\t\t\tEnter expected return: ";
    cin >> expectedReturn;

    cout << "\t\t\t\t\tEnter risk (as a decimal, e.g., 0.05 for 5%): ";
    cin >> risk;

    cin.ignore();

    cout << "\t\t\t\t\tEnter investment type: ";
    getline(cin, type);

    file << name << "," << cost << "," << expectedReturn << "," << risk << "," << type;

    cout << "\t\t\t\t\tInvestment data added successfully!" << endl;

    file.close();
}

vector<Investment> readInvestmentData(const string& filename) {
    vector<Investment> investments;
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cerr << "\t\t\t\t\tError opening file: " << filename << endl;
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
            cerr << "\t\t\t\t\tError parsing line: " << line << endl;
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
            cerr << "\t\t\t\t\tError parsing line: " << e.what() << endl;
        }
    }

    file.close();
    return investments;
}

void displayAllInvestments(const string& filename) {
    vector<Investment> investments = readInvestmentData(filename);

    if (investments.empty()) {
        cout << "\t\t\t\t\tNo investments found in the file." << endl;
        return;
    }

    cout << "\n\n\t\t\t\t.......................All Investments........................\n\n";
    for (const auto& investment : investments) {
        investment.display();
    }
}

void displaySelectedInvestments(const vector<Investment>& selectedInvestments) {
    if (!selectedInvestments.empty()) {
        for (const auto& investment : selectedInvestments) {
            investment.display();
        }
    } else {
        cout << "\t\t\t\t\tNo suitable investments found within the budget." << endl;
    }
}