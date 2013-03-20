//ESTRUTURA PARA ARMAZENAR OS PARAMETROS
//RELATIVOS AOS DADOS
typedef struct _parametros{
	char *arq_entrada_1, *arq_entrada_2, *arq_saida;
	int NP, NT;
	float UNDEF;
} parametros;

//ESTRUTURA PARA ARMAZENAR OS PARAMETROS
//RELATIVOS A EXECUCAO
typedef struct _parametros_exec{
	int total_npos, npos_por_ciclo, total_ciclos,
		threads_por_bloco, blocos_por_grid;
	size_t tam_por_ciclo, mem_total, mem_free;
} parametros_exec;
