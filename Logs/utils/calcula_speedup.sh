#!/bin/bash

# O **PRIMEIRO** ARQUIVO DE ENTRADA DEVE CONTER UMA LISTA DE DUAS COLUNAS,
# ONDE A PRIMEIRA CONTEM OS PARAMETROS DE EXECUCAO (OS QUAIS
# SERAO IGNORADOS NESSE CALCULO) E NA SEGUNDA OS TEMPOS DE 
# EXECUCAO DA EXECUCAO QUE SERA TOMADA COMO A ***BASE DO SPEEDUP***
#
# O ***SEGUNDO*** ARQUIVO DE ENTRADA DEVE CONTER UMA LISTA COM AS MESMAS
# DUAS COLUNAS DO PRIMEIRO, E ***EXATAMENTE*** A MESMA QUANTIDADE DE LINHAS
# CONTENDO NA PRIMEIRA COLUNA ***EXATAMENTE OS MESMOS PARAMETROS CONTIDOS
# NO PRIMEIRO ARQUIVO, E NA SEGUNDA OS TEMPOS RELATIVOS A EXECUCAO
# A QUAL SERA CALCULADO O SPEEDUP

ARQ_BASE_SPEEDUP=$1
ARQ_EXEC_SPEEDUP=$2

if [[ $# != 2 ]]; then
	echo -e "Parametros errados! Utilze:"
	echo -e "$0 [ARQ_BASE_SPEEDUP] [ARQ_EXEC_SPEEDUP]"
	echo -e ""
	exit 1
fi

LISTA_PARAM=$(cat $ARQ_BASE_SPEEDUP | tr -s "\t" " " | cut -d " " -f1)

for P in $LISTA_PARAM; do
	TEMPO_BASE=$(grep "^${P}" $ARQ_BASE_SPEEDUP | tr -s "\t" " " | cut -d " " -f2 | sed "s/m/#/g; s/s//g")
	TEMPO_EXEC=$(grep "^${P}" $ARQ_EXEC_SPEEDUP | tr -s "\t" " " | cut -d " " -f2 | sed "s/m/#/g; s/s//g")
	
	MIN_TEMPO_BASE=$(echo $TEMPO_BASE | cut -d "#" -f1)
	SEG_TEMPO_BASE=$(echo $TEMPO_BASE | cut -d "#" -f2)
	TEMPO_TOTAL_BASE=$(echo "($MIN_TEMPO_BASE*60)+$SEG_TEMPO_BASE" | bc -l)

	MIN_TEMPO_EXEC=$(echo $TEMPO_EXEC | cut -d "#" -f1)
	SEG_TEMPO_EXEC=$(echo $TEMPO_EXEC | cut -d "#" -f2)
	TEMPO_TOTAL_EXEC=$(echo "($MIN_TEMPO_EXEC*60)+$SEG_TEMPO_EXEC" | bc -l)
	
	SPEEDUP=$(echo "$TEMPO_TOTAL_BASE / $TEMPO_TOTAL_EXEC" | bc -l)
	
	echo "$P $SPEEDUP"
done

