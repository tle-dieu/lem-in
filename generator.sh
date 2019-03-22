#!/bin/bash

i=0
total=0
total_time=0
loop=10000
RED="\033[38;2;255;60;51m"
RESET="\033[0m"
GREEN="\033[38;2;12;231;58m"
BLUE="\033[38;2;0;188;218m"
param="big-superposition"
while [[ $i -lt $loop ]]; do
	i=$(($i + 1))
	if [[ $#>1 ]]; then
		param=$1
	fi
	./maps/generator --$param > maps/gen_test
	output=$(make run map=maps/gen_test time=y 2>&1)
	actual_time=$(echo "$output" | grep real | awk '{for(i=1;i<=NF;i++)if($i~/^-?[0-9]+\.[0-9]+$/){print $i}}')
	diff=$(echo "$output" | grep -E 'L[0-9]' | wc -l | tr -d ' ')
	steps=$(echo "$output" | grep -E 'best path|nb de bfs|real|user|sys' 2>&1)
	error=$(echo "$output" | grep -v required | grep -E '\-[0-9]|ERROR' | grep -A 1 'reste' 2>&1)
	required=$(cat maps/gen_test | grep required | sort -u 2>&1 | cut -d ' ' -f 8 2>&1)
	echo "$steps"
	echo "${BLUE}nb instructions: $diff"
	printf "required: $required - result: $diff = "
	diff=$(echo "$diff - $required" | bc)
	if [[ $diff -le 0 ]]; then
		echo "${GREEN}$diff${RESET}"
	else
		echo "${RED}$diff${RESET}"
	fi
	if [[ $diff -gt 10 ]]; then
		name=$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 10 | head -n 1)
		mkdir -p maps/hard_maps/
		mv -f maps/gen_test maps/hard_maps/steps_$name
		echo "${RED}new hard map: ${RESET}steps_$name"
		echo "diff: $diff" >> maps/hard_maps/steps_$name
	fi
	if [[ $actual_time>1.5 ]]; then
		name=$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 10 | head -n 1)
		mkdir -p maps/hard_maps/
		mv -f maps/gen_test maps/hard_maps/time_$name
		echo "${RED}new hard map: ${RESET}time_$name"
		echo "time: $actual_time" >> maps/hard_maps/time_$name
	fi
	total=$(echo "$diff + $total" | bc)
	j=0.2
	printf "${GREEN}average: $RESET"
	echo "$total / $i" | bc
	printf "\033[0m"
	while [[ $j>-1 ]]; do
		printf "\rsleep $j"
		sleep 0.01
		j=$(echo "$j - 0.01" | bc)
	done
	printf "\033[2K\n"
done
