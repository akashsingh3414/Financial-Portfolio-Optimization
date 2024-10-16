set terminal png size 1400,1000
set output 'data/imageInvestmentCostAndReturn.png'
set title 'Investment Type vs Cost and Return'
set xlabel 'Investment Type'
set ylabel 'Value'
set xtics rotate by -45
set style data linespoints
set lmargin 10
set rmargin 10
set key inside top right
set grid
set yrange [*:*]
plot 'data/investmentCostAndReturn.dat' using 2:xtic(1) title 'Average Cost' with linespoints lw 2 lc rgb 'red', \
     'data/investmentCostAndReturn.dat' using 3:xtic(1) title 'Average Return' with linespoints lw 2 lc rgb 'green', \
     'data/investmentCostAndReturn.dat' using 4:xtic(1) title 'Average Profit (over given period)' with linespoints lw 2 lc rgb 'blue' 
