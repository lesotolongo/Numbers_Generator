/******************************************************************************
 * File: random_generator.c
 * -Compile: gcc -o random_generator random_generator.c -lm
 * -OR
 * -Compile using makefile
 * -Execute: ./ass1
 *
 * Purpose:
 *This program demonstrates the generation of random numbers using both uniform
 * and normal distributions, including support for:
 * Features:
 * - Generates random numbers to meet criteria for each given scenario. 
 * - Creates and stores .txt files generated into data folder for each scenario.  
******************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

#define frand() (rand() / (double)RAND_MAX)
#define nrand() (sqrt(-2 * log(frand())) * cos(2 * M_PI * frand()))

void generate_uniform_integers(const char *filename, int min, int max, int count);
void generate_uniform_reals(const char *filename, double min, double max, int count);
void generate_normal_integers(const char *filename, double mean, double stddev, int count);
void generate_normal_reals(const char *filename, double mean, double stddev, int count);
void generate_truncated_normal_integers(const char *filename, double mean, double stddev, int min, int max, int count);
void generate_truncated_normal_reals(const char *filename, double mean, double stddev, double min, double max, int count);
void create_directory(const char *path);

int main() {
    srand(time(NULL));

    struct Scenario {
        double mean, stddev;
        int min, max, sample_size;
        char label[20];
    } scenarios[] = {
        {5, 1, 1, 8, 20, "Scenario_1"},
        {1024, 256, 1, 2000, 200000, "Scenario_2"},
        {4096, 1331, 1, 8100, 2000000, "Scenario_3"}
    };

    const char *directory = "DATA";
    create_directory(directory);

    for (int i = 0; i < 3; i++) {
        char path[50];
        snprintf(path, sizeof(path), "%s/%s", directory, scenarios[i].label);
        create_directory(path);

        char filename[100];

        snprintf(filename, sizeof(filename), "%s/uniform_integers.txt", path);
        generate_uniform_integers(filename, scenarios[i].min, scenarios[i].max, scenarios[i].sample_size);

        snprintf(filename, sizeof(filename), "%s/uniform_reals.txt", path);
        generate_uniform_reals(filename, scenarios[i].min, scenarios[i].max, scenarios[i].sample_size);

        snprintf(filename, sizeof(filename), "%s/normal_integers.txt", path);
        generate_normal_integers(filename, scenarios[i].mean, scenarios[i].stddev, scenarios[i].sample_size);

        snprintf(filename, sizeof(filename), "%s/normal_reals.txt", path);
        generate_normal_reals(filename, scenarios[i].mean, scenarios[i].stddev, scenarios[i].sample_size);

        snprintf(filename, sizeof(filename), "%s/truncated_normal_integers.txt", path);
        generate_truncated_normal_integers(filename, scenarios[i].mean, scenarios[i].stddev, scenarios[i].min, scenarios[i].max, scenarios[i].sample_size);

        snprintf(filename, sizeof(filename), "%s/truncated_normal_reals.txt", path);
        generate_truncated_normal_reals(filename, scenarios[i].mean, scenarios[i].stddev, scenarios[i].min, scenarios[i].max, scenarios[i].sample_size);
    }

    printf("Random number sequences generated and saved in '%s' directory.\n", directory);
    return 0;
}

void create_directory(const char *path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        mkdir(path, 0700);
    }
}

void generate_uniform_integers(const char *filename, int min, int max, int count) {
    FILE *file = fopen(filename, "w");
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d\n", rand() % (max - min + 1) + min);
    }
    fclose(file);
}

void generate_uniform_reals(const char *filename, double min, double max, int count) {
    FILE *file = fopen(filename, "w");
    for (int i = 0; i < count; i++) {
        fprintf(file, "%lf\n", frand() * (max - min) + min);
    }
    fclose(file);
}

void generate_normal_integers(const char *filename, double mean, double stddev, int count) {
    FILE *file = fopen(filename, "w");
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d\n", (int)(nrand() * stddev + mean));
    }
    fclose(file);
}

void generate_normal_reals(const char *filename, double mean, double stddev, int count) {
    FILE *file = fopen(filename, "w");
    for (int i = 0; i < count; i++) {
        fprintf(file, "%lf\n", nrand() * stddev + mean);
    }
    fclose(file);
}

void generate_truncated_normal_integers(const char *filename, double mean, double stddev, int min, int max, int count) {
    FILE *file = fopen(filename, "w");
    for (int i = 0; i < count; i++) {
        int value;
        do {
            value = (int)(nrand() * stddev + mean);
        } while (value < min || value > max);
        fprintf(file, "%d\n", value);
    }
    fclose(file);
}

void generate_truncated_normal_reals(const char *filename, double mean, double stddev, double min, double max, int count) {
    FILE *file = fopen(filename, "w");
    for (int i = 0; i < count; i++) {
        double value;
        do {
            value = nrand() * stddev + mean;
        } while (value < min || value > max);
        fprintf(file, "%lf\n", value);
    }
    fclose(file);
}
