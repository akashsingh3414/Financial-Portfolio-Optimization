#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include "dataTypes.h"

void insertDataIntoCSV(const std::string& filename);
std::vector<Investment> readInvestmentData(const std::string& filename);
void displayAllInvestments(const std::string& filename);

#endif // UTILS_H
