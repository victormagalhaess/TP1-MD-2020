#include <stdio.h>
#include <stdlib.h>
#define TAMANHO_MAXIMO_ARQUIVO 5000

typedef struct
{
    int x;
    int y;
} Elemento;

int associaElementoACasa(int elementos[], int elemento, int numeroDeElementos);

int main()
{
    FILE *ponteiroArquivo;
    ponteiroArquivo = fopen("input.txt", "r");
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

    //flags para verificação das propriedades
    int Reflexiva = 1;
    int Irreflexiva = 1;
    int Simetrica = 1;
    int Antisimetrica = 1;
    int Assimetrica = 1;
    int Transitiva = 1;

    //VERIFICA SE É REFLEXIVA

    Elemento faltaParaSerReflexiva[numeroDeElementos];
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

    //VERIFICA SE É IRREFLEXIVA

    Elemento faltaParaSerIrreflexiva[numeroDeElementos];
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

    Elemento faltaParaSerAntisimetrica[quantidadeDeRelacoes];
    int numeroDeFaltamParaSerAntisimetrica = 0;
    for (int i = 0; i < numeroDeElementos; i++)
    {
        for (int j = 0; j < numeroDeElementos; j++)
        {
            if (matrizDeRelacoes[i][j] && i != j)
            {
                if (matrizDeRelacoes[j][i])
                {

                    Antisimetrica = 0;
                    faltaParaSerAntisimetrica[numeroDeFaltamParaSerAntisimetrica].x = elementos[j];
                    faltaParaSerAntisimetrica[numeroDeFaltamParaSerAntisimetrica].y = elementos[i];
                    numeroDeFaltamParaSerAntisimetrica++;
                }
            }
        }
    }

    //VERIFICA SE É ASSIMÉTRICA

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

    int numeroDeFaltamParaSerTransitivo = 0;
    Elemento faltamParaSerTransitiva[quantidadeDeRelacoes];
    for (int i = 0; i < numeroDeElementos; i++)
    {
        for (int j = 0; j < numeroDeElementos; j++)
        {
            for (int k = 0; k < numeroDeElementos; k++)
            {
                if (matrizDeRelacoes[i][j] && matrizDeRelacoes[j][k] && !matrizDeRelacoes[i][k])
                {
                    Transitiva = 0;
                    faltamParaSerTransitiva[numeroDeFaltamParaSerTransitivo].x = elementos[i];
                    faltamParaSerTransitiva[numeroDeFaltamParaSerTransitivo].y = elementos[k];
                    numeroDeFaltamParaSerTransitivo++;
                }
            }
        }
    }

    int numeroDeFaltamParaSerTransitivaSemDuplicatas = 0;
    Elemento faltamParaSerTransitivaSemDuplicatas[numeroDeFaltamParaSerTransitivo];
    int podeInserir = 1;
    for (int i = 0; i < numeroDeFaltamParaSerTransitivo; i++)
    {
        for (int j = 0; j < numeroDeFaltamParaSerTransitivaSemDuplicatas; j++)
        {
            if (faltamParaSerTransitiva[i].x == faltamParaSerTransitivaSemDuplicatas[j].x && faltamParaSerTransitiva[i].y == faltamParaSerTransitivaSemDuplicatas[j].y)
            {
                podeInserir = 0;
            }
        }
        if (podeInserir)
        {
            faltamParaSerTransitivaSemDuplicatas[numeroDeFaltamParaSerTransitivaSemDuplicatas] = faltamParaSerTransitiva[i];
            numeroDeFaltamParaSerTransitivaSemDuplicatas++;
        }
        podeInserir = 1;
    }

    //VERIFICAR SE É EQUIVALENCIA
    char equivalencia = (Reflexiva && Simetrica && Transitiva) ? 'V' : 'F';

    //VERIFICAR SE É ORDEM PARCIAL
    char parcial = (Reflexiva && Antisimetrica && Transitiva) ? 'V' : 'F';

    FILE *ponteiroArquivoSaida;
    ponteiroArquivoSaida = fopen("output.txt", "w");

    //PRINT SE É REFLEXIVA
    fprintf(ponteiroArquivoSaida, "Reflexiva: ");
    if (Reflexiva)
    {
        fprintf(ponteiroArquivoSaida, "V\n");
    }
    else
    {
        fprintf(ponteiroArquivoSaida, "F\n");
        for (int i = 0; i < numeroDeFaltamParaSerReflexiva; i++)
        {
            fprintf(ponteiroArquivoSaida, "(%d,%d); ", faltaParaSerReflexiva[i].x, faltaParaSerReflexiva[i].y);
        }
        fprintf(ponteiroArquivoSaida, "\n");
    }

    // PRINT SE É IRREFLEXIVA
    fprintf(ponteiroArquivoSaida, "Irreflexiva: ");
    if (Irreflexiva)
    {
        fprintf(ponteiroArquivoSaida, "V\n");
    }
    else
    {
        fprintf(ponteiroArquivoSaida, "F\n");
        for (int i = 0; i < numeroDeFaltamParaSerIrreflexiva; i++)
        {
            fprintf(ponteiroArquivoSaida, "(%d,%d); ", faltaParaSerIrreflexiva[i].x, faltaParaSerIrreflexiva[i].y);
        }
        fprintf(ponteiroArquivoSaida, "\n");
    }

    //PRINT SE É SIMÉTRICA
    fprintf(ponteiroArquivoSaida, "Simétrica: ");
    if (Simetrica)
    {
        fprintf(ponteiroArquivoSaida, "V\n");
    }
    else
    {
        fprintf(ponteiroArquivoSaida, "F\n");
        for (int i = 0; i < numeroDeFaltamParaSerSimetrica; i++)
        {
            fprintf(ponteiroArquivoSaida, "(%d,%d); ", faltaParaSerSimetrica[i].x, faltaParaSerSimetrica[i].y);
        }
        fprintf(ponteiroArquivoSaida, "\n");
    }

    //PRINT SE É ANTI-SIMÉTRICA
    fprintf(ponteiroArquivoSaida, "Anti-simétrica: ");
    if (Antisimetrica)
    {
        fprintf(ponteiroArquivoSaida, "V\n");
    }
    else
    {
        fprintf(ponteiroArquivoSaida, "F\n");
        for (int i = 0; i < numeroDeFaltamParaSerAntisimetrica; i++)
        {
            fprintf(ponteiroArquivoSaida, "(%d,%d); ", faltaParaSerAntisimetrica[i].x, faltaParaSerAntisimetrica[i].y);
        }
        fprintf(ponteiroArquivoSaida, "\n");
    }

    //PRINT SE É ASSIMÉTRICA
    fprintf(ponteiroArquivoSaida, "Assimétrica: ");
    if (Assimetrica)
    {
        fprintf(ponteiroArquivoSaida, "V\n");
    }
    else
    {
        fprintf(ponteiroArquivoSaida, "F\n"); //Removi o print dos elementos pois mudaram a saída
    }

    //PRINT SE É TRANSITIVA
    fprintf(ponteiroArquivoSaida, "Transitiva: ");
    if (Transitiva)
    {
        fprintf(ponteiroArquivoSaida, "V\n");
    }
    else
    {
        fprintf(ponteiroArquivoSaida, "F\n");
        for (int i = 0; i < numeroDeFaltamParaSerTransitivaSemDuplicatas; i++)
        {
            fprintf(ponteiroArquivoSaida, "(%d,%d); ", faltamParaSerTransitivaSemDuplicatas[i].x, faltamParaSerTransitivaSemDuplicatas[i].y);
        }
        fprintf(ponteiroArquivoSaida, "\n");
    }

    //PRINT SE É EQUIVALENCIA
    fprintf(ponteiroArquivoSaida, "Relação de equivalência: %c\n", equivalencia);

    //PRINT SE É ORDEM PARCIAL
    fprintf(ponteiroArquivoSaida, "Relação de ordem parcial: %c\n", parcial);

    //PRINT O FECHO TRANSITIVO
    fprintf(ponteiroArquivoSaida, "Fecho transitivo da relação:");
    for (int i = 0; i < quantidadeDeRelacoes; i++)
    {
        fprintf(ponteiroArquivoSaida, "(%d,%d); ", relacoes[i].x, relacoes[i].y);
    }
    for (int i = 0; i < numeroDeFaltamParaSerTransitivaSemDuplicatas; i++)
    {
        fprintf(ponteiroArquivoSaida, "(%d,%d); ", faltamParaSerTransitivaSemDuplicatas[i].x, faltamParaSerTransitivaSemDuplicatas[i].y);
    }
    fprintf(ponteiroArquivoSaida, "\n");

    fclose(ponteiroArquivoSaida);
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