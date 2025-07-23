/******************************************************************************
 * File: analyze_data c.c
 * -Compile: gcc -o analyze_data analyze_data c.c -lm
 * -Execute: ./analyze_data c
 *
 * Purpose:
 * This program reads the data from the files created by 'random_generator c.c' to display it back on the console.
 *
 * Features:
 * Calculate mean and standard deviation from each scenario to display back on console. 
******************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define NUM_SCENARIOS 3
#define NUM_FILES 6

struct Stats {
    double mean;
    double stddev;
};

struct Scenario {
    char name[20];
    struct Stats stats[NUM_FILES];
};

void calculate_stats(const char *filename, struct Stats *result);
void print_results(struct Scenario scenarios[]);

int main() {
    struct Scenario scenarios[NUM_SCENARIOS] = {
        {"Scenario_1", {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}},
        {"Scenario_2", {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}},
        {"Scenario_3", {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}}
    };

    const char *file_names[NUM_FILES] = {
        "uniform_integers.txt",
        "uniform_reals.txt",
        "normal_integers.txt",
        "normal_reals.txt",
        "truncated_normal_integers.txt",
        "truncated_normal_reals.txt"
    };

    for (int i = 0; i < NUM_SCENARIOS; i++) {
        char dir_path[50];
        snprintf(dir_path, sizeof(dir_path), "DATA/%s", scenarios[i].name);

        for (int j = 0; j < NUM_FILES; j++) {
            char file_path[100];
            snprintf(file_path, sizeof(file_path), "%s/%s", dir_path, file_names[j]);

            calculate_stats(file_path, &scenarios[i].stats[j]);
        }
    }

    print_results(scenarios);
    return 0;
}

void calculate_stats(const char *filename, struct Stats *result) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open %s\n", filename);
        result->mean = 0;
        result->stddev = 0;
        return;
    }

    double sum = 0, sum_sq = 0, value;
    int count = 0;

    while (fscanf(file, "%lf", &value) == 1) {
        sum += value;
        sum_sq += value * value;
        count++;
    }
    fclose(file);

    if (count == 0) {
        result->mean = 0;
        result->stddev = 0;
        return;
    }

    result->mean = sum / count;
    result->stddev = sqrt((sum_sq / count) - (result->mean * result->mean));
}

void print_results(struct Scenario scenarios[]) {
    const char *labels[NUM_FILES] = {
        "Uniform Integers",
        "Uniform Real Numbers",
        "Normally Distributed Integers",
        "Normally Distributed Real Numbers",
        "Truncated Normal Integers",
        "Truncated Normal Real Numbers"
    };

    for (int i = 0; i < NUM_SCENARIOS; i++) {
        printf("\n--- %s ---\n", scenarios[i].name);
        for (int j = 0; j < NUM_FILES; j++) {
            printf("%-30s Mean: %.2lf, StdDev: %.2lf\n",
                   labels[j], scenarios[i].stats[j].mean, scenarios[i].stats[j].stddev);
        }
    }
}
