#! /bin/bash

#Ejercicio 1

cat cpuinfo | grep "model"

#Ejercicio 2

cat cpuinfo | grep "model" | wc -l

#Ejercicio 3

wget -O simon_in_wonderland.txt https://www.gutenberg.org/files/11/11-0.txt && sed -i 's/Alice/Simon/g' "simon_in_wonderland.txt"

#Ejercicio 4

sort -n -k5,5 -o weather_cordoba_sort.in weather_cordoba.in && cut -d' ' -f1-3 weather_cordoba_sort.in | head -n 1 && cut -d' ' -f1-3 weather_cordoba_sort.in | tail -n 1

#Ejercicio 5

sort -n -k3,3 -o atpplayers_sort.in atpplayers.in

#Ejercicio 6

awk '{$0 = $0 OFS ($7 - $8)} 1' superliga.in > superliga_sort.in && sort -k2,2 -k9,9 superliga_sort.in

#Ejercicio 7

ip link show | grep ether

#Ejercicio 8

#Creo los archivos

for i in {1..9}; do echo > "fma_S01E0${i}_es.txt"; done | echo > "fma_S01E10_es.txt"
#Los renombro

for f in *_es*; do mv $f ${f%_es.srt}.srt; done
