#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cstdlib>
#include "../include/dataTypes.h"
#include "../include/utils.h"
#include "../include/output.h"

using namespace std;

void groupInvestments(const vector<Investment>& investments, vector<pair<string, vector<double>>>& investmentData) {
    map<string, pair<double, double>> investmentSums; // (total cost, total return)
    map<string, int> investmentCounts;

    for (const auto& investment : investments) {
        string type = investment.getType();
        investmentSums[type].first += investment.getCost(); // Summing costs
        investmentSums[type].second += investment.getExpectedReturn(); // Summing expected returns
        investmentCounts[type]++;
    }

    for (const auto& entry : investmentSums) {
        string type = entry.first;
        double avgCost = entry.second.first / investmentCounts[type];
        double avgReturn = entry.second.second / investmentCounts[type];
        vector<double> temp;
        temp.emplace_back(avgCost);
        temp.emplace_back(avgReturn);
        temp.emplace_back(avgReturn - avgCost); // Calculate average profit
        investmentData.push_back(make_pair(type, temp));
    }
}

void writeInvestmentDataToFile(const vector<pair<string, vector<double>>>& investmentData, const string& filename) {
    ofstream dataFile(filename);
    if (dataFile) {
        for (const auto& investment : investmentData) {
            dataFile << "\"" << investment.first << "\" "
                     << investment.second[0] << " " // Average Cost
                     << investment.second[0] + investment.second[1] << " " // Average Return
                     << investment.second[1] << endl; // Average Profit
        }
    } else {
        cerr << "\t\t\t\tError opening file: " << filename << endl;
    }
}

void createGnuplotScriptForLineGraph(const string& dataFilename, const string& scriptFilename) {
    ofstream scriptFile(scriptFilename);

    if (!scriptFile.is_open()) {
        cerr << "\t\t\t\tError opening file for writing: " << scriptFilename << endl;
        return;
    }

    scriptFile << "set terminal png size 1400,1000\n";
    scriptFile << "set output 'data/imageInvestmentCostAndReturn.png'\n";
    scriptFile << "set title 'Investment Type vs Cost and Return'\n";
    scriptFile << "set xlabel 'Investment Type'\n";
    scriptFile << "set ylabel 'Value'\n";
    scriptFile << "set xtics rotate by -45\n";
    scriptFile << "set style data linespoints\n";
    scriptFile << "set lmargin 10\n";
    scriptFile << "set rmargin 10\n";
    scriptFile << "set key inside top right\n";
    scriptFile << "set grid\n";

    // Setting the y-range to accommodate both positive and negative values
    scriptFile << "set yrange [*:*]\n"; // This allows Gnuplot to automatically adjust the y-axis range

    scriptFile << "plot '" << dataFilename << "' using 2:xtic(1) title 'Average Cost' with linespoints lw 2 lc rgb 'red', \\\n";
    scriptFile << "     '" << dataFilename << "' using 3:xtic(1) title 'Average Return' with linespoints lw 2 lc rgb 'green', \\\n";
    scriptFile << "     '" << dataFilename << "' using 4:xtic(1) title 'Average Profit (over given period)' with linespoints lw 2 lc rgb 'blue' \n";
    scriptFile.close();
}

void plotInvestmentCostAndReturn(const vector<Investment>& investments) {
    string dataFilename = "data/investmentCostAndReturn.dat";  
    string scriptFilename = "data/plotInvestmentCostAndReturn.gp";

    vector<pair<string, vector<double>>> investmentData;

    groupInvestments(investments, investmentData);
    writeInvestmentDataToFile(investmentData, dataFilename);
    createGnuplotScriptForLineGraph(dataFilename, scriptFilename);

    string command = "gnuplot " + scriptFilename;
    system(command.c_str());

    system("start data/imageInvestmentCostAndReturn.png");

    cout << "\n\t\t\t\tPlot generated and saved as 'data/imageInvestmentCostAndReturn.png'.\n";
}

void plotInvestmentsVsReturn() {
    vector<Investment> investments = readInvestmentData("data/investments.csv");
    plotInvestmentCostAndReturn(investments);
}
