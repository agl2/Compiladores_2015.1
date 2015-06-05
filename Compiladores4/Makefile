FLAGS=-Wall -pg -c -O4
FILE1=arvore
FILE2=pilha
SRC=$(wildcard src/*.c)
OBJ=$(wildcard obj/*.o)

define \n


endef

%: %.c
	gcc $(FLAGS) $< -o $@.o

all: obj_code bin_code

clean: obj/$(FILE1).o obj/$(FILE2).o obj/$(FILE3).o
	rm obj/$(FILE1).o 
	rm obj/$(FILE2).o 
	rm obj/$(FILE3).o
	rm bin/executavel

bin_code: $(OBJ)
	gcc -pg -o bin/executavel $(OBJ)

obj_code: $(SRC)
	$(foreach var,$(SRC), gcc $(FLAGS) $(var) -o $(patsubst src/%.c,obj/%.o, $(var)) $(\n))
