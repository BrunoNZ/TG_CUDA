#set terminal postscript enhanced eps font 18
set terminal pngcairo size 1280,512 enhanced font 'Arial,20' dashed
set output "lanczos_tempos.png"

set size ratio 0.4

set ylabel "Tempo de Execucao"
set xlabel "Tamanho da serie"

set ydata time
set timefmt "%Mm%Ss"
set format y "%Mmin"

set xrange [1000:22000]
set xtics rotate by -45 (1000,3000,5000,7000,9000,11000,13000,15000,17000,19000,21000)

set key left

set style line 1 lt 1 lw 4 lc rgb "black"
set style line 2 lt 1 lw 4 lc rgb "blue"
set style line 3 lt 1 lw 4 lc rgb "red"
set style line 4 lt 2 lw 4 lc rgb "green"
set style line 5 lt 1 lw 4 lc rgb "dark-grey"
set style line 6 lt 1 lw 4 lc rgb "#1E90FF"

plot "../../Logs/Lanczos/processados/seq_uhura.lista" using 1:2 w l title "[SEQ] Intel I7" ls 1,\
	"../../Logs/Lanczos/processados/omp_servlab.lista" using 1:2 w l title "[OMP] Intel I5" ls 2,\
	"../../Logs/Lanczos/processados/omp_uhura.lista" using 1:2 w l title "[OMP] Intel I7" ls 3,\
	"../../Logs/Lanczos/processados/omp_priorat.lista" using 1:2 w l title "[OMP] AMD Opteron" ls 4,\
	"../../Logs/Lanczos/processados/cuda_9600gt_PP.lista" using 1:2 w l title "[CUDA] 9600GT" ls 5 ,\
	"../../Logs/Lanczos/processados/cuda_mccoy_PP.lista" using 1:2 w l title "[CUDA] GTX480" ls 6
	

