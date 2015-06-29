%{
int count = 0;
%}

%%

[^ \t\n]+			count++;

%%
main() {
	yylex();
	printf("\n%d palavras contadas. \n", count);
}