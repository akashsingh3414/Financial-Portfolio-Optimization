#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cstdlib> 
#include "../include/dataTypes.h"
#include "../include/utils.h"
#include "../include/output.h"

using namespace std;

void groupInvestments(const vector<Investment>& investments, vector<pair<string, vector<double>>>& investmentData, const Constraints& constraints) {
    map<string, pair<double, double>> investmentSums;
    map<string, int> investmentCounts;
    for (const auto& investment : investments) {
        string type = investment.getType();
        investmentSums[type].first += investment.getCost();
        investmentSums[type].second += investment.getCost() + investment.getExpectedReturn();
        investmentCounts[type]++;
    }

    for (const auto& entry : investmentSums) {
        string type = entry.first;
        double avgCost = entry.second.first / investmentCounts[type];
        double avgCostPlusReturn = entry.second.second / investmentCounts[type];
        vector<double> temp;
        temp.emplace_back(avgCost);
        temp.emplace_back(avgCostPlusReturn);
        investmentData.push_back(make_pair(type, temp));
    }
}

void writeInvestmentDataToFile(const vector<pair<string, vector<double>>>& investmentData, const string& filename) {
    ofstream dataFile(filename);
    if (dataFile) {
        for (const auto& investment : investmentData) {
            dataFile << "\"" << investment.first << "\" " << investment.second[0] << " " << investment.second[1] << " " << investment.second[1] - investment.second[0] << endl;
        }
    } else {
        cerr << "\t\t\t\t\tError opening file: " << filename << endl;
    }
}

void createGnuplotScriptForLineGraph(const string& dataFilename, const string& scriptFilename) {
    ofstream scriptFile(scriptFilename);

    if (!scriptFile.is_open()) {
        cerr << "\t\t\t\t\tError opening file for writing: " << scriptFilename << endl;
        return;
    }

    scriptFile << "set terminal png size 1400,1000\n";
    scriptFile << "set output '../data/imageInvestmentCostAndReturn.png'\n";
    scriptFile << "set title 'Investment Type vs Cost and Return (for given period)'\n";
    scriptFile << "set xlabel 'Investment Type'\n";
    scriptFile << "set ylabel 'Value'\n";
    scriptFile << "set xtics rotate by -45\n";
    scriptFile << "set style data linespoints\n";
    scriptFile << "set key outside\n";
    scriptFile << "set xtics\n";
    scriptFile << "plot '" << dataFilename << "' using 2:xtic(1) title 'Average Cost' with linespoints lw 2 lc rgb 'red', \\\n";
    scriptFile << "     '" << dataFilename << "' using 3:xtic(1) title 'Average Return' with linespoints lw 2 lc rgb 'green', \\\n";
    scriptFile << "     '" << dataFilename << "' using 4:xtic(1) title 'Average Profit(over given period)' with linespoints lw 2 lc rgb 'blue' \n";
    
    scriptFile.close();
}

void plotInvestmentCostAndReturn(const vector<Investment>& investments, const Constraints& constraints) {
    string dataFilename = "../data/investmentCostAndReturn.dat";  
    string scriptFilename = "../data/plotInvestmentCostAndReturn.gp";

    vector<pair<string, vector<double>>> investmentData;

    groupInvestments(investments, investmentData, constraints);
    writeInvestmentDataToFile(investmentData, dataFilename);
    createGnuplotScriptForLineGraph(dataFilename, scriptFilename);

    string command = "gnuplot " + scriptFilename;
    system(command.c_str());

    cout << "\n\t\t\t\tPlot generated and saved as '../data/imageInvestmentCostAndReturn.png'.\n";
}

void plotInvestmentsVsReturn(const Constraints& constraints) {
    vector<Investment> investments = readInvestmentData("../data/investments.csv");
    plotInvestmentCostAndReturn(investments, constraints);
}
