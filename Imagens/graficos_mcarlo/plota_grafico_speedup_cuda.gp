#set terminal postscript enhanced eps font 18
set terminal pngcairo size 1280,512 enhanced font 'Arial,20'
set output "mcarlo_speedup_cuda.png"

set size ratio 0.4

set ylabel "Speedup"
set xlabel "Tamanho da serie / Numero de Permutacoes"


set xrange [1:16]
set xtics rotate by -45\
		(	"1000/1000" 1,"1000/3000" 2,"1000/5000" 3,"1000/7000" 4,"1000/9000" 5,\
			"3000/1000" 6,"3000/3000" 7,"3000/5000" 8,"3000/7000" 9,"3000/9000" 10,\
			"5000/1000" 11,"5000/3000" 12,"5000/5000" 13,"5000/7000" 14,"5000/9000" 15)

set key left

plot "../../Logs/MonteCarlo/processados/cuda_9600gt.speedup" using 1:2 title "NVidia 9600GT" w l lt 1 lw 4 lc 3
