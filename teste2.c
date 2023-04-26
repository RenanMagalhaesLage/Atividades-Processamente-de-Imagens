#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *input_file, *output_file;
    char *input_filename = "imagem.pgm";
    char *output_filename = "imagem_redimensionada.pgm";
    int width = 800, height = 600, max_value;
    int new_width = 100, new_height = 30;
    int x_ratio = (int)((width << 16)/new_width) + 1;
    int y_ratio = (int)((height << 16)/new_height) + 1;
    int *buffer = (int*)malloc(width * height * sizeof(int));
    unsigned char *output_buffer = (unsigned char*)malloc(new_width * new_height * sizeof(unsigned char));

    if (buffer == NULL || output_buffer == NULL) {
        printf("Error allocating memory.\n");
        return 1;
    }

    input_file = fopen(input_filename, "rb");
    if (input_file == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }

    // read PGM header
    fscanf(input_file, "P5 %d %d %d ", &width, &height, &max_value);

    // read pixels into buffer
    fread(buffer, sizeof(int), width*height, input_file);

    output_file = fopen(output_filename, "wb");
    if (output_file == NULL) {
        printf("Error opening output file.\n");
        return 1;
    }

    // write PGM header for output file
    fprintf(output_file, "P5\n%d %d\n%d\n", new_width, new_height, max_value);

    // resize image using average of pixels
    for (int j = 0; j < new_height; j++) {
        for (int i = 0; i < new_width; i++) {
            int x = ((i*x_ratio)>>16);
            int y = ((j*y_ratio)>>16);
            int sum = 0;
            int count = 0;

            for (int jj = 0; jj < y_ratio; jj++) {
                for (int ii = 0; ii < x_ratio; ii++) {
                    int pixel = buffer[(y+jj)*width + (x+ii)];
                    sum += pixel;
                    count++;
                }
            }

            int average = (int) (1.0 * sum / count);
            output_buffer[j*new_width+i] = (unsigned char) average;
        }
    }

    // write output buffer to file
    fwrite(output_buffer, sizeof(unsigned char), new_width*new_height, output_file);

    fclose(input_file);
    fclose(output_file);
    free(buffer);
    free(output_buffer);

    return 0;
}
