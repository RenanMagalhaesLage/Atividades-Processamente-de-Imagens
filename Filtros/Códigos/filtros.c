/*-------------------------------------------------------------------------
 * Operacao de convolucao
 * Por Luiz Eduardo da Silva.
 * 
 * Comando:
 * gcc imagelib.c negative.c -o negative
 * ./negative img.pgm
 *-------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "imagelib.h"

void ordena(int *v, int n)
{
    int i, j, tmp;
    for (i = 0; i < n; i++)
    {
        int m = i;
        for (j = i + 1; j < n - 1; j++)
            if (v[j] < v[m])
                m = j;
        tmp = v[i];
        v[i] = v[m];
        v[m] = tmp;
    }
}
/*
void convolucao(image In, image Out, int nl, int nc, int mn)
{
    int w[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}};
    for (int i = 1; i < nl - 1; i++)
        for (int j = 1; j < nc - 1; j++)
        {
            int sum = 0, vetor[9];
            vetor[0] = In[(i - 1) * nc + (j - 1)];
            vetor[1] = In[(i - 1) * nc + j];
            vetor[2] = In[(i - 1) * nc + (j + 1)];
            vetor[3] = In[i * nc + (j - 1)];
            vetor[4] = In[i * nc + j];
            vetor[5] = In[i * nc + (j + 1)];
            vetor[6] = In[(i + 1) * nc + (j - 1)];
            vetor[7] = In[(i + 1) * nc + j];
            vetor[8] = In[(i + 1) * nc + (j + 1)];
            ordena(vetor, 9);
            // for (int y = -1; y <= 1; y++)
            //     for (int x = -1; x <= 1; x++)
            //     {
            //         vetor[0] = In[(i + y) * nc + (j + x)] * w[y + 1][x + 1];
            //     }
            // valor = sum;
            // if (sum < 0)
            //     valor = 0;
            Out[i * nc + j] = vetor[4];
            // Out[i * nc + j] = valor;
        }
}*/

/*
Função de Convolução - Deixa a imagem um pouco embaçada
*/
void convolucao(image In, image Out, int nl, int nc, int mn){
    int sum;
    for(int i = 1; i < nl - 1; i++){
        for(int j = 1; j < nc - 1; j++)
        {
            sum = 0;
            for(int y = -1; y <= 1; y++)
            {
                for(int x = -1; x <= 1; x++)
                {
                    int px = (i + y) * nc + (j + x);
                    sum += In[px];
                }
            }
            Out[i * nc + j] = sum / 9;
        }
    }
    // Aguçamento
    //for (int i = 0; i < nl * nc; i++){
    //    Out[i] = abs(In[i] - Out[i]) + In[i];
    //}
}

void laplaciano(image In, image Out, int nl, int nc, int mn){
    int laplaciano[3][3] =
        {0, 1, 0,
         1, -4, 1,
         0, 1, 0};
    int sum, max = -1;
    for(int i = 1; i < nl - 1; i++)
    {
        for(int j = 1; j < nc - 1; j++)
        {
            sum = 0;
            for(int y =-1; y <= 1; y++)
            {
                for(int x = -1; x <= 1; x++)
                {
                    int px = (i + y) * nc + (j + x);
                    sum += In[px] * laplaciano[y+1][x+1];
                }
            }
            if(abs(sum) > max){
                max = abs(sum);
            }
            Out[i * nc + j] = abs(sum);
        }
    }
    for(int i = 0; i < nl * nc; i++)
    {
        Out[i] = ((float)Out[i] / max) * mn;
    }
}

void negativo(image In, image Out, int nl, int nc, int mn)
{
    for (int i = 0; i < nl * nc; i++)
        Out[i] = mn - In[i];
}

void msg(char *s)
{
    printf("\nProcessamento de Imagens - Filtros");
    printf("\n----------------------------------");
    printf("\nUso:  %s  nome-imagem[.pgm] \n\n", s);
    printf("    nome-imagem[.pgm] é o nome do arquivo da imagem \n");
    exit(1);
}

/*-------------------------------------------------------------------------
 * main function
 *-------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    int nc, nr, ml, tp;
    char *p, nameIn[100], nameOut[100], cmd[110];
    image In, Out;
    if (argc < 2)
        msg(argv[0]);
    img_name(argv[1], nameIn, nameOut, GRAY);
    //-- read image
    In = img_get(nameIn, &nr, &nc, &ml, GRAY);
    Out = img_alloc(nr, nc);
    //-- transformation
    int opcao;

    printf("\n+---------------------------------------------------------------+");
    printf("\n|              Bem Vindo a edicao de imagens pgm!               |");
    printf("\n|       Escolha qual operacao com a imagem deseja realizar      |");
    printf("\n|                                                               |");
    printf("\n|       1) Imagem Negativa                                      |");
    printf("\n|       2) Convolucao / Embacar a imagem                        |");
    printf("\n|       3) Laplaciano - Fundo Preto                             |");
    printf("\n|       4) Laplaciano - Fundo Branco                            |");
    printf("\n|       0) EXIT                                                 |");
    printf("\n|                                                               |");
    printf("\n+---------------------------------------------------------------+\n");

    printf(" Digite a opcao desejada : \n");
    scanf("%d",&opcao);

    /*Caso o usuario digitar algum número que esta fora das 
    opções exibe a seguinte mensagem:*/
    while ( opcao < 0 || opcao > 4){
        printf(" ATENCAO - Digite um numero que esteja entre as opcoes: \n");
        scanf("%d",&opcao);
    }
    switch (opcao)
    {
    case 1:
        negativo(In, Out, nr, nc, ml);
        img_put(Out, nameOut, nr, nc, ml, GRAY);
        sprintf(cmd, "%s %s &", VIEW, nameOut);
        system(cmd);
        img_free(In);
        img_free(Out);
        break;
    case 2:
        convolucao(In, Out, nr, nc, ml);
        img_put(Out, nameOut, nr, nc, ml, GRAY);
        sprintf(cmd, "%s %s &", VIEW, nameOut);
        system(cmd);
        img_free(In);
        img_free(Out);
        break;
    case 3:
        laplaciano(In, Out, nr, nc, ml);
        img_put(Out, nameOut, nr, nc, ml, GRAY);
        sprintf(cmd, "%s %s &", VIEW, nameOut);
        system(cmd);
        img_free(In);
        img_free(Out);
        break;
    case 4:
        laplaciano(In, Out, nr, nc, ml);
        negativo(Out, Out, nr, nc, ml);
        img_put(Out, nameOut, nr, nc, ml, GRAY);
        sprintf(cmd, "%s %s &", VIEW, nameOut);
        system(cmd);
        img_free(In);
        img_free(Out);
        break;      
    case 0:
        return 0;
    }

    return 0;
}
