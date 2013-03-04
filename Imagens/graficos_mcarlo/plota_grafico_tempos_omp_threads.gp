#set terminal postscript enhanced eps font 18
set terminal pngcairo size 1280,768 enhanced font 'Arial,20'
set output "mcarlo_tempos_omp_threads.png"

set size ratio 0.6

set ylabel "Tempo de Execucao"
set xlabel "Tamanho da serie / Numero de Permutacoes"

set ydata time
set timefmt "%Mm%Ss"
set format y "%M"
set yrange ["0:0":"60:0"]
set ytics ("0m" "0:0", "10m" "10:0", "20m" "20:0", "30m" "30:0", "40m" "40:0", "50m" "50:0", "60m" "60:0" )

set xrange [1:16]
set xtics rotate by -45\
		(	"1000/1000" 1,"1000/3000" 2,"1000/5000" 3,"1000/7000" 4,"1000/9000" 5,\
			"3000/1000" 6,"3000/3000" 7,"3000/5000" 8,"3000/7000" 9,"3000/9000" 10,\
			"5000/1000" 11,"5000/3000" 12,"5000/5000" 13,"5000/7000" 14,"5000/9000" 15)

set key left

plot "../../Logs/MonteCarlo/processados/seq_uhura.lista" using 1:3 title "[SEQ] Intel I7" w l lt 1 lw 4 lc 0,\
	"../../Logs/MonteCarlo/processados/omp_uhura_2threads.lista" using 1:3 title "[OMP] Intel I7 (2 Threads)" w l lt 1 lw 4 lc 1,\
	"../../Logs/MonteCarlo/processados/omp_uhura_4threads.lista" using 1:3 title "[OMP] Intel I7 (4 Threads)" w l lt 1 lw 4 lc 2,\
	"../../Logs/MonteCarlo/processados/omp_uhura_8threads.lista" using 1:3 title "[OMP] Intel I7 (8 Threads)" w l lt 1 lw 4 lc 3
