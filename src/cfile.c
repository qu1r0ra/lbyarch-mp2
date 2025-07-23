#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void run_performance_test_mode();
void *safer_malloc(size_t size);
void randomize_img_float_rep(int imgHeight, int imgWidth, float *imgFloatRep);
void run_manual_input_mode();
int read_int(const char *prompt);
void read_img_float_rep(int imgHeight, int imgWidth, float *imgFloatRep);
float read_float(const char *prompt);
void print_img_float_rep(int imgHeight, int imgWidth, float *imgFloatRep);
void print_img_int_rep(int imgHeight, int imgWidth, int *imgIntRep);

extern void imgCvtGrayFloatToInt(int imgHeight, int imgWidth, float *imgFloatRep, int *imgIntRep);

int main() {
    srand(time(NULL));
    
    int choice;
    printf("Modes:\n");
    printf("1. Performance test\n");
    printf("2. Manual input\n\n");
    printf("Select a mode (1 or 2): ");
    scanf("%d", &choice);
    printf("\n");

    if (choice == 1) {
        run_performance_test_mode();
    } else if (choice == 2) {
        run_manual_input_mode();
    } else {
        printf("Invalid choice\n");
        return 1;
    }
    return 0;
}

void run_performance_test_mode() {
    const int sizes[] = {10, 100, 1000};
    const int numSizes = sizeof(sizes) / sizeof(sizes[0]);
    const int numRuns = 30;

    for (int i = 0; i < numSizes; i++) {
        int imgHeight = sizes[i];
        int imgWidth = sizes[i];
        double total_seconds_elapsed = 0.0;

        float *imgFloatRep = safer_malloc(imgHeight * imgWidth * sizeof(float));
        int *imgIntRep = safer_malloc(imgHeight * imgWidth * sizeof(int));

        for (int run = 0; run < numRuns; run++) {
            randomize_img_float_rep(imgHeight, imgWidth, imgFloatRep);

            clock_t start = clock();
            imgCvtGrayFloatToInt(imgHeight, imgWidth, imgFloatRep, imgIntRep);
            clock_t end = clock();
            double seconds_elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
            total_seconds_elapsed += seconds_elapsed;
        }
        
        free(imgFloatRep);
        free(imgIntRep);

        double avg_seconds_elapsed = total_seconds_elapsed / numRuns;
        printf("Average time taken to convert a %d x %d image over %d runs: ", imgHeight, imgWidth, numRuns);
        printf("\033[1;32m%f seconds\033[0m\n\n", avg_seconds_elapsed);
    }

    return;
}

void *safer_malloc(size_t size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void randomize_img_float_rep(int imgHeight, int imgWidth, float *imgFloatRep) {
    for (int i = 0; i < imgHeight * imgWidth; i++) {
        imgFloatRep[i] = (float)rand() / RAND_MAX;
    }
}

void run_manual_input_mode() {
    int imgHeight = read_int("Enter the image's height: ");
    int imgWidth = read_int("Enter the image's width: ");
    printf("\n");

    float *imgFloatRep = safer_malloc(imgHeight * imgWidth * sizeof(float));
    int *imgIntRep = safer_malloc(imgHeight * imgWidth * sizeof(int));

    read_img_float_rep(imgHeight, imgWidth, imgFloatRep);
    print_img_float_rep(imgHeight, imgWidth, imgFloatRep);

    imgCvtGrayFloatToInt(imgHeight, imgWidth, imgFloatRep, imgIntRep);
    print_img_int_rep(imgHeight, imgWidth, imgIntRep);

    free(imgFloatRep);
    free(imgIntRep);

    return;
}

int read_int(const char *prompt) {
    int n;
    printf("%s", prompt);
    scanf("%d", &n);
    return n;
}

void read_img_float_rep(int imgHeight, int imgWidth, float *imgFloatRep) {
    for (int i = 0; i < imgHeight; i++) {
        for (int j = 0; j < imgWidth; j++) {
            char prompt[100];
            sprintf(prompt, "Enter the value of the pixel at row %d and column %d: ", i, j);
            imgFloatRep[i * imgWidth + j] = read_float(prompt);
            printf("\n");
        }
    }
}

float read_float(const char *prompt) {
    float n;
    printf("%s", prompt);
    scanf("%f", &n);
    return n;
}

void print_img_float_rep(int imgHeight, int imgWidth, float *imgFloatRep) {
    printf("Image's float representation:\n");
    for (int i = 0; i < imgHeight; i++) {
        for (int j = 0; j < imgWidth; j++) {
            printf("%f ", imgFloatRep[i * imgWidth + j]);
        }
        printf("\n");
    }
    printf("\n");
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