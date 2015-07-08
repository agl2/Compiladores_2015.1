flex front_end.l
bison -d -y -v front_end.y
gcc -g -c lex.yy.c y.tab.c fila.c front_end.c
gcc -g y.tab.o lex.yy.o fila.o front_end.o -o ../bin_front_end
rm y.tab.c lex.yy.c *.o
