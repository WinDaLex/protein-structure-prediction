/*
 * test.c: Testing program
 */

#include <stdio.h>

#include "fann.h"

inline int check(float predicted[4], float desired[4], int ignore_ct);

inline void process_bar(int x, int n, int r);

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "usage: %s network data\n", argv[0]);
        return -1;
    }

    printf("Loading file...\n");

    struct fann *ann = fann_create_from_file(argv[1]);
    struct fann_train_data *test_data = fann_read_train_from_file(argv[2]);

    printf("Testing...\n");

    fann_reset_MSE(ann);
    int num_correct = 0, ratio = 0, length_data = fann_length_train_data(test_data);
    for (int i = 0; i < length_data; i++) {
        fann_type *calc_out = fann_run(ann, test_data->input[i]);
        fann_test(ann, test_data->input[i], test_data->output[i]);
        num_correct += check(calc_out, test_data->output[i], 0) ? 1 : 0;

        printf("Accuracy: %d / %d = %5.1f%%\t", num_correct, i, (double)num_correct / i * 100);
        process_bar(i, length_data / 100, 20);
    }

    printf("Accuracy: %d / %d = %5.1f%%\n", num_correct, length_data, (double)num_correct / length_data * 100);
    printf("MSE error on test data: %f\n", fann_get_MSE(ann));
    printf("bit fail on test data: %u\n", fann_get_bit_fail(ann));

    fann_destroy_train(test_data);
    fann_destroy(ann);

    puts("Done!");

    return 0;
}

int check(float predicted[4], float desired[4], int ignore_ct) {
    int max = 0;
    for (int i = 1; i < 4; i++)
        if (predicted[i] > predicted[max])
            max = i;
    if (ignore_ct && max >= 2) return desired[2] || desired[3];
    return desired[max];
}

void process_bar(int x, int n, int r) {
    int ratio = x / n;
    printf("Progress: %3d%%[", ratio);
    for (int i = 0; i < r; i++) putchar(i < ratio / (100 / r) ? '=' : ' ');
    printf("]\n\033[F\033[J");
}
