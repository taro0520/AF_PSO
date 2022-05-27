set title "Ackley function" 
set terminal gif animate delay 20
set output "pso_2d.gif"
stats 'data_pso.txt' nooutput
set xlabel "X axis" 
set ylabel "Y axis" 
set xrange [-40.000000:40.000000]
set yrange [-40.000000:40.000000]
set xtics -40,10,40
set ytics -40,10,40
do for [i=0:100]{ plot "data_pso.txt" using 1:2 index(i) with point lt 7 ps 1}
# int(STATS_blocks-1)
