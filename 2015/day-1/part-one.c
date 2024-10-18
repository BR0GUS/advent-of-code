#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int figure_out_first_character_occurence(const char[], const char);
char* read_input_from_file(const char*);

int main(void) {
        char *input;
        input = read_input_from_file("input");
        int santa_floor = figure_out_first_character_occurence(input, ')');
        printf("%d", santa_floor);
        free(input);
        return 0;
}

char* read_input_from_file(const char* file_name) {
        FILE *file = fopen(file_name, "r");
        if (file == NULL) {
                perror("Error opening file");
                return NULL;
        }

        size_t buffer_size = 1024;
        char* buffer = malloc(buffer_size);
        if (buffer == NULL) {
                fclose(file);
                return NULL;
        }

        size_t total_read = 0;
        size_t bytes_read;

        while (1) {
                bytes_read = fread(buffer + total_read, 1, buffer_size - total_read, file);
                if (bytes_read == 0) {
                        break;
                }

                total_read += bytes_read;
                if (total_read == buffer_size) {
                        buffer_size *= 2;
                        char* new_buffer = realloc(buffer, buffer_size);
                        if (new_buffer == NULL) {
                                free(buffer);
                                fclose(file);
                                return NULL;
                        }

                        buffer = new_buffer;
                }
        }

        buffer[total_read] = '\0';
        fclose(file);
        return buffer;

}

int figure_out_first_character_occurence(const char input[], const char character) {
        size_t input_length = strlen(input);

        int santa_floor = 0;
                
        for (int i = 0; i < input_length; i++) {
                switch (input[i]) {
                        case '(':
                                santa_floor++;
                                break;
                        case ')':
                                santa_floor--;
                                break;
                        default:
                                break;
                }
        }

        return santa_floor;
}

