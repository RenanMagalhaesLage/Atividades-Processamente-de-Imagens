/*−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
 *           UNIFAL − Universidade Federal de Alfenas.
 *             BACHARELADO EM CIENCIA DA COMPUTACAO.
 * Trabalho..: Imagem ASCII
 * Disciplina: Processamento de Imagens
 * Professor.: Luiz Eduardo da Silva
 * Aluno.....: Renan Magalhães Lage
 * Data......: 21/04/2023
 *−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imagelib.h"


int amostragemColuna(int nc, char *coluna)
{
    int valor = atoi(coluna);
    valor = (nc * 1) / valor;
    return valor;
}

int amostragemLinha(int nr, char *linha)
{
    int valor = atoi(linha);
    valor = (nr * 1) / valor;
    return valor;
}

char* obtemSimbolos(char *simbolos)
{
    int tamanho = strlen(simbolos);
    char *simbs = simbolos;
    /*for(int i = 0; i < tamanho; i++)
    {
        printf("%c \n", simbs[i]);
    }*/
    return simbs;
    //char teste = simbolos[0];
}

int quantizacao(int ml, int tamanho)
{
    int valor = (int)(ml * 1) / tamanho;
    //printf("valor = %d\n", valor);
    return valor;
}

void asci(image In, image Out, image Out2, int nr, int nc, int mn, int numL, int numC, int amostraC, int amostraL, int quantidade, char *simbolos)
{
    int soma;
    int cont = amostraC;
    int x;
    int pixels = 0;
    //Primeiro iremos rezlizar a média dos valores da amostra da coluna
    //no final desse for teremos uma imagem com o novo numero de coluna porém com o numero de linhas originais
    for(int i = 0; i < nr; i++)
    {
        x = 0;
        for(int j = 0; j < nc; j++)
        {
            soma = soma + In[i * nc + j];
            cont--;
            if(cont == 0){//foi somado os oito números
                cont = amostraC;
                Out[i * numC + x] = soma / amostraC;
                x++; //serve para acessar a posição correta em Out
                soma = 0;
            }
        }
    }
    soma = 0;
    cont = amostraL;
    //Agora iremos rezlizar a média dos valores da amostra da linha
    for(int i = 0; i < numC; i++)
    {
        x = 0;
        for(int j = 0; j < nr; j++, x = i + numC) // x = i + nc irá acessar os elementos de cada coluna
        {
            soma = soma + Out[x];
            cont--;
            if(cont == 0){
                cont = amostraL;
                Out2[i * numC + x] = soma / amostraL;
                pixels++;
                x++; //serve para acessar a posição correta em Out
                soma = 0;
            }
        }
    }
    printf("pixels = %d\n", pixels);

}

void msg(char *s)
{
    printf("\nImagem em ASCII");
    printf("\n-------------------------------");
    printf("\nUso:  %s  nome-imagem[.pgm]  <ncolunas> <nlinhas> <string>\n\n", s);
    printf("    -nome-imagem[.pgm] e o nome do arquivo da imagem \n");
    printf("    -ncolunas e o numero de colunas que deseja na imagem  \n");
    printf("    -nlinhas e o numero de linhas que deseja na imagem  \n");
    printf("    -string sao os caracteres que sedeja usar para produzir a imagem\n\n");
    exit(1);
}

/*-------------------------------------------------------------------------
 * main function
 *-------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    int nc, nr, ml, tp;
    char *p, nameIn[100], nameOut[100], cmd[110];
    int amostraC, amostraL, quant;
    char *simbolos;
    image In, Out, Teste;
    if (argc < 5)
        msg(argv[0]);
    img_name(argv[1], nameIn, nameOut, GRAY);
    //-- read image
    In = img_get(nameIn, &nr, &nc, &ml, GRAY);
    Out = img_alloc(nr, nc);
    
    //-- transformation
    amostraC = amostragemColuna(nc, argv[2]);
    amostraL = amostragemLinha(nr, argv[3]);

    //alocando vetor para a nova imagem
    //Teste = img_alloc(atoi(argv[2]), atoi(argv[3]));
    Teste = img_alloc(nr, nc);

    simbolos = obtemSimbolos(argv[4]);

    quant = quantizacao(ml, strlen(simbolos));

    asci(In, Out, Teste, nr, nc, ml, atoi(argv[3]), atoi(argv[2]), amostraC, amostraL, quant, simbolos);


    //convolucao(In, Out, nr, nc, ml);
    //-- save image
    img_put(Out, nameOut, atoi(argv[3]), atoi(argv[2]), ml, GRAY);
    sprintf(cmd, "%s %s &", VIEW, nameOut);
    system(cmd);
    img_free(In);
    img_free(Out);
    img_free(Teste);
    return 0;
}
