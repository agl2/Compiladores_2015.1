%{
	#include <stdlib.h>
	#include <string.h>
	#include "front_end.h"
	#include "y.tab.h"

	void yyerror(char*) ;
%}

%%
(if)					{return IF ; }	
(else)					{return ELSE; }
(~)						{return NOT; }
(&)						{return AND; }
(|)						{return OR; }
(H)						{return HEAD; }
(T)						{return TAIL; }
([])					{return VAZIA;}

(true)					{yylval.bool = 1; return BOOLEAN; }
(false)					{yylval.bool = 0; return BOOLEAN; }

(==)					{return EQ; }
(\*)					{return *yytext ;}
(\/)					{return *yytext ;}
(\[)					{return *yytext ;}
(\])					{return *yytext ;}
(\^)					{return *yytext ;}
(\{)					{return *yytext ;}
(\})					{return *yytext ;}

[a-zA-Z][a-zA-Z0-9]*		{yylval.id = strdup(yytext) ; return ID; }

[0-9]+					{yylval.numero = atoi(yytext) ; return NUM; }

\"[a-zA-Z0-9]*\"		{yylval.string = strdup(yytext); return STRING; }

[+-:><=,()]				{return *yytext ; }

[ \t\n.]				;

.						{yyerror("Lexic error");}

%%
int yywrap() {
	return 1 ;
}
