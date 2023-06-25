/*---------------------------------------------------------
 * Image Processing
 * 
 * Steganography - decode
 *---------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "imagelib.h"
#define DEBUG(x) x


void decode(image In)
{
    FILE *file;
    char name[100];
    int fsize;
    unsigned char byte;
    int tamanhoImagem = In->nc * In->nr;
    //printf("tamanho = %d", tamanhoImagem);

    // decode the name

    int verificaNome = 0; // Variável para verificar se chegou no fim do nome 
    unsigned char bit; //Variável que irá receber o bit analisado da imagem

    int R, G, B;
    int pixel;
    unsigned char suc, ante, x; // suc = Sucessor; ante = Antecessor
    enum //variável para indicar qual banda rgb está sendo analizada
    {
        red = 1,
        green,
        blue
    };
    int banda = 1; //1 = red, 2=green, 3=blue
    char bits[8];
    int contBit = 0;
    int teste;
    int teste2 = 0;
    char* endptr;
    char simb;

    do{
        for(int i = 0; i < tamanhoImagem; i++)
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
                printf("R = %d, R+1 = %d, R-1 = %d \n", R, R+1, R-1);
                printf("x= %d suc=%d ante=%d \n", x, suc, ante);
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
                printf("G = %d, G+1 = %d, G-1 = %d \n", G, G+1, G-1);
                printf("x= %d suc=%d ante=%d \n", x, suc, ante);
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
                printf("B = %d, B+1 = %d, B-1 = %d \n", B, B+1, B-1);
                printf("x= %d suc=%d ante=%d \n", x, suc, ante);
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
                contBit = 0;

                long decimal = strtol(bits, &endptr, 2);
                printf("%ld\n", decimal);
                simb = decimal;
                printf("simb = %c\n", simb);

                teste2++;
                if(teste2 == 5)
                {
                    printf("R = %d, G= %d, B= %d \n", R,G,B);
                    abort();
                }
            }

            banda++;
            if(banda > 3)
            {
                banda = 1;
            }

            
            /*for(int j = 0; j < 8; j++)
            {

                //byte = In->px[i]+'0';
                //printf(" int = %d \n",In->px[i]);
                //printf(" char = %c \n",byte);
                //byte = byte & 0xFE;
                //printf("%c \n",byte);
                /*if(In->px[i] == (byte - '0'))
                {
                    printf("px = %c  byte = %c \n", In->px[i]+'0',byte );
                    printf("O valor do bit eh zero \n");
                }
                else{
                    printf("px = %d  byte = %c \n", In->px[i],byte );
                    printf("MUDOU\n");
                }

                i++;

            }
            //printf("name = %s \n",name);*/

            
        }

    }while(verificaNome < 8);

    printf("File name: %s\n", name);
    
    // decode file size
    
    printf("File size: %d bytes\n", fsize);
    
    // decode file
    
    file = fopen(name, "wb");
    if (!file)
    {
        printf("Cannot create file %s\n", name);
        exit(10);
    }
    while (fsize)
    {
        // decode the bytes of the file
    
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
