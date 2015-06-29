flex front_end.l
bison -y -d front_end.y
gcc -c lex.yy.c y.tab.c
gcc y.tab.o lex.yy.o -o front_end
rm y.tab.* lex.yy.*

gcc MG-V7.c
