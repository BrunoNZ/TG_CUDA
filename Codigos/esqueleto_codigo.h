//ESTRUTURA PARA ARMAZENAR OS PARAMETROS
//RELATIVOS AOS DADOS
typedef struct _parametros{
	char *arq_entrada_1;
	char *arq_entrada_2;
	char *arq_saida;
	int NP;
	int NT;
	float UNDEF;
} parametros;

//ESTRUTURA PARA ARMAZENAR OS PARAMETROS
//RELATIVOS A EXECUCAO
typedef struct _parametros_exec{
	int total_npos;
	int npos_por_ciclo;
	int total_ciclos;
	int threads_por_bloco;
	int blocos_por_grid;
	size_t tam_por_ciclo;
	size_t mem_total;
	size_t mem_free;
} parametros_exec;
