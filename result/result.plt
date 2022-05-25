set title "Ackley function" 
set output "output.png"
unset key
set view 70, 20, 1, 1
set xlabel "X axis" 
set ylabel "Y axis" 
set zlabel "Z axis" 
set xrange [-32.000000:32.000000]
set yrange [-32.000000:32.000000]
set ztics  norangelimit 0,2.5,25
set pm3d
set hidden3d
set dgrid3d 50,50 qnorm 4
splot "data.txt" using 1:2:3 with lines
