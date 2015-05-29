FLAGS=-Wall -pg -c -O4
FILE1=arvore
FILE2=pilha
FILE3=main
 

%: %.c
	gcc $(FLAGS) $< -o $@.o
all: $(FILE1).o $(FILE2).o $(FILE3).o
	gcc $(FLAGS) $(FILE1).c -o $(FILE1).o
	gcc $(FLAGS) $(FILE2).c -o $(FILE2).o
	gcc $(FLAGS) $(FILE3).c -o $(FILE3).o
	gcc -pg -o executavel $(FILE1).o $(FILE2).o $(FILE3).o
