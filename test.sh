#!/bin/bash
if [ $# -ne 2 ] && [ $# -ne 4 ]; then
echo "usage: $0 mode(1-random, 2-compare files) algorithm# [file1 file2]"
exit
fi

if [ -e output.txt ]; then
rm -f output.txt
fi

if [ ! -e algorisme$2 ]; then
g++ -std=c++11 -o algorisme$2 algorisme$2.cpp
fi

if [ $2 -lt 3 ]; then
echo "Introducir k: "
read k
fi

if [ $2 -eq 2 ]; then
echo "Número de shingles: "
read shin
echo "Número de hashes: "
read hashes
fi

if [ $1 -eq 1 ]; then
if [ ! -e wordPermutator ]; then
g++ -o wordPermutator wordPermutator.cpp
fi
echo "50 20" > inputFile
./wordPermutator < inputFile > /dev/null
rm -f inputFile
bar="[==============================================================================]"
total=210
for i in `seq 0 19`;
do
ini=$(($i+1))
for j in `seq $ini 19`;
do
if [ ! $i -eq $j ]; then
echo "permutation$i.txt permutation$j.txt $k $shin $hashes" > inputFile
echo "Comparació permutació $i amb permutació $j: " >> output.txt
./algorisme$2 < inputFile  >> output.txt
rm -f inputFile
fi
pd=$(( ($i * $j + $j) * 80 / $total ))
ij=$(( $i * $j + $j))
printf "\r%3d.%1d%% %.${pd}s" $(( $ij * 100 / $total )) $(( ($ij * 1000 / $total) % 10 )) $bar
done
done
rm -f permutation*

elif [ $1 -eq 2 ]; then
echo "$3 $4 $k $shin $hashes" > inputFile
echo "Comparació de $3 amb $4:" > output.txt
./algorisme$2 < inputFile >> output.txt
rm -f inputFile
fi

echo "\nSe han guardado los resultados en output.txt"



