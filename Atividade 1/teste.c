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

/*
    Como a nova imagem gerada será formada de char, foi necessário
    definir um novo tipo 
*/
typedef char *imageASCII;

/*
    Para melhor visualização para resolver problemas enfrentados ao longo da realização
    desse código, preferi definir esse valor, que representa quantos elementos serão 
    colocados no arquivo de saída por linha
*/
#define POR_LINHA 99

/*
    Função que calcula a amostragem das Colunas
    Parâmetros:
        nc = Número de colunas da imagem original
        *coluna = Nova quantidade de colunas passadas pelo usuária
*/
int amostragemColuna(int nc, char *coluna)
{
    int valor = atoi(coluna);
    valor = (nc * 1) / valor;
    return valor;
}

/*
    Função que calcula a amostragem das Linhas
    Parâmetros:
        nr = Número de linhas da imagem original
        *linha = Nova quantidade de linhas passadas pelo usuária
*/
int amostragemLinha(int nr, char *linha)
{
    int valor = atoi(linha);
    valor = (nr * 1) / valor;
    return valor;
}

/*
    Função que obtem que extrai da string os caracteres e os coloca em um vetor
    Parâmetros:
        *simbolos = String de Caracteres
*/
char* obtemSimbolos(char *simbolos)
{
    char *simbs = simbolos;
    return simbs;
}

/*
    Função que calcula quantos niveis de cinza irá codificar cada char do string de caracteres
    Parâmetros:
        max = Máximo tom de cinza
        tamanho = Tamanho da string de caracteres

*/
int quantizacao(int max, int tamanho)
{
    //int valor = round((ml) / tamanho);
    float valor = (float)(max) / tamanho;
    int x = round (valor);
    /*
    if(tamanho * x < ml){
        printf("Sobra da quantizacao: %d\n", (ml -(tamanho * valor )));
    }
    if(tamanho * x > ml){
        printf("Excesso da quantizacao: %d\n", ((tamanho * x )-ml));
    }
    */
    return x;
}

/*
    Função que irá transformar a imagem nr x nc na imagem numL x numC através dos valores da amostra das coluna e das linhas
    Parâmetros:
        In = Imagem de entrada -> Imagem original inserida pelo usuário
        Out = Imagem nr x numC -> Imagem com as colunas transformadas
        Out2 = Imagem numL x numC -> Imagem com as colunas e linhas transformadas
        nr = Número de linhas da imagem original
        nc = Número de colunas da imagem original
        numL = Número de linhas da nova imagem definida pelo usuário
        numC = Número de colunas da nova imagem definida pelo usuário
        amostraC = Amostra do tamanho da coluna
        amostraL = Amostra do tamanho da linha
        quantidade = Quantização dos valores de cinza
        *simbolos = Vetor com os caracteres desejados pelo usuário

*/
void asci(image In, image Out, image Out2, int nr, int nc, int numL, int numC, int amostraC, int amostraL, int quantidade, char *simbolos)
{
    int x,y;
    /*
        Primeiro iremos obter os valores necessários para formar a imagem com o novo número de colunas
        Ou seja, ou final desse primeiro 'for' iremos obter uma imagem nr x numC
    */
    for(int i = 0; i < nr; i++)
    {
        x = 0;
        for(int j = 0; j < nc; j= j + amostraC)
        {
            Out[i * numC + x] = In[i * nc + j];
            x++;            
        }
    }
    /*
        Agora iremos obter os valores necessários para formar a imagem com o novo número de linhas,
        usando a imagem já com o novo número de colunas
        Ou seja, ou final desse primeiro 'for' iremos obter uma imagem numL x numC
    */
    for(int i = 0; i < numC; i++)
    {
        x = i;
        y=i;
        for(int j = 0; j < numL; j++)
        {
            Out2[x] = Out[i+j*numC*amostraL];
            x = x + numC;
        }
    }

}

