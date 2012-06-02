#!/bin/bash
TIMEFORMAT="%U"
sum=0
for i in {1..1000}
do
	t=$( { time $1; } 2>&1 )
	sum=$( bc <<< "scale=10; $sum + $t" )
done
avrg=$( bc <<< "scale=3; $sum / 1000" )
echo "$avrg"
