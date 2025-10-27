#include <stdio.h>
#include <stdlib.h>

void extractMessage(FILE *img) {
    int ch, i = 0;
    char character = 0;

    // Skip the first 54 bytes (BMP header)
    for (int j = 0; j < 54; j++) {
        fgetc(img);
    }

    while (1) {
        ch = fgetc(img);
        if (ch == EOF) break;

        // Shift left and add current LSB
        character = character << 1;
        character |= (ch & 1);
        i++;

        // Every 8 bits = 1 character
        if (i % 8 == 0) {
            if (character == '\0') {
                break; // Null terminator = end of message
            }
            printf("%c", character);
            character = 0;
        }
    }

    printf("\n");
}

int main() {
    char filename[50];
    printf("Enter the file name:");
    scanf("%s",&filename);
    FILE *img = fopen(filename, "rb");

    if (!img) {
        printf("File error. Could not open output.bmp\n");
        return 1;
    }

    printf("Hidden message: ");
    extractMessage(img);
    fclose(img);
    return 0;
}

