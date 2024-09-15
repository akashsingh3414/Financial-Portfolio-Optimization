# Financial Portfolio Optimization Project (C++)

## Overview

This project provides an optimized solution for financial portfolio selection using different algorithmic techniques. The objective is to select a set of investments that maximize returns while adhering to constraints such as budget and risk tolerance.

## Input

- **Constraints**: 
  - Budget
  - Risk Type
  
- **Investment Dataset**:
  - Name
  - Cost
  - Return
  - Risk (0-1 scale)
  - Type (investment category)

## Features

1. **Knapsack and Greedy Algorithm (High Return-to-Cost Ratio)**:
   - Uses the knapsack algorithm to select an optimized set of investments based on the highest return-to-cost ratio.
   - The greedy algorithm also runs to offer a comparative set.
   - Both algorithms respect the input constraints of budget and risk type.

2. **Dynamic Programming for Maximum Return**:
   - This feature provides the most optimized result set, maximizing the return while adhering to constraints.
   - It avoids considering multiple periods for simplicity and focuses solely on maximizing returns in a single period.

3. **Filtering and Sorting**:
   - Filter and sort the investment dataset based on:
     - High return
     - Low cost
     - Low risk

4. **Graphical Visualization with Gnuplot**:
   - Plots a graph showing grouped investments by type.
   - Displays average cost, average return, and profit generated for each type using Gnuplot.

## How to Run

1. Compile the project using your preferred C++ compiler.
2. Input the investment dataset and define the constraints (budget, risk type).
3. Choose the desired feature to run: knapsack, dynamic programming, filtering/sorting, or plotting.
4. For graphical output, ensure Gnuplot is installed on your system.

## Dependencies

- C++ compiler
- Gnuplot (for graphical visualization)

## License

MIT License

---

This project simplifies financial portfolio optimization, offering solutions ranging from quick, ratio-based selections to more complex dynamic programming models, all while considering key constraints like budget and risk.
