#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/utils.h"

using namespace std;

void insertDataIntoCSV(const string& filename) {
    ofstream file;
    file.open(filename, ios::app);

    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string name, type;
    double cost, expectedReturn, risk;

    cin.ignore();  

    cout << "Enter investment name: ";
    getline(cin, name);

    cout << "Enter investment cost: ";
    cin >> cost;

    cout << "Enter expected return: ";
    cin >> expectedReturn;

    cout << "Enter risk (as a decimal, e.g., 0.05 for 5%): ";
    cin >> risk;

    cin.ignore();

    cout << "Enter investment type: ";
    getline(cin, type);

    file << name << "," << cost << "," << expectedReturn << "," << risk << "," << type << endl;

    cout << "Investment data added successfully!" << endl;

    file.close();
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

        if (getline(iss, name, ',') &&
            (iss >> cost) &&
            (iss.ignore(), iss >> expectedReturn) &&
            (iss.ignore(), iss >> risk) &&
            (iss.ignore(), getline(iss, type))) {
            
            if (iss.fail()) {
                cerr << "Error parsing line: " << line << endl;
                continue;
            }
            
            investments.emplace_back(name, cost, expectedReturn, risk, type);
        } else {
            cerr << "Error parsing line: " << line << endl;
        }
    }

    file.close();
    return investments;
}

void displayAllInvestments(const string& filename) {
    vector<Investment> investments = readInvestmentData(filename);

    if (investments.empty()) {
        cout << "No investments found in the file." << endl;
        return;
    }

    cout << "\n===== All Investments =====\n";
    for (const auto& investment : investments) {
        investment.display();
    }
}
