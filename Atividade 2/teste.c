#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
    unsigned char x = 209;
    unsigned char byte = 10;
    printf("Entrada = %d \n", x);
    printf("X = %d \n", (x & 0xFE));
    printf("X + 1 = %d \n", ((x+1) & 0xFE));
    printf("X - 1 = %d \n", ((x-1) & 0xFE));

    //char string_binaria[] = "00101110";
    //char* endptr;

    // Converte a string binária em um número decimal
    //long decimal = strtol(string_binaria, &endptr, 2);

    //printf("%ld\n", decimal);

    
    //byte = byte + '1';
    //printf("X+1 %c \n", (x |0x01));


    /*int x = 41; 
    printf("x << 1 = %d\n", x << 1); 
    printf("x >> 1 = %d\n", x >> 1);
    printf("x >> 1 = %d\n", x | 1); 
    printf("x >> 1 = %d\n", x & 254); */

    return 0;
}