__global__ void nome_algoritmo( <ARGUMENTOS> ){

int p = (blockDim.x * blockIdx.x) + threadIdx.x;
if (p >= total_pos) return;

int ini_seq=(p*NT);

<ALGORITMO>
}
