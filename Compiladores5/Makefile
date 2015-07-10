FLAGS=-Wall -O4
SRC=$(wildcard src/*.c)
OBJ=$(wildcard obj/*.o)
CC=gcc
LIBS=-lm
define \n


endef

%: %.c
	%(CC) $(FLAGS) $< -o $@.o

all: obj_code bin_code

clean: obj/$(FILE1).o obj/$(FILE2).o obj/$(FILE3).o
	$(foreach var, $(OBJ), rm var)
	rm -rf bin/executavel

bin_code: $(OBJ)
	$(CC) $(FLAGS) -o ../bin_backend $(OBJ) $(LIBS)

obj_code: $(SRC)
	$(foreach var,$(SRC), $(CC) $(FLAGS) -c $(var) -o $(patsubst src/%.c,obj/%.o, $(var)) $(\n))
