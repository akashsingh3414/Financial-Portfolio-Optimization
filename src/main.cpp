#include "../include/input.h"
#include "../include/knapsack.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    Constraints constraints = getUserConstraints();
    constraints.display();

    std::string filename = "../data/investments.csv";
    std::vector<Investment> investments = readInvestmentData(filename);

    std::cout << "\nInvestments:\n\n";
    for (const auto& investment : investments) {
        investment.display();
    }

    Knapsack knapsack;
    std::vector<Investment> optimizedInvestments = knapsack.optimize(investments, constraints.getBudget(), constraints.getRiskTolerance());

    knapsack.displaySelectedInvestments(optimizedInvestments);

    return 0;
}
