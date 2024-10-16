set terminal png size 800,600
set output 'data/imageReturnComparison.png'
set title 'Maximum Returns Comparison'
set xlabel 'Algorithm'
set ylabel 'Maximum Return'
set xtics ('Knapsack' 1, 'DP with Risk' 2, 'DP without Risk' 3)
set style fill solid
set boxwidth 0.5
set key outside right
plot 'data/returnsComparison.dat' using 1:2 with boxes title 'Maximum Return'
