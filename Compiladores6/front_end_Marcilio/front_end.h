struct op ;

// Struct para a construção de uma lista
typedef struct lista{
	struct op* elem ;
	struct lista* next ;
} Lista ;

// Struct referente a operadores (construção da árvore sintática)
typedef struct op {
	int tipo ;
	int qtd_args ;
	struct op** vetor_op ;
	union{ //Union para operadores com apenas o operandos (NUM, STRING etc...)
		int num ;
		unsigned short boolean ;
		char* string ;
	} ;
} Op ;

// Struct para fazer o bracket abstraction
typedef struct bracket {
	char* terminal ;
	int qtd_elem ;
	struct bracket** elems ;
} Bracket;

//Struct para dados de uma função
typedef struct {
	char* nome ;
	int* tipos ;
	int qtd_param ;
	int saida ;
	Bracket* codigo ;
} Function ;