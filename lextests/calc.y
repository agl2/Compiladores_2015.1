%{
#include <stdio.h>
%}

%union {
double real;
int integer;
}

%token <integer> INTEGER
%type <integer> expr;

%left '+' '-'
%left '*' '/'
%nonassoc UMINUS

%%
lines:  /* nothing */
	| lines line
	;

line: '\n'
	| expr '\n' {printf("%d\n", $1);}
	| error '\n'  {yyerror();}
	;

expr: INTEGER
	| expr '+' expr  {$$ = $1 + $3;}
	| expr '-' expr  {$$ = $1 - $3;}
	| expr '*' expr  {$$ = $1 * $3;}
	| expr '/' expr  {if($3) $$ = $1 / $3;
					  else {
					  			yyerror("divide by zero");
					  		}
					  }
	| '(' expr ')' {$$ = $2;}
	| '-' expr %prec UMINUS {$$ = - $2;};

%%
int lineno = 0;
main() {
 yyparse();
}

yyerror(s) 
char *s;
{
	printf("calc: %s", s);
	printf(" line %d\n", lineno);
}