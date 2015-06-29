	%{
	#include <stdlib.h>
	#include <string.h>
	#include "front_end.h"
	#include "y.tab.h"

	void yyerror(char*) ;
%}

%%
(if)					{return IF ; }	
(then)					{return THEN ;}
(else)					{return ELSE; }
(not)					{return NOT; }
(and)					{return AND; }
(or)					{return OR; }
(head)					{return HEAD; }
(tail)					{return TAIL; }
(vazia)					{return VAZIA;}

(True)					{yylval.bool = 1; return BOOLEAN; }
(False)					{yylval.bool = 0; return BOOLEAN; }

(==)					{return EQ; }
(\*)					{return *yytext ;}
(\/)					{return *yytext ;}
(\[)					{return *yytext ;}
(\])					{return *yytext ;}
(\^)					{return *yytext ;}

[a-z_][a-zA-Z0-9_]*		{yylval.id = strdup(yytext) ; return ID; }

[0-9]+					{yylval.numero = atoi(yytext) ; return NUM; }

\"[a-zA-Z0-9]*\"		{yylval.string = strdup(yytext); return STRING; }

[+-:><=,()]				{return *yytext ; }

[ \t\n.]				;

.						{yyerror("Lexic error");}

%%
int yywrap() {
	return 1 ;
}
