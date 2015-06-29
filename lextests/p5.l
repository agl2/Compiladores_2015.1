%%
[.]             ;
then            ;
var             ;
[{]             printf("/*");
[}]             printf("*/");
mod             printf("%%");
or              printf("||");
and             printf("&&");
begin           printf("{");
end             printf("}");
program.*[(].*$ printf("main()\n{");
[^:><][=]       printf("==");
[:][=]          printf("=");
[<][>]          printf("!=");
^.*integer;		ShuffleInt();
.               ECHO;
%%
ShuffleInt() { 
	int i;
	printf("int ");
	for(i=0; yytext[i]!=':'; i++)  printf("%c", yytext[i]);
	printf(";");

}