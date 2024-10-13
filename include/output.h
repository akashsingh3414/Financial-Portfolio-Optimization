#ifndef OUTPUT_H
#define OUTPUT_H

#include <vector>
#include "dataTypes.h"

using namespace std;

void groupInvestments(const vector<Investment>& investments, vector<pair<string, vector<double>>>& investmentData);

void writeInvestmentDataToFile(const vector<pair<string, vector<double>>>& investmentData, const string& filename);

void createGnuplotScriptForLineGraph(const string& dataFilename, const string& scriptFilename);

void plotInvestmentCostAndReturn(const vector<Investment>& investments);

void plotInvestmentsVsReturn();

#endif // OUTPUT_H
