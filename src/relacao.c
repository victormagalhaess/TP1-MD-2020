#include <stdio.h>
#include <stdlib.h>
#define TAMANHO_MAXIMO_ARQUIVO 1000

typedef struct
{
    int x;
    int y;
} ParOrdenado;

char *leDoArquivo()
{
    static char arquivo[TAMANHO_MAXIMO_ARQUIVO];
    FILE *ponteiroArquivo;
    if ((ponteiroArquivo = fopen("input.txt", "r")) == NULL)
    {
        printf("Arquivo não encontrado, cheque se o arquivo input.txt está na mesma pasta que o executável!");
        exit(1);
    }
    fscanf(ponteiroArquivo, "%[^EOF]", arquivo);
    int tamanhoArquivo = ftell(ponteiroArquivo);
    arquivo[tamanhoArquivo] = EOF;
    fclose(ponteiroArquivo);
    return arquivo;
}

int main()
{
    char *arquivo;
    arquivo = leDoArquivo();
    while (*arquivo != EOF)
    {
        printf("%c", *arquivo);
        arquivo++;
    }

    return 0;
}
