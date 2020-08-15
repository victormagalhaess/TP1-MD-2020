#include <stdio.h>
#include <stdlib.h>
#define TAMANHO_MAXIMO_ARQUIVO 1000

typedef struct
{
    int x;
    int y;
} ParOrdenado;

int main()
{

    FILE *ponteiroArquivo;
    if ((ponteiroArquivo = fopen("input.txt", "r")) == NULL)
    {
        printf("Arquivo não encontrado, cheque se o arquivo input.txt está na mesma pasta que o executável!");
        exit(1);
    }
    int quantidadeDeRelacoes = 0;
    ParOrdenado relacoes[TAMANHO_MAXIMO_ARQUIVO];
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

    for (int i = 0; i < numeroDeElementos; i++)
    {
        printf("%d\n", elementos[i]);
    }

    for (int i = 0; i < quantidadeDeRelacoes; i++)
    {
        printf("x: %d y: %d \n", relacoes[i].x, relacoes[i].y);
    }

    return 0;
}
