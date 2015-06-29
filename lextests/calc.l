%{
#include "y.tab.h"
%}
integer    [0-9]+
nl         \n

%%

[ \t]+     ;
{integer} {sscanf(yytext,"%d",&yylval.integer); return INTEGER;}
{nl}      {extern int lineno;  lineno++; return '\n';}

.          {return yytext[0];}

%%
int yywrap() {
	return 1 ;
}