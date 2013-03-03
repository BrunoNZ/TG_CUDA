all:	mcarlo_tempos_cuda.png\
		mcarlo_speedup_cuda.png\
		mcarlo_tempos_omp.png\
		mcarlo_speedup_omp.png\
		mcarlo_tempos_omp_threads.png

mcarlo_tempos_cuda.png: plota_grafico_tempos_cuda.gp
	gnuplot plota_grafico_tempos_cuda.gp
	eog mcarlo_tempos_cuda.png

mcarlo_speedup_cuda.png: plota_grafico_speedup_cuda.gp
	gnuplot plota_grafico_speedup_cuda.gp
	eog mcarlo_speedup_cuda.png
	
mcarlo_tempos_omp.png: plota_grafico_tempos_omp.gp
	gnuplot plota_grafico_tempos_omp.gp
	eog mcarlo_tempos_omp.png

mcarlo_speedup_omp.png: plota_grafico_speedup_omp.gp
	gnuplot plota_grafico_speedup_omp.gp
	eog mcarlo_speedup_omp.png
	
mcarlo_tempos_omp_threads.png: plota_grafico_tempos_omp_threads.gp
	gnuplot plota_grafico_tempos_omp_threads.gp
	eog mcarlo_tempos_omp_threads.png
