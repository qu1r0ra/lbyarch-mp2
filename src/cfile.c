#include <stdio.h>
#include <stdlib.h>

int read_int(const char *prompt);
float read_float(const char *prompt);
void *safe_malloc(size_t size);
void print_img_int_rep(int imgHeight, int imgWidth, int *imgIntRep);

extern void imgCvtGrayFloatToInt(int imgHeight, int imgWidth, float *imgFloatRep, int *imgIntRep);

int main() {
    int imgHeight = read_int("Enter the image's height: ");
    int imgWidth = read_int("Enter the image's width: ");
    printf("\n");

    float *imgFloatRep = safe_malloc(imgHeight * imgWidth * sizeof(float));
    int *imgIntRep = safe_malloc(imgHeight * imgWidth * sizeof(int));

    imgCvtGrayFloatToInt(imgHeight, imgWidth, imgFloatRep, imgIntRep);
    print_img_int_rep(imgHeight, imgWidth, imgIntRep);
    return 0;
}

int read_int(const char *prompt) {
    int n;
    printf("%s", prompt);
    scanf("%d", &n);
    return n;
}

float read_float(const char *prompt) {
    float n;
    printf("%s", prompt);
    scanf("%f", &n);
    return n;
}

void *safe_malloc(size_t size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void print_img_int_rep(int imgHeight, int imgWidth, int *imgIntRep) {
    printf("Image's integer representation:\n");
    for (int i = 0; i < imgHeight; i++) {
        for (int j = 0; j < imgWidth; j++) {
            printf("%d ", imgIntRep[i * imgWidth + j]);
        }
        printf("\n");
    }
}