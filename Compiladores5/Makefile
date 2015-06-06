FLAGS=-g -Wall -pg -c -O4
SRC=$(wildcard *.c)
OBJ=$(wildcard obj/*.o)
CC=gcc

define \n


endef

%: %.c
	%(CC) $(FLAGS) $< -o obj/$@.o

all: obj_code bin_code

clean: $(OBJ)
	$(foreach var, $(OBJ), rm $(var) $(\n))
	rm bin/executavel

bin_code: $(OBJ)
	g++ -pg -o bin/executavel $(OBJ)

obj_code: $(SRC)
	$(foreach var,$(SRC), $(CC) $(FLAGS) $(var) -o $(patsubst %.c, obj/%.o, $(var)) $(\n))
