set encoding utf8
set terminal postscript enhanced eps font 20
#set terminal pngcairo size 1280,512 enhanced font 'Arial,20'
set output "mcarlo_speedup_cuda.eps"

set size ratio 0.4

set ylabel "Speedup"
set xlabel "Tamanho da série / Número de permutações"

set yrange [0:10]
set xrange [1:16]
set xtics rotate by -45\
		(	"1000/1000" 1,"1000/3000" 2,"1000/5000" 3,"1000/7000" 4,"1000/9000" 5,\
			"3000/1000" 6,"3000/3000" 7,"3000/5000" 8,"3000/7000" 9,"3000/9000" 10,\
			"5000/1000" 11,"5000/3000" 12,"5000/5000" 13,"5000/7000" 14,"5000/9000" 15)

set key left

set style line 1 lt 1 lw 4 lc rgb "black"
set style line 2 lt 1 lw 4 lc rgb "blue"
set style line 3 lt 1 lw 4 lc rgb "red"
set style line 4 lt 1 lw 4 lc rgb "green"
set style line 5 lt 1 lw 4 lc rgb "dark-grey"

U=value(1)
plot 	"../../Logs/MonteCarlo/processados/seq_uhura.lista_2" using 1:4 w l title "[SEQ] Intel I7" ls 1,\
	"../../Logs/MonteCarlo/processados/cuda_9600gt.speedup" using 1:2 w l title "[CUDA] NVidia 9600GT" ls 2 ,\
	"../../Logs/MonteCarlo/processados/cuda_orval.speedup" using 1:2 w l title "[CUDA] NVidia Tesla C1060" ls 3 ,\
	"../../Logs/MonteCarlo/processados/cuda_achel.speedup" using 1:2 w l title "[CUDA] NVidia Tesla C2050" ls 4
