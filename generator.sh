#!/bin/bash

i=0
mkdir -p maps/big_super
while [[ 100 -gt $i ]]; do
	i=$(($i + 1))
	./maps/generator --big-superposition > map/big_super/gen_$i
done
