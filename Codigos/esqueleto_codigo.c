//VARIAVEIS GLOBAIS:
parametros param;
parametros_exec param_exec;

float *h_entrada = NULL;
float *h_saida = NULL;

float *d_entrada = NULL;
float *d_saida = NULL;

//DEFINICAO DO NUMERO DE THREADS POR BLOCO
#define THREADS_POR_BLOCO 64

void desaloca_variaveis(){
	if (h_entrada != NULL) free(h_entrada);
	if (h_saida != NULL) free(h_saida);

	if (d_entrada != NULL) cudaFree(d_entrada);
	if (d_saida != NULL) cudaFree(d_saida);
}

int calcula_pos_matriz(int NT, int p, int t){
	return (p*NT)+t;
}

void le_argumentos(int argc, char **argv, parametros *param) {
	if (argc-1 < 7){
		printf("PARAMETROS INVALIDOS!\n");
		exit(1);
	}
	param->arq_entrada_1=argv[1];
	param->arq_entrada_2=argv[2];
	param->arq_saida=argv[3];
	param->NP=atoi(argv[4])*atoi(argv[5]);
	param->NT=atoi(argv[6]);
	param->UNDEF=atof(argv[7]);
}

void le_matriz_entrada(char *arq_entrada, parametros param, float **d){
	int p,t,pos;
	FILE *arq;
	float *buffer;

	arq=fopen(arq_entrada,"rb");
	if (!arq){
		printf("Erro na abertura do arquivo de entrada!");
		desaloca_variaveis();
		exit (1);
	}

	buffer=(float*)malloc(param.NP*sizeof(float));

	(*d)=(float*)malloc((param.NP*param.NT)*sizeof(float));

	for (t=0;t<param.NT;t++){
		fread(buffer,sizeof(float),param.NP,arq);

		for(p=0;p<param.NP;p++){
			pos=calcula_pos_matriz(param.NT,p,t);
			(*d)[pos]=buffer[p];
		}
	}

	free(buffer);

	fclose(arq);
}

void salva_dados_saida(parametros param, float *s){
	FILE *arq;
	int p,t,pos;

	arq=fopen(param.arq_saida,"wb");
	if (!arq){
		printf("Erro na abertura do arquivo de saida!");
		desaloca_variaveis();
		exit (1);
	}

	for (t=0;t<param.NT;t++){
		for (p=0;p<param.NP;p++){
			pos=calcula_pos_matriz(param.NT,p,t);
			fwrite((s+pos),sizeof(float),1,arq);
		}
	}

	fclose(arq);
}

void calcula_parametros_execucao(parametros_exec *param_exec, int NP, int NT){

	int npos_por_ciclo;
	int total_ciclos;
	size_t tam_por_ciclo;

	total_ciclos=1;
	npos_por_ciclo=NP;

	cudaMemGetInfo(&param_exec->mem_free, &param_exec->mem_total);
		verifica_erro_cuda("cudaMemGetInfo",-1);

	tam_por_ciclo=(npos_por_ciclo*NT)*sizeof(float);
	while ( tam_por_ciclo > (param_exec->mem_free-50) ){
		total_ciclos=total_ciclos+1;
		npos_por_ciclo=ceil(NP/total_ciclos);
		tam_por_ciclo=(npos_por_ciclo*NT)*sizeof(float);
	}

	param_exec->npos_por_ciclo=npos_por_ciclo;
	param_exec->total_ciclos=total_ciclos;
	param_exec->tam_por_ciclo=tam_por_ciclo;
	param_exec->threads_por_bloco=THREADS_POR_BLOCO;
	param_exec->blocos_por_grid=(npos_por_ciclo+THREADS_POR_BLOCO-1)/THREADS_POR_BLOCO;

	//CALCULA O NUMERO TOTAL DE POSICOES QUE SERAO CALCULADAS
	// ESSE NUMERO PROVAVELMENTE SERA MAIOR QUE O NP,
	// POR ISSO NAO SE PODE ALOCAR EXATAMENTE O TAMANHO DA SAIDA ESPERADO.
	// TEM QUE ALOCAR ESSA MEMORIA A MAIS PARA GARANTIR
	// QUE NO ULTIMO CICLO NAO SEJA COPIADO DADOS ALEM DO QUE FOI ALOCADO
	param_exec->total_npos=param_exec->npos_por_ciclo*param_exec->total_ciclos;

	return;
}

__global__ void nome_funcao( <ARGUMENTOS> ){

int p = (blockDim.x * blockIdx.x) + threadIdx.x;
if (p >= total_pos) return;

int ini_seq=(p*NT);

<ALGORITMO>

}

int main(int argc, char **argv){

//VARIAVEIS AUXILIARES:
int ciclo;
int pos_inicio_copia_entrada, pos_inicio_copia_saida;

//LE OS ARGUMENTOS E OS DADOS DE ENTRADA
le_argumentos(argc,argv,&param);
le_dados_entrada(param,&h_entrada);

//******************************************************//
//EXECUCAO CUDA

//RESETA O DISPOSITIVO CUDA
cudaDeviceReset();

//CALCULA OS PARAMETROS DE EXECUCAO
calcula_parametros_execucao(param, &param_exec);

//ALOCA E COPIA O VETOR "WT"
cudaMalloc((void**)&d_wt, param_exec.mem_aux_por_ciclo);
cudaMemcpy(d_wt, h_wt, param_exec.mem_aux_por_ciclo,
           cudaMemcpyHostToDevice);

//ALOCA O ESPACO PARA OS DADOS DE ENTRADA E SAIDA NO DEVICE
cudaMalloc((void**)&d_entrada,param_exec.mem_entrada_por_ciclo);
cudaMalloc((void**)&d_saida, param_exec.mem_saida_por_ciclo);

//ALOCA NO HOST O ESPACO PARA A SAIDA (TOTAL)
h_saida=(float*)malloc(param_exec.mem_saida_total);

for (ciclo=0;ciclo<param_exec.total_ciclos;ciclo++){

	//CALCULA A POSICAO DE INICIO DA COPIA DOS DADOS DE ENTRADA
	pos_inicio_copia_entrada=(ciclo*param_exec.npos_por_ciclo)*param.NT;

	//COPIA OS DADOS DE ENTRADA
	cudaMemcpy(d_entrada,(h_entrada+pos_inicio_copia_entrada),
			param_exec.mem_entrada_por_ciclo, cudaMemcpyHostToDevice);

	//EXECUTA O FILTRO LANCZOS EM CUDA
	nome_funcao<<<param_exec.blocos_por_grid,
	              param_exec.threads_por_bloco>>>
	              ( <ARGUMENTOS> );

	//ESPERA O TERMINIO DA EXECUCAO DO DEVICE
	cudaDeviceSynchronize();

	//CALCULA A POSICAO DE INICIO DA COPIA DOS DADOS DE SAIDA
	pos_inicio_copia_saida=(ciclo*param_exec.npos_por_ciclo)*param.NT;

	//COPIA A SAIDA DO DEVICE PARA O HOST
	cudaMemcpy((h_saida+pos_inicio_copia_saida),d_saida,
			param_exec.mem_saida_por_ciclo, cudaMemcpyDeviceToHost);
}
//******************************************************//

salva_arq_saida(param, h_saida);

desaloca_variaveis();

return 0;
}
