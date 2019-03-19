#!/bin/bash

i=0
total=0
while [[ $i -lt 100 ]]; do
	i=$(($i + 1))
	./maps/generator --big-superposition > maps/big_super/gen_$i
	error=$(make run map=big_super/gen_$i time=y 2>&1)
	res=$(echo "$error" | grep -E 'best path|nb de bfs|real|user|sys' 2>&1)
	printf "$res\n"
	error=$(echo "$error" | grep -v required | grep -E '\-[0-9]|ERROR' | grep -A 1 'reste' 2>&1)
	printf "$error\n"
	res=$(echo "$res" | grep best | cut -d ' ' -f 3 2>&1)
	req=$(cat maps/big_super/gen_$i | grep required | sort -u 2>&1 | cut -d ' ' -f 8 2>&1)
	printf "required: $req - result: $res = "
	diff=$(echo "$res - $req" | bc)
	if [[ $diff -le 0 ]]; then
		printf "\033[38;2;12;231;58m"
	else
		printf "\033[38;2;255;60;51m"
	fi
	echo "$diff"
	if [[ $diff -gt 10 ]]; then
		name=$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 16 | head -n 1)
		mkdir -p maps/big_super/hard_maps/
		cp -f maps/big_super/gen_$i maps/big_super/hard_maps/$name
		echo "new hard map: $name"
		echo "diff: $diff" >> maps/big_super/hard_maps/$name
	fi
	total=$(echo "$res - $req + $total" | bc)
	j=1.0
	printf "\033[0m"
	while [[ $j>-1 ]]; do
		printf "\rsleep $j"
		sleep 0.01
		j=$(echo "$j - 0.01" | bc)
	done
	printf "\033[2K\n"
done
echo "$total / 100" | bc
