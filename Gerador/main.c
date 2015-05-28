
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int numY = 200;
    printf("Numero de repeticoes de Y: "); scanf("%d", &numY);
    int i=0;
    char valordeY[1000] = "s(cBI(SII))I(B(cBI(SII))I)";

    FILE *entradagerada;
    entradagerada = fopen ("in.txt", "w");

    for(i = 0 ; i < numY-2 ; i++)
    {
        fputs(valordeY,entradagerada);
        fputs("((",entradagerada);
    }
        fputs(valordeY,entradagerada);
        fputs("((",entradagerada);
        fputs(valordeY,entradagerada);
        fputs("(KK))K)",entradagerada);

    for(i = 0 ; i < numY-2 ; i++)
    {
        fputs(")K)",entradagerada);

    }

    return 0;
}
