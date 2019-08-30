#!/bin/bash

if [[ -f cfg_value_set.txt ]]; then
	rm cfg_value_set.txt
fi


for (( i = 0; i < $1; i++ ));
do
	printf "%08x\n" $i >> cfg_value_set.txt
done



