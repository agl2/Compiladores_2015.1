%{
	int nlin=0;
%}
Qqchar             .*
NovaLinha          [\n]
%%
^{Qqchar}{NovaLinha} {nlin=nlin+1;printf("%4d\t%s", nlin, yytext);}
