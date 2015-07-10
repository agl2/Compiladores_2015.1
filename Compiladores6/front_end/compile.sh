bison -d -y -v front_end.y
flex front_end.l
gcc -g -c lex.yy.c y.tab.c fila.c front_end.c
gcc -g y.tab.o lex.yy.o fila.o front_end.o -o ../bin_frontend
rm y.tab.c lex.yy.c *.o
