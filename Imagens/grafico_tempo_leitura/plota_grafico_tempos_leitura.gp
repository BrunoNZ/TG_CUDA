set encoding utf8
set terminal postscript enhanced eps font 20
#set terminal pngcairo size 1280,512 enhanced font 'Arial,20' dashed
set output "lanczos_tempos_leitura.eps"

set size ratio 0.4

set ylabel "Tempo de leitura dos dados"
set xlabel "Tamanho da série"

#set ydata time
#set timefmt "%Mm%Ss"
#set format y "%Ss"

#set xrange [5000:22000]
#set xtics rotate by -45 (1000,3000,5000,7000,9000,11000,13000,15000,17000,19000,21000)

set xtics rotate by -45

set key left

set style line 1 lt 1 lw 1 lc rgb "black"
set style line 2 lt 1 lw 1 lc rgb "blue"
set style line 3 lt 1 lw 1 lc rgb "red"
set style line 4 lt 1 lw 1 lc rgb "green"
set style line 5 lt 1 lw 1 lc rgb "gold"

set style data histogram
set style histogram
set style fill solid border
set boxwidth 0.75

set auto x
plot 	"../../Logs/Lanczos/processados/leitura-original_achel.lista_2" using 2:xtic(1) title "Método original" ls 1,\
	"../../Logs/Lanczos/processados/leitura_achel.lista_2" using 2:xtic(1) title "Método proposto" ls 2
	

