/* VICTOR HUGO FARIA DIAS MAGALHÃES - 2019055010
// COMPLEXIDADE O(n^4)
// FEITO E TESTADO NO UBUNTU 18.0.4 LTS gcc 7.5.0
// COMANDO PARA EXECUTAR NO UBUNTU: g++ relacao.c -o relacao && ./relacao
*/

#include <stdio.h>
#include <stdlib.h>
#define TAMANHO_MAXIMO_ARQUIVO 1000

typedef struct
{
    int x;
    int y;
} Elemento;

int associaElementoACasa(int elementos[], int elemento, int numeroDeElementos);

int main()
{
    FILE *ponteiroArquivo;
    if ((ponteiroArquivo = fopen("input.txt", "r")) == NULL)
    {
        printf("Arquivo não encontrado, cheque se o arquivo input.txt está na mesma pasta que o executável!");
        exit(1);
    }
    int quantidadeDeRelacoes = 0;
    Elemento relacoes[TAMANHO_MAXIMO_ARQUIVO];
    int numeroDeElementos;
    fscanf(ponteiroArquivo, "%d", &numeroDeElementos);
    int elementos[numeroDeElementos];

    for (int i = 0; i < numeroDeElementos; i++)
    {
        fscanf(ponteiroArquivo, "%d", &elementos[i]);
    }

    while (!feof(ponteiroArquivo) && quantidadeDeRelacoes < TAMANHO_MAXIMO_ARQUIVO)
    {
        fscanf(ponteiroArquivo, "%d %d", &relacoes[quantidadeDeRelacoes].x, &relacoes[quantidadeDeRelacoes].y);
        quantidadeDeRelacoes++;
    }

    int matrizDeRelacoes[numeroDeElementos][numeroDeElementos];

    for (int i = 0; i < numeroDeElementos; i++)
    {
        for (int j = 0; j < numeroDeElementos; j++)
        {
            matrizDeRelacoes[i][j] = 0;
        }
    }

    fclose(ponteiroArquivo);

    for (int i = 0; i < quantidadeDeRelacoes; i++)
    {
        int origem = associaElementoACasa(elementos, relacoes[i].x, numeroDeElementos);
        int destino = associaElementoACasa(elementos, relacoes[i].y, numeroDeElementos);
        matrizDeRelacoes[origem][destino] = 1;
    }

    //VERIFICAR PROPRIEDADES
    printf("Propriedades:\n");

    //VERIFICAR SE É REFLEXIVA
    Elemento faltaParaSerReflexiva[numeroDeElementos];
    int Reflexiva = 1;
    int numeroDeFaltamParaSerReflexiva = 0;
    for (int i = 0; i < numeroDeElementos; i++)
    {
        if (!(matrizDeRelacoes[i][i]))
        {
            Reflexiva = 0;
            faltaParaSerReflexiva[numeroDeFaltamParaSerReflexiva].x = elementos[i];
            faltaParaSerReflexiva[numeroDeFaltamParaSerReflexiva].y = elementos[i];
            numeroDeFaltamParaSerReflexiva++;
        }
    }

    //VERIFICAR SE É IRREFLEXIVA
    Elemento faltaParaSerIrreflexiva[numeroDeElementos];
    int Irreflexiva = 1;
    int numeroDeFaltamParaSerIrreflexiva = 0;
    for (int i = 0; i < numeroDeElementos; i++)
    {
        if ((matrizDeRelacoes[i][i]))
        {
            Irreflexiva = 0;
            faltaParaSerIrreflexiva[numeroDeFaltamParaSerIrreflexiva].x = elementos[i];
            faltaParaSerIrreflexiva[numeroDeFaltamParaSerIrreflexiva].y = elementos[i];
            numeroDeFaltamParaSerIrreflexiva++;
        }
    }

    //VERIFICA SE É SIMÉTRICA
    int Simetrica = 1;
    Elemento faltaParaSerSimetrica[quantidadeDeRelacoes];
    int numeroDeFaltamParaSerSimetrica = 0;
    for (int i = 0; i < numeroDeElementos; i++)
    {
        for (int j = 0; j < numeroDeElementos; j++)
        {
            if (matrizDeRelacoes[i][j])
            {
                if (!matrizDeRelacoes[j][i])
                {
                    Simetrica = 0;
                    faltaParaSerSimetrica[numeroDeFaltamParaSerSimetrica].x = elementos[j];
                    faltaParaSerSimetrica[numeroDeFaltamParaSerSimetrica].y = elementos[i];
                    numeroDeFaltamParaSerSimetrica++;
                }
            }
        }
    }

    //VERIFICA SE É ANTI-SIMÉTRICA
    int Antisimetrica = 1;
    Elemento faltaParaSerAntisimetrica[quantidadeDeRelacoes];
    int numeroDeFaltamParaSerAntisimetrica = 0;
    int elementoJaContado = 0;
    for (int i = 0; i < numeroDeElementos; i++)
    {
        for (int j = 0; j < numeroDeElementos; j++)
        {
            if (matrizDeRelacoes[i][j] && i != j)
            {
                if (matrizDeRelacoes[j][i])
                {
                    for (int k = 0; k < numeroDeFaltamParaSerAntisimetrica; k++)
                    {
                        if (faltaParaSerAntisimetrica[k].y == elementos[j] && faltaParaSerAntisimetrica[k].x == elementos[i])
                        {
                            elementoJaContado = 1;
                        }
                    }
                    if (!elementoJaContado)
                    {
                        Antisimetrica = 0;
                        faltaParaSerAntisimetrica[numeroDeFaltamParaSerAntisimetrica].x = elementos[j];
                        faltaParaSerAntisimetrica[numeroDeFaltamParaSerAntisimetrica].y = elementos[i];
                        numeroDeFaltamParaSerAntisimetrica++;
                    }
                    elementoJaContado = 0;
                }
            }
        }
    }

    //VERIFICA SE É ASSIMÉTRICA
    int Assimetrica = 1;
    Elemento faltaParaSerAssimetrica[quantidadeDeRelacoes];
    int numeroDeFaltamParaSerAssimetrica = 0;
    for (int i = 0; i < numeroDeElementos; i++)
    {
        for (int j = 0; j < numeroDeElementos; j++)
        {
            if (matrizDeRelacoes[i][j])
            {
                if (matrizDeRelacoes[j][i])
                {
                    Assimetrica = 0;
                    faltaParaSerAssimetrica[numeroDeFaltamParaSerAssimetrica].x = elementos[j];
                    faltaParaSerAssimetrica[numeroDeFaltamParaSerAssimetrica].y = elementos[i];
                    numeroDeFaltamParaSerAssimetrica++;
                }
            }
        }
    }

    //VERIFICA SE É TRANSITIVA
    int Transitiva = 1;
    int numeroDeFaltamParaSerTransitivo = 0;
    Elemento faltamParaSerTransitiva[quantidadeDeRelacoes];
    int elementoJaListado = 0;
    for (int i = 0; i < numeroDeElementos; i++)
    {
        for (int j = 0; j < numeroDeElementos; j++)
        {
            for (int k = 0; k < numeroDeElementos; k++)
            {
                if (matrizDeRelacoes[i][j] && matrizDeRelacoes[j][k] && !matrizDeRelacoes[i][k])
                {
                    for (int x = 0; x < numeroDeFaltamParaSerTransitivo; x++)
                    {
                        if (faltamParaSerTransitiva[x].x == elementos[i] && faltamParaSerTransitiva[x].y == elementos[k])
                        {
                            elementoJaListado = 1;
                        }
                    }
                    if (!elementoJaListado)
                    {
                        Transitiva = 0;
                        faltamParaSerTransitiva[numeroDeFaltamParaSerTransitivo].x = elementos[i];
                        faltamParaSerTransitiva[numeroDeFaltamParaSerTransitivo].y = elementos[k];
                        numeroDeFaltamParaSerTransitivo++;
                    }
                    elementoJaListado = 0;
                }
            }
        }
    }
    //VERIFICAR SE É EQUIVALENCIA
    char equivalencia = (Reflexiva && Simetrica && Transitiva) ? 'V' : 'F';

    //VERIFICAR SE É ORDEM PARCIAL
    char parcial = (Reflexiva && Antisimetrica && Transitiva) ? 'V' : 'F';

    //PRINT SE É REFLEXIVA
    printf("1. Reflexiva: ");
    if (Reflexiva)
    {
        printf("V\n");
    }
    else
    {
        printf("F\n   ");
        for (int i = 0; i < numeroDeFaltamParaSerReflexiva; i++)
        {
            printf("(%d, %d); ", faltaParaSerReflexiva[i].x, faltaParaSerReflexiva[i].y);
        }
        printf("\n");
    }

    // PRINT SE É IRREFLEXIVA
    printf("2. Irreflexiva: ");
    if (Irreflexiva)
    {
        printf("V\n");
    }
    else
    {
        printf("F\n   ");
        for (int i = 0; i < numeroDeFaltamParaSerIrreflexiva; i++)
        {
            printf("(%d, %d); ", faltaParaSerIrreflexiva[i].x, faltaParaSerIrreflexiva[i].y);
        }
        printf("\n");
    }

    //PRINT SE É SIMÉTRICA
    printf("3. Simétrica: ");
    if (Simetrica)
    {
        printf("V\n");
    }
    else
    {
        printf("F\n   ");
        for (int i = 0; i < numeroDeFaltamParaSerSimetrica; i++)
        {
            printf("(%d, %d); ", faltaParaSerSimetrica[i].x, faltaParaSerSimetrica[i].y);
        }
        printf("\n");
    }

    //PRINT SE É ANTI-SIMÉTRICA
    printf("4. Anti-simétrica: ");
    if (Antisimetrica)
    {
        printf("V\n");
    }
    else
    {
        printf("F\n   ");
        for (int i = 0; i < numeroDeFaltamParaSerAntisimetrica; i++)
        {
            printf("(%d, %d) e (%d, %d); ", faltaParaSerAntisimetrica[i].x, faltaParaSerAntisimetrica[i].y, faltaParaSerAntisimetrica[i].y, faltaParaSerAntisimetrica[i].x);
        }
        printf("\n");
    }

    //PRINT SE É ASSIMÉTRICA
    printf("5. Assimétrica: ");
    if (Assimetrica)
    {
        printf("V\n");
    }
    else
    {
        printf("F\n   ");
        for (int i = 0; i < numeroDeFaltamParaSerAssimetrica; i++)
        {
            printf("(%d, %d); ", faltaParaSerAssimetrica[i].x, faltaParaSerAssimetrica[i].y);
        }
        printf("\n");
    }

    //PRINT SE É TRANSITIVA
    printf("6. Transitiva: ");
    if (Transitiva)
    {
        printf("V\n");
    }
    else
    {
        printf("F\n   ");
        for (int i = 0; i < numeroDeFaltamParaSerTransitivo; i++)
        {
            printf("(%d, %d); ", faltamParaSerTransitiva[i].x, faltamParaSerTransitiva[i].y);
        }
        printf("\n");
    }

    //PRINT SE É EQUIVALENCIA
    printf("\nRelação de equivalência: %c\n", equivalencia);

    //PRINT SE É ORDEM PARCIAL
    printf("Relação de ordem parcial: %c\n\n", parcial);

    //PRINT O FECHO TRANSITIVO
    printf("Fecho transitivo da relação: {");
    for (int i = 0; i < quantidadeDeRelacoes; i++)
    {
        printf("(%d, %d), ", relacoes[i].x, relacoes[i].y);
    }
    for (int i = 0; i < numeroDeFaltamParaSerTransitivo; i++)
    {
        if (i != numeroDeFaltamParaSerTransitivo - 1)
        {
            printf("(%d, %d), ", faltamParaSerTransitiva[i].x, faltamParaSerTransitiva[i].y);
        }
        else
        {
            printf("(%d, %d)", faltamParaSerTransitiva[i].x, faltamParaSerTransitiva[i].y);
        }
    }
    printf("} \n");

    return 0;
}

int associaElementoACasa(int elementos[], int elemento, int numeroDeElementos)
{
    for (int casa = 0; casa < numeroDeElementos; casa++)
    {
        if (elemento == elementos[casa])
        {
            return casa;
        }
    }
    return -1;
}