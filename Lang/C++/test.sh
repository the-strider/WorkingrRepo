#! /bin/bash
# This is something
for ((i = 1; ; i++)); do
	echo $i
	./gen $i > in
	./D < in > out1
	./B < out1 > out2
	./A < out1 > out3
	diff -w out2 out3 || break
done