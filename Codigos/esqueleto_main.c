int main(int argc, char **argv){

//VARIAVEIS AUXILIARES:
int ciclo, pos_inicio_copia_entrada, pos_inicio_copia_saida;

le_argumentos(argc,argv,&param);
le_dados_entrada(param,&h_entrada);

calcula_parametros_execucao(param, &param_exec);

cudaDeviceReset();

cudaMalloc((void**)&d_entrada,param_exec.mem_entrada_por_ciclo);
cudaMalloc((void**)&d_saida, param_exec.mem_saida_por_ciclo);

h_saida=(float*)malloc(param_exec.mem_saida_total);

for (ciclo=0;ciclo<param_exec.total_ciclos;ciclo++){

	pos_inicio_copia_entrada=(ciclo*param_exec.npos_por_ciclo)*param.NT;

	cudaMemcpy(d_entrada,(h_entrada+pos_inicio_copia_entrada),
			param_exec.mem_entrada_por_ciclo, cudaMemcpyHostToDevice);

	nome_algoritmo <<<param_exec.blocos_por_grid,
					param_exec.threads_por_bloco>>>
					( <ARGUMENTOS> );
	cudaDeviceSynchronize();

	//IGUAL AO DE ENTRADA POIS NESSE CASO A SAIDA TAMBEM E' UMA SERIE
	pos_inicio_copia_saida=(ciclo*param_exec.npos_por_ciclo)*param.NT;

	cudaMemcpy((h_saida+pos_inicio_copia_saida),d_saida,
			param_exec.mem_saida_por_ciclo, cudaMemcpyDeviceToHost);
}

salva_arq_saida(param, h_saida);
return 0;
}
