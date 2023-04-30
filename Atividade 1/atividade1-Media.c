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
#include <math.h>
#include "imagelib.h"

typedef char *imageASCII;
#define PER_LINE 99

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

/*Função que obtem um vetor com os caracteres*/
char* obtemSimbolos(char *simbolos)
{
    int tamanho = strlen(simbolos);
    //printf("%d\n", tamanho);
    char *simbs = simbolos;
    /*for(int i = 0; i < tamanho; i++)
    {
        printf("simb: %c \n", simbs[i]);
    }*/
    return simbs;
    //char teste = simbolos[0];
}

/*Função que calcula quantos niveis de cinza irá representar um caracter*/
int quantizacao(int ml, int tamanho)
{
    //int valor = round((ml) / tamanho);
    float valor = (float)(ml * 1) / tamanho;
    int x = round (valor);
    printf("valor = %d e %f\n",x, valor);
    //int valor = (ml * 1) / tamanho;
    if(tamanho * valor < ml){
        printf("Sobra da quantizacao: %d\n", (ml -(tamanho * valor )));
    }
    //printf("valor = %d\n", valor);
    return x;
}

void asci(image In, image Out, image Out2, int nr, int nc, int mn, int numL, int numC, int amostraC, int amostraL, int quantidade, char *simbolos)
{
    int soma;
    int cont = amostraC;
    int x,y;
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
                Out[i * numC + x] = (soma / amostraC);
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
        x = i;
        y=i;
        for(int j = 0; j < nr; j++) // x = i + nc irá acessar os elementos de cada coluna
        {
            soma = soma + Out[x];
            cont--;
            if(cont == 0){
                cont = amostraL;
                Out2[y] = soma / amostraL;
                //printf("Out[%d] = %d\n",y,Out2[y]);
                y= y + numC;; //serve para acessar a posição correta em Out
                soma = 0;
            }
            x = x + numC;
        }
    }

}

void caracteres(image In, imageASCII Out, int numL, int numC, int amostraC, int amostraL, int quantidade, char *simbolos){
    int x = 0;
    int numSimb = strlen(simbolos);
    for(int y = quantidade, yant = 0; y <= (numSimb*quantidade); yant = y, y = y + quantidade ){
        for(int i = 0; i < numL; i++)
        {
            for(int j = 0; j < numC; j++)
            {
                if (In[i * numC + j] < y && In[i * numC + j] > yant){  
                    Out[i * numC + j] = simbolos[x];
                    //printf("%c  ", Out[i * numC + j]);
                }
            }
        }
        //printf("x=%d\n", x);
        x++;
    }
    
}

void imprime(imageASCII Out, int numL, int numC){
    int cont = 0;
    for(int i = 0; i < numL; i++)
    {
        for(int j = 0; j < numC; j++)
        {
            printf("%c", Out[i * numC + j]);
        }
        printf("\n");
    }
}

void msg2(int numL, int numC, int amostraC, int amostraL, int quantidade, int numSimb){
    printf("\nImage ASCII Informations:");
    printf("\n--------------------------\n");
    printf("Number of rows..............: %d \n", numL);
    printf("Number of columns...........: %d \n", numC);
    printf("Numero de simbolos..........: %d \n", numSimb);
    printf("Amostragem das linhas.......: %d \n", amostraL);
    printf("Amostragem das colunas......: %d \n", amostraC);
    printf("Quantificacao. .............: %d \n\n", quantidade);

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


void img_put2(imageASCII img, char *name, int nr, int nc, int ml, int tp)
{
    int count;
    FILE *fimg;
    ERROR((fimg = fopen(name, "wt")) == NULL, errormsg("Image creation error: <%s>", name));
    fprintf(fimg, "P%c\n", tp + '0');
    fputs(CREATOR, fimg);
    fprintf(fimg, "%d  %d\n", nc, nr);
    if (tp != BW)
        fprintf(fimg, "%d\n", ml);
    count = 0;
    for (int i = 0; i < nr * nc; i++)
    {
        if (tp != COLOR)
        {
            char x = img[i];
            fprintf(fimg, "%c ", x);
        }
        else
        {
            int r = (img[i] >> 16) & 0xFF;
            int g = (img[i] >> 8) & 0xFF;
            int b = img[i] & 0xFF;
            fprintf(fimg, "%3d %3d %3d ", r, g, b);
        }
        count++;
        if (count > PER_LINE)
        {
            fprintf(fimg, "\n");
            count = 0;
        }
    }
    fclose(fimg);
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
    imageASCII Dog = (imageASCII)malloc(atoi(argv[3]) * atoi(argv[2]) * sizeof(char));

    simbolos = obtemSimbolos(argv[4]);

    quant = quantizacao(ml, strlen(simbolos));

    asci(In, Out, Teste, nr, nc, ml, atoi(argv[3]), atoi(argv[2]), amostraC, amostraL, quant, simbolos);
    msg2(atoi(argv[3]), atoi(argv[2]),amostraC, amostraL, quant, strlen(simbolos));
    caracteres(Teste, Dog, atoi(argv[3]), atoi(argv[2]),amostraC, amostraL, quant, simbolos);
    imprime(Dog, atoi(argv[3]), atoi(argv[2]));
    //-- save image
    //img_put2(Dog, nameOut, atoi(argv[3]), atoi(argv[2]), ml, GRAY);
    img_put(Teste, nameOut, atoi(argv[3]), atoi(argv[2]), ml, GRAY);
    sprintf(cmd, "%s %s &", VIEW, nameOut);
    system(cmd);
    img_free(In);
    img_free(Out);
    img_free(Teste);
    return 0;
}
