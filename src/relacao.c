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
    int EhReflexiva = 1;
    int numeroDeFaltamParaSerReflexiva = 0;
    for (int i = 0; i < numeroDeElementos; i++)
    {
        if (!(matrizDeRelacoes[i][i]))
        {
            EhReflexiva = 0;
            faltaParaSerReflexiva[numeroDeFaltamParaSerReflexiva].x = elementos[i];
            faltaParaSerReflexiva[numeroDeFaltamParaSerReflexiva].y = elementos[i];
            numeroDeFaltamParaSerReflexiva++;
        }
    }
    printf("1. Reflexiva: ");
    if (EhReflexiva)
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

    //VERIFICAR SE É IRREFLEXIVA
    Elemento faltaParaSerIrreflexiva[numeroDeElementos];
    int EhIrreflexiva = 1;
    int numeroDeFaltamParaSerIrreflexiva = 0;
    for (int i = 0; i < numeroDeElementos; i++)
    {
        if ((matrizDeRelacoes[i][i]))
        {
            EhIrreflexiva = 0;
            faltaParaSerIrreflexiva[numeroDeFaltamParaSerIrreflexiva].x = elementos[i];
            faltaParaSerIrreflexiva[numeroDeFaltamParaSerIrreflexiva].y = elementos[i];
            numeroDeFaltamParaSerIrreflexiva++;
        }
    }
    printf("2. Irreflexiva: ");
    if (EhIrreflexiva)
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

    //VERIFICA SE É SIMÉTRICA
    int EhSimetrica = 1;
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
                    EhSimetrica = 0;
                    faltaParaSerSimetrica[numeroDeFaltamParaSerSimetrica].x = elementos[j];
                    faltaParaSerSimetrica[numeroDeFaltamParaSerSimetrica].y = elementos[i];
                    numeroDeFaltamParaSerSimetrica++;
                }
            }
        }
    }

    printf("3. Simétrica: ");
    if (EhSimetrica)
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

    //VERIFICA SE É ANTI-SIMÉTRICA
    int EhAntisimetrica = 1;
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
                        EhAntisimetrica = 0;
                        faltaParaSerAntisimetrica[numeroDeFaltamParaSerAntisimetrica].x = elementos[j];
                        faltaParaSerAntisimetrica[numeroDeFaltamParaSerAntisimetrica].y = elementos[i];
                        numeroDeFaltamParaSerAntisimetrica++;
                    }
                    elementoJaContado = 0;
                }
            }
        }
    }

    printf("4. Anti-simétrica: ");
    if (EhAntisimetrica)
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

    //VERIFICA SE É ASSIMÉTRICA
    int EhAssimetrica = 1;
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
                    EhAssimetrica = 0;
                    faltaParaSerAssimetrica[numeroDeFaltamParaSerAssimetrica].x = elementos[j];
                    faltaParaSerAssimetrica[numeroDeFaltamParaSerAssimetrica].y = elementos[i];
                    numeroDeFaltamParaSerAssimetrica++;
                }
            }
        }
    }

    printf("5. Assimétrica: ");
    if (EhAssimetrica)
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

    fclose(ponteiroArquivo);
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
}
