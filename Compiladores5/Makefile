FLAGS=-Wall -pg -c -O4
SRC=$(wildcard src/*.c)
OBJ=$(wildcard obj/*.o)
CC=g++

define \n


endef

%: %.c
	gcc $(FLAGS) $< -o $@.o

all: obj_code bin_code

clean: obj/$(FILE1).o obj/$(FILE2).o obj/$(FILE3).o
	$(foreach var, $(OBJ), rm var)
	rm bin/executavel

bin_code: $(OBJ)
	$(CC) -pg -o bin/executavel $(OBJ)

obj_code: $(SRC)
	$(foreach var,$(SRC), $(CC) $(FLAGS) $(var) -o $(patsubst src/%.c,obj/%.o, $(var)) $(\n))
