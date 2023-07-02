/*---------------------------------------------------------
 * Image Processing
 * 
 * Steganography - decode
 *---------------------------------------------------------*/

/*−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
 *           UNIFAL − Universidade Federal de Alfenas.
 *             BACHARELADO EM CIENCIA DA COMPUTACAO.
 * Trabalho..: Steganography
 * Disciplina: Processamento de Imagens
 * Professor.: Luiz Eduardo da Silva
 * Aluno.....: Renan Magalhães Lage
 * Data......: 27/06/2023
 *−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "imagelib.h"
#define DEBUG(x) x


void decode(image In)
{
    FILE *file;
    char name[100]="";
    int fsize;
    unsigned char byte;

    int tamanhoImagem = In->nc * In->nr;
    int R, G, B;
    int pixel;
    unsigned char suc, ante, x; // suc = Sucessor; ante = Antecessor
    /*Variável para indicar qual banda rgb está sendo analizada*/
    enum 
    {
        red = 1,
        green,
        blue
    };
    int banda = 1; //1 = red, 2=green, 3=blue
    char bits[9] = "";
    char bitsTam[33] = "";
    int contBit = 0;
    char* endptr; //Ponteiro usado para a função strol
    char simb;
    long decimal;
    int fimNome = 0; //1= chegou no fim do nome do arquivo; 0 = Ainda não chegou no fim do arquivo
    int continuacao = 0;

    /*DECODIFICANDO O NOME*/
    for(int i = 0; i < tamanhoImagem && fimNome!=1; i++)
    {
        pixel = In->px[i];
        R = (pixel >> 16) & 0xFF;
        G = (pixel >> 8) & 0xFF;
        B = (pixel) & 0xFF;
        //printf("R = %d, G= %d, B= %d \n", R,G,B);
        switch (banda)
        {
        case red:
            x = (R & 0xFE);
            suc = ((R+1) & 0xFE);
            ante = ((R-1) & 0xFE);
            //printf("R = %d, R+1 = %d, R-1 = %d \n", R, R+1, R-1);
            //printf("x= %d suc=%d ante=%d \n", x, suc, ante);
            if(x == suc)
            {
                //printf("ESCONDEU ZERO\n");
                bits[contBit] = '0';
            }
            if(x == ante)
            {
                //printf("ESCONDEU UM\n");
                bits[contBit] = '1';
            }
            break;

        case green:
            x = (G & 0xFE);
            suc = ((G+1) & 0xFE);
            ante = ((G-1) & 0xFE);
            //printf("G = %d, G+1 = %d, G-1 = %d \n", G, G+1, G-1);
            //printf("x= %d suc=%d ante=%d \n", x, suc, ante);
            if(x == suc)
            {
                //printf("ESCONDEU ZERO\n");
                bits[contBit] = '0';
            }
            if(x == ante)
            {
                //printf("ESCONDEU UM\n");
                bits[contBit] = '1';
            }
            break;

        case blue:
            x = (B & 0xFE);
            suc = ((B+1) & 0xFE);
            ante = ((B-1) & 0xFE);
            //printf("B = %d, B+1 = %d, B-1 = %d \n", B, B+1, B-1);
            //printf("x= %d suc=%d ante=%d \n", x, suc, ante);
            if(x == suc)
            {
                //printf("ESCONDEU ZERO\n");
                bits[contBit] = '0';
            }
            if(x == ante)
            {
                //printf("ESCONDEU UM\n");
                bits[contBit] = '1';
            }
            break;
        }
        contBit++;
        if(contBit > 7)
        {     
            bits[contBit]= '\0';
            decimal = strtol(bits, &endptr, 2);
            //printf("%ld\n", decimal);
            if(decimal == 0)
            {
                fimNome = 1;
                continuacao = i;
            }
            /*Atribuindo o caracteres do NOME enquanto não for o fim do nome do arquivo*/
            if(fimNome == 0){
                
                name[i/8] = decimal;
                name[(i+1)/8] = '\0';
                //printf("name[%d] = %c\n", i/8, name[i/8]);
            }   
            
            contBit = 0;
        }
        banda++;
        if(banda > 3)
        {
            banda = 1;
        }
    }
    printf("File name: %s\n", name);
    
    contBit = 0;
    //printf("conti = %d \n", continuacao);

    /* DECODIFICANDO O TAMANHO */
    for(int i = 0; i < 32; i++, continuacao++)
    {
        pixel = In->px[continuacao+1];
        R = (pixel >> 16) & 0xFF;
        G = (pixel >> 8) & 0xFF;
        B = (pixel) & 0xFF;
        //printf("R = %d, G= %d, B= %d \n", R,G,B);
        switch (banda)
        {
        case red:
            x = (R & 0xFE);
            suc = ((R+1) & 0xFE);
            ante = ((R-1) & 0xFE);
            //printf("R = %d, R+1 = %d, R-1 = %d \n", R, R+1, R-1);
            //printf("x= %d suc=%d ante=%d \n", x, suc, ante);
            if(x == suc)
            {
                //printf("ESCONDEU ZERO\n");
                bitsTam[i] = '0';
            }
            if(x == ante)
            {
                //printf("ESCONDEU UM\n");
                bitsTam[i] = '1';
            }
            break;

        case green:
            x = (G & 0xFE);
            suc = ((G+1) & 0xFE);
            ante = ((G-1) & 0xFE);
            //printf("G = %d, G+1 = %d, G-1 = %d \n", G, G+1, G-1);
            //printf("x= %d suc=%d ante=%d \n", x, suc, ante);
            if(x == suc)
            {
                //printf("ESCONDEU ZERO\n");
                bitsTam[i] = '0';
            }
            if(x == ante)
            {
                //printf("ESCONDEU UM\n");
                bitsTam[i] = '1';
            }
            break;

        case blue:
            x = (B & 0xFE);
            suc = ((B+1) & 0xFE);
            ante = ((B-1) & 0xFE);
            //printf("B = %d, B+1 = %d, B-1 = %d \n", B, B+1, B-1);
            //printf("x= %d suc=%d ante=%d \n", x, suc, ante);
            if(x == suc)
            {
                //printf("ESCONDEU ZERO\n");
                bitsTam[i] = '0';
            }
            if(x == ante)
            {
                //printf("ESCONDEU UM\n");
                bitsTam[i] = '1';
            }
            break;
        }
        banda++;
        if(banda > 3)
        {
            banda = 1;
        }
    }
    bitsTam[32] = '\0';
    //printf("bitsTAM = %s\n",bitsTam) ;
    decimal = strtol(bitsTam, &endptr, 2);
    fsize = decimal;
    
    printf("File size: %d bytes\n", fsize);
    
    file = fopen(name, "wb");
    if (!file)
    {
        printf("Cannot create file %s\n", name);
        exit(10);
    }
    contBit = 0;
    while (fsize)
    {
        /* DECODIFICANDO O CONTEUDO */
        for(int i = 0; i < 8; i++, continuacao++)
        {
            pixel = In->px[continuacao+1];
            R = (pixel >> 16) & 0xFF;
            G = (pixel >> 8) & 0xFF;
            B = (pixel) & 0xFF;
            //printf("R = %d, G= %d, B= %d \n", R,G,B);
            switch (banda)
            {
            case red:
                x = (R & 0xFE);
                suc = ((R+1) & 0xFE);
                ante = ((R-1) & 0xFE);
                //printf("R = %d, R+1 = %d, R-1 = %d \n", R, R+1, R-1);
                //printf("x= %d suc=%d ante=%d \n", x, suc, ante);
                if(x == suc)
                {
                    //printf("ESCONDEU ZERO\n");
                    bits[i] = '0';
                }
                if(x == ante)
                {
                    //printf("ESCONDEU UM\n");
                    bits[i] = '1';
                }
                break;

            case green:
                x = (G & 0xFE);
                suc = ((G+1) & 0xFE);
                ante = ((G-1) & 0xFE);
                //printf("G = %d, G+1 = %d, G-1 = %d \n", G, G+1, G-1);
                //printf("x= %d suc=%d ante=%d \n", x, suc, ante);
                if(x == suc)
                {
                    //printf("ESCONDEU ZERO\n");
                    bits[i] = '0';
                }
                if(x == ante)
                {
                    //printf("ESCONDEU UM\n");
                    bits[i] = '1';
                }
                break;

            case blue:
                x = (B & 0xFE);
                suc = ((B+1) & 0xFE);
                ante = ((B-1) & 0xFE);
                //printf("B = %d, B+1 = %d, B-1 = %d \n", B, B+1, B-1);
                //printf("x= %d suc=%d ante=%d \n", x, suc, ante);
                if(x == suc)
                {
                    //printf("ESCONDEU ZERO\n");
                    bits[i] = '0';
                }
                if(x == ante)
                {
                    //printf("ESCONDEU UM\n");
                    bits[i] = '1';
                }
                break;
            }
            banda++;
            if(banda > 3)
            {
                banda = 1;
            }
        }
        bits[8] = '\0';
        //printf("conti = %d \n", continuacao);
        //printf("bits = %s \n", bits);
        decimal = strtol(bits, &endptr, 2);
        simb = decimal;
        //printf("simb = %c\n", simb);
        fprintf(file, "%c", simb);     

    
        fsize--;
    }
    fclose(file);
}

void msg(char *s)
{
    printf("\nSteganography - decode");
    printf("\n-------------------------------");
    printf("\nUSE.:  %s  <IMG.PPM>", s);
    printf("\nWhere:\n");
    printf("    <IMG.PPM>  Image file in PPM ASCII format\n\n");
    exit(20);
}

/*-----------------------------------------
  Main program
------------------------------------------*/
int main(int argc, char *argv[])
{
    char name[100];
    image In;
    char *p;
    if (argc < 2)
        msg(argv[0]);
    strcpy(name, argv[1]);
    p = strstr(name, ".ppm");
    if (p)
        *p = 0;
    strcat(name, ".ppm");
    In = img_get(name, COLOR);
    decode(In);
    img_free(In);
    return 0;
}
