#!/bin/bash
flex -t c2test.l>c2test.c
g++ -c -o c2test.o c2test.c
g++ -o c2test c2test.o -ll
./c2test<in.txt>out.txt
