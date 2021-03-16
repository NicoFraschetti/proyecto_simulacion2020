#Set linestyles
set style line 1 \
	linecolor rgb '#0060ad' \
        linetype 1 linewidth 1 \
	    pointtype 7 pointsize 1
set style line 2 \
	linecolor rgb '#DC143C' \
        linetype 1 linewidth 1 \
	pointtype 7 pointsize 1
#Set ranges
set xrange[0:1000]
set yrange[0:10]
#Set names
set xlabel "Tiempo"
set ylabel "Piso Ascensor"
set term x11 title "Trayectoria Ascensor 1"
#Plot
plot  'output/trayectoriaA1.txt' using 2:1 with linespoints linestyle 1
#new window
set term x11 1
#set ranges
set xrange[0:1000]
set yrange[0:10]
#Set names
set xlabel "Tiempo"
set ylabel "Piso Ascensor"
set term x11 title "Trayectoria Ascensor 2"
#Plot
plot  'output/trayectoriaA2.txt' using 2:1 with linespoints linestyle 2

