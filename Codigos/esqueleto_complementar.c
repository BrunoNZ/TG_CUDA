#include "esqueleto_codigo.h"

//DEFINICAO DO NUMERO DE THREADS POR BLOCO
#define THREADS_POR_BLOCO 16

//VARIAVEIS GLOBAIS:
parametros param;
parametros_exec param_exec;
float *h_entrada = NULL;
float *h_saida = NULL;
float *d_entrada = NULL;
float *d_saida = NULL;

void le_argumentos(int argc, char **argv, parametros *param) {
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

void calcula_parametros_execucao(parametros_exec *param_exec, int NP, int NT){

	int npos_por_ciclo, total_ciclos;
	size_t tam_por_ciclo;

	total_ciclos=1;
	npos_por_ciclo=NP;

	cudaMemGetInfo(&param_exec->mem_free, &param_exec->mem_total);

	//FOI DECREMENTADO UMA QUANTIA DO VALOR TOTAL DE MEMORIA LIVRE
	//PARA QUE NAO SEJA USADO 100% DA MEMORIA DISPONIVEL, POR
	//UMA QUESTAO DE ESTABILIDADE. ISSO PODE CAUSAR TRAVAMENTOS.
	//ESSE VALOR PODE SER ALTERADO.
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
	//ESSE NUMERO PROVAVELMENTE SERA MAIOR QUE O NP,
	//POR ISSO NAO SE PODE ALOCAR EXATAMENTE O TAMANHO DA SAIDA ESPERADO.
	//TEM QUE ALOCAR ESSA MEMORIA A MAIS PARA GARANTIR
	//QUE NO ULTIMO CICLO NAO SEJA COPIADO DADOS ALEM DO QUE FOI ALOCADO
	param_exec->total_npos=param_exec->npos_por_ciclo*param_exec->total_ciclos;

	return;
}

int calcula_pos_matriz(int NT, int p, int t){
	return (p*NT)+t;
}

void salva_dados_saida(parametros param, float *s){
	FILE *arq;
	int p,t,pos;

	arq=fopen(param.arq_saida,"wb");

	for (t=0;t<param.NT;t++){
		for (p=0;p<param.NP;p++){
			pos=calcula_pos_matriz(param.NT,p,t);
			fwrite((s+pos),sizeof(float),1,arq);
		}
	}
	fclose(arq);
}
