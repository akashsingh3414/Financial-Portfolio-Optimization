set terminal png size 1400,1000
set output '../data/imageInvestmentCostAndReturn.png'
set title 'Investment Type vs Cost and Return (for given period)'
set xlabel 'Investment Type'
set ylabel 'Value'
set xtics rotate by -45
set style data linespoints
set key outside
set xtics
plot '../data/investmentCostAndReturn.dat' using 2:xtic(1) title 'Average Cost' with linespoints lw 2 lc rgb 'red', \
     '../data/investmentCostAndReturn.dat' using 3:xtic(1) title 'Average Return' with linespoints lw 2 lc rgb 'green', \
     '../data/investmentCostAndReturn.dat' using 4:xtic(1) title 'Average Profit(over given period)' with linespoints lw 2 lc rgb 'blue' 
