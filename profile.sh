#!/bin/bash

infile=$1
pattern=$2

[[ -z $infile ]] && { echo "Usage: $0 <infile>"; exit 1; }
[[ -z $pattern ]] && pattern="loop"

lines=`cat $infile | wc -l`
middle=$(( lines / 2 ))
median=`cat $infile | grep "$pattern" | grep -o ": [0-9]\+" | grep -o "[0-9]\+" | sort | tail -$middle | head -1`

echo "$median us: median time($pattern)"

