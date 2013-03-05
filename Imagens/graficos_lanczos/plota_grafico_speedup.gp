#set terminal postscript enhanced eps font 18
set terminal pngcairo size 1280,512 enhanced font 'Arial,20' dashed
set output "lanczos_speedup.png"

set size ratio 0.4

set ylabel "Speedup"
set xlabel "Quantidade de valores na serie de tempo"

set xrange [1000:22000]
set xtics rotate by -45 (1000,3000,5000,7000,9000,11000,13000,15000,17000,19000,21000)

set key left

set style line 1 lt 1 lw 4 lc rgb "black"
set style line 2 lt 1 lw 4 lc rgb "blue"
set style line 3 lt 1 lw 4 lc rgb "red"
set style line 4 lt 2 lw 4 lc rgb "green"
set style line 5 lt 1 lw 4 lc rgb "dark-grey"
set style line 6 lt 1 lw 4 lc rgb "#1E90FF"

plot "../../Logs/Lanczos/processados/omp_servlab.speedup" using 1:2 w l title "[OMP] Intel I5" ls 2 ,\
	"../../Logs/Lanczos/processados/omp_uhura.speedup" using 1:2 w l title "[OMP] Intel I7" ls 3 ,\
	"../../Logs/Lanczos/processados/omp_priorat.speedup" using 1:2 w l title "[OMP] AMD Opteron" ls 4 ,\
	"../../Logs/Lanczos/processados/cuda_9600gt_PP.speedup" using 1:2 w l title "[CUDA] 9600GT" ls 5 ,\
	"../../Logs/Lanczos/processados/cuda_mccoy_PP.speedup" using 1:2 w l title "[CUDA] GTX480" ls 6
