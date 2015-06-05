
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int numY;
    printf("Numero de repeticoes de Y: ");
    scanf("%d", &numY);
    int i=0;
    char valordeY[1000] = "S(S(S(KS)(S(KK)(SKK)))(K(S(SKK)(SKK))))(S(S(KS)(S(KK)(SKK)))(K(S(SKK)(SKK))))"; 
    //s(cBI(SII))I(B(cBI(SII))I)
    //"S(S(S(KS)(S(KK)(SKK)))(K(S(SKK)(SKK))))(S(S(KS)(S(KK)(SKK)))(K(S(SKK)(SKK))))"
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
