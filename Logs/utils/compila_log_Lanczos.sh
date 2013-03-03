#!/bin/bash

if [[ $# < 1 ]]; then
	echo -e "Parametros errados! Utilze:"
	echo -e "$0 [ARQ_LOG]"
	echo -e ""
	exit 1
fi

ARQ_LOG=${1}
NUM_LINHAS=$(wc -l $ARQ_LOG | cut -d  " " -f1)

for OP_EXEC in $(grep "\[EXEC\]\_" $ARQ_LOG | sed "s/^##//g" | cut -d "_" -f2); do
	TEMPO=$(grep -A${NUM_LINHAS} "\[EXEC\]\_${OP_EXEC}" $ARQ_LOG | grep -m1 "^real" | tr -s "\t" " " | cut -d " " -f2)
	echo "$OP_EXEC $TEMPO"
done
