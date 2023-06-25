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

    // decode the name

    int tamanhoImagem = In->nc * In->nr;
    //printf("tamanho = %d", tamanhoImagem);
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
    char bitsTam[32];
    int contBit = 0;
    //int teste2 = 0;
    char* endptr;
    char simb;
    long decimal;
    int fimNome = 0; //1= chegou no fim do nome do arquivo; 0 = Ainda não chegou no fim do arquivo
    int contTam = 0;
    char tamanho[32];
    int continuacao = 0;

    
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
            contBit = 0;
            decimal = strtol(bits, &endptr, 2);
            //printf("bits = %.8s\n",bits);
            printf("%ld\n", decimal);
            if(decimal == 0 && fimNome == 0)
            {
                fimNome = 1;
                continuacao = i;
                //name[i/8] = '\0';
                //printf("File name: %s\n", name);
                //printf("Nome do arquivo = %s\n", name);
                //abort();
            }
            /*Atribuindo o Nome enquanto não for o fim do nome do arquivo*/
            if(fimNome == 0){
                simb = decimal;
                //printf("simb = %c\n", simb);
                name[i/8] = simb;
                name[(i+1)/8] = '\0';
                printf("name[%d] = %c\n", i, name[i/8]);
            }    
        }
        banda++;
        if(banda > 3)
        {
            banda = 1;
        }
    }
    printf("File name: %s\n", name);
    
    contBit = 0;
    printf("conti = %d \n", continuacao);
    for(int i = continuacao + 1; i < tamanhoImagem; i++)
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
                bitsTam[contBit] = '0';
            }
            if(x == ante)
            {
                //printf("ESCONDEU UM\n");
                bitsTam[contBit] = '1';
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
                bitsTam[contBit] = '0';
            }
            if(x == ante)
            {
                //printf("ESCONDEU UM\n");
                bitsTam[contBit] = '1';
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
                bitsTam[contBit] = '0';
            }
            if(x == ante)
            {
                //printf("ESCONDEU UM\n");
                bitsTam[contBit] = '1';
            }
            break;
        }
        contBit++;
        if(contBit > 7)
        {
            contBit = 0;
            decimal = strtol(bits, &endptr, 2);
            printf("Tamanho = %ld\n", decimal);
        } 
        /*Operações Relacionadas ao tamanho do arquivo*/
        /*
        if(contBit > 31)
        {
            if(contTam == 0)
            {
                strcpy(tamanho,bitsTam);
                printf("bits = %s\n", bitsTam);
                printf("tamanho = %s\n", tamanho);
            }
            else{
                strcat(tamanho, bitsTam);
                if(contTam == 3)
                {
                    decimal = strtol(tamanho, &endptr, 2);
                    printf("Tamanho = %ld\n", decimal);
                    abort();
                }
            }
            contTam++;        
        }     */                  
    }
    
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
