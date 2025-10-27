#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hideMessage(FILE *img, FILE *out, const char *message) {
    int ch, i = 0, bit;
    int msgLen = strlen(message) + 1; // +1 for null terminator
    int totalBits = msgLen * 8;

    while ((ch = fgetc(img)) != EOF && i < totalBits) {
        bit = (message[i / 8] >> (7 - (i % 8))) & 1;
        ch = (ch & 0xFE) | bit;
        fputc(ch, out);
        i++;
    }

    // Copy the remaining image data
    while ((ch = fgetc(img)) != EOF) {
        fputc(ch, out);
    }
}

int main() {
    FILE *img = fopen("input.bmp", "rb");
    FILE *out = fopen("output.bmp", "wb");
    const char *secret = "There is a murder";

    if (!img || !out) {
        printf("File error.\n");
        return 1;
    }

    // Copy BMP header (first 54 bytes)
    for (int i = 0; i < 54; i++) {
        fputc(fgetc(img), out);
    }

    hideMessage(img, out, secret);

    fclose(img);
    fclose(out);

    printf("Message hidden successfully!\n");
    return 0;
}