/*
    Função que irá transformar os valores de tons de cinza da imagem em seus caracteres correspondentes
    Parâmetros:
        In = Imagem de entrada -> Imagem já com o novo tamanho definido na entrada pelo usuário
        Out = Imagem de saida -> Imagem com os caracteres correspondentes
        numL = Número de linhas da nova imagem definida pelo usuário
        numC = Número de colunas da nova imagem definida pelo usuário
        amostraC = Amostra do tamanho da coluna
        amostraL = Amostra do tamanho da linha
        quantidade = Quantização dos valores de cinza
        *simbolos = Vetor com os caracteres desejados pelo usuário
        max = Máximo tom de cinza
*/
void caracteres(image In, imageASCII Out, int numL, int numC, int amostraC, int amostraL, int quantidade, char *simbolos, int max){
    int numSimb = strlen(simbolos);
    int vet[numSimb];
    int def = 0; //Variável para identificar se aquele valor já foi convertido para char -> 0 = não foi convertido; 1 = já foi convertido
    for(int y = 0; y < numSimb; y++ ){
        if(y == (numSimb-1)){
            vet[y] = max;
        }
        else{
            vet[y] = ((y+1)*quantidade);
        }
        //printf("vet[%d]=%d  simb = %c\n", y, vet[y], simbolos[y]);
    }
    for(int i = 0; i < numL; i++)
    {
        for(int j = 0; j < numC; j++)
        {
            for(int x = 0; x < numSimb; x++){
                if (In[i * numC + j] <= vet[x] && def == 0){  
                    Out[i * numC + j] = simbolos[x];
                    def = 1; 
                    //printf("In[%d]=%d   Out=%c\n", (i * numC + j), In[i * numC + j], Out[i * numC + j]);
                }
            }
            def = 0;
        }
    }   
}

/*
    Função para imprimir a imagem em ASCII no terminal
    Parâmetros:
        Out = Imagem com os chars
        numL = Número de linhas da imagem
        numC = Número de colunas da imagem
*/
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

void msg2(int numL, int numC, int amostraC, int amostraL, int quantidade, int numSimb){
    printf("\nInformacoes - Imagem em ASCII:");
    printf("\n---------------------------------\n");
    printf("Numero de Linhas............: %d \n", numL);
    printf("Numero de colunas...........: %d \n", numC);
    printf("Numero de simbolos..........: %d \n", numSimb);
    printf("Amostragem das linhas.......: %d \n", amostraL);
    printf("Amostragem das colunas......: %d \n", amostraC);
    printf("Quantificacao de char.......: %d \n\n", quantidade);

}


void img_put2(imageASCII img, char *name, int nr, int nc, int ml, int tp)
{
    int count;
    FILE *fimg;
    ERROR((fimg = fopen(name, "wt")) == NULL, errormsg("Image creation error: <%s>", name));
    /*
    fprintf(fimg, "P%c\n", tp + '0');
    fputs(CREATOR, fimg);
    fprintf(fimg, "%d  %d\n", nc, nr);
    if (tp != BW)
        fprintf(fimg, "%d\n", ml);
    */
    count = 0;
    for (int i = 0; i < nr * nc; i++)
    {
        if (tp != COLOR)
        {
            char x = img[i];
            fprintf(fimg, "%c", x);
        }
        else
        {
            int r = (img[i] >> 16) & 0xFF;
            int g = (img[i] >> 8) & 0xFF;
            int b = img[i] & 0xFF;
            fprintf(fimg, "%3d %3d %3d ", r, g, b);
        }
        count++;
        if (count > POR_LINHA)
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
    image In, Out, Out2;

    if (argc < 5)
        msg(argv[0]);
    img_name(argv[1], nameIn, nameOut, GRAY);
    //-- read image
    In = img_get(nameIn, &nr, &nc, &ml, GRAY);
    Out = img_alloc(nr, nc);
    
    //-- transformation
    amostraC = amostragemColuna(nc, argv[2]);
    amostraL = amostragemLinha(nr, argv[3]);

    Out2 = img_alloc(nr, nc);
    imageASCII Ascii = (imageASCII)malloc(atoi(argv[3]) * atoi(argv[2]) * sizeof(char));

    simbolos = obtemSimbolos(argv[4]);

    quant = quantizacao(ml, strlen(simbolos));

    asci(In, Out, Out2, nr, nc, atoi(argv[3]), atoi(argv[2]), amostraC, amostraL, quant, simbolos);
    msg2(atoi(argv[3]), atoi(argv[2]),amostraC, amostraL, quant, strlen(simbolos));
    caracteres(Out2, Ascii, atoi(argv[3]), atoi(argv[2]),amostraC, amostraL, quant, simbolos, ml);
    //imprime(Dog, atoi(argv[3]), atoi(argv[2]));

    //-- save image
    img_put2(Ascii, nameOut, atoi(argv[3]), atoi(argv[2]), ml, GRAY);
    //img_put(Teste, nameOut, atoi(argv[3]), atoi(argv[2]), ml, GRAY);
    //img_put(Out, nameOut, nr, atoi(argv[2]), ml, GRAY);
    sprintf(cmd, "%s %s &", VIEW, nameOut);
    system(cmd);
    img_free(In);
    img_free(Out);
    img_free(Out2);
    free(Ascii);
    return 0;
}
