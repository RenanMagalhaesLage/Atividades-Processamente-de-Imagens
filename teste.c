#include <stdio.h>
#include <stdlib.h>

#define MAX_PIXEL_VALUE 255

int main(int argc, char *argv[]) {
    FILE *input_file, *output_file;
    char *input_filename, *output_filename, *quantization_string;
    int width, height, max_value, pixel, sample_width, sample_height, quantization_length;
    unsigned char character;

    if (argc != 6) {
        printf("Usage: %s input_file.pgm output_file.txt sample_width sample_height quantization_string\n", argv[0]);
        return 1;
    }

    input_filename = argv[1];
    output_filename = argv[2];
    sample_width = atoi(argv[3]);
    sample_height = atoi(argv[4]);
    quantization_string = argv[5];
    quantization_length = strlen(quantization_string);

    input_file = fopen(input_filename, "rb");
    if (input_file == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }

    // read PGM header
    fscanf(input_file, "P5 %d %d %d ", &width, &height, &max_value);

    output_file = fopen(output_filename, "w");
    if (output_file == NULL) {
        printf("Error opening output file.\n");
        return 1;
    }

    // convert pixels to characters and write to output file
    for (int y = 0; y < height; y += sample_height) {
        for (int x = 0; x < width; x += sample_width) {
            int sum = 0;
            int count = 0;

            for (int j = 0; j < sample_height; j++) {
                for (int i = 0; i < sample_width; i++) {
                    if (y+j < height && x+i < width) {
                        fseek(input_file, (y+j)*width*sizeof(int) + (x+i)*sizeof(int), SEEK_SET);
                        fread(&pixel, sizeof(int), 1, input_file);
                        sum += pixel;
                        count++;
                    }
                }
            }

            int average = (int) (1.0 * sum / count);
            int quantization_index = (int) (1.0 * average / MAX_PIXEL_VALUE * quantization_length);
            quantization_index = quantization_index >= quantization_length ? quantization_length - 1 : quantization_index;
            character = quantization_string[quantization_index];
            fprintf(output_file, "%c", character);
        }
        fprintf(output_file, "\n");
    }

    fclose(input_file);
    fclose(output_file);

    return 0;
}
