%{
	#include <stdlib.h>
	#include <string.h>
	#include "y.tab.h"

	void yyerror(char*) ;
%}

%%
(if)					return IF ; 
(else)					return ELSE; 
(&)						return *yytext; 
(|)						return *yytext; 
(H)						return *yytext; 
(T)						return *yytext; 

(true)					{yylval.bool = 1; return BOOLEAN; }
(false)					{yylval.bool = 0; return BOOLEAN; }

(==)					return EQ; 
(\*)					return *yytext ;
(\/)					return *yytext ;
(\[)					return *yytext ;
(\])					return *yytext ;
(\^)					return *yytext ;
(\{)					return *yytext ;
(\})					return *yytext ;

[a-zA-Z][a-zA-Z0-9]*		{yylval.id = strdup(yytext) ; return ID; }

[1-9][0-9]+					{yylval.number = atoi(yytext) ; return NUMBER; }

\"[a-zA-Z0-9]*\"		{yylval.str = strdup(yytext); return STRING; }

[+-:><=,()]				return *yytext ;

[ \t]					;
	
[\n]  				 	return NEW_LINE;



.						yyerror("Lexic error");

%%
int yywrap() {
	return 1 ;
}
