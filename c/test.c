#include <stdio.h>

#include "fann.h"

int max(float a[]) {
    int res = 0;
    for (int i = 1; i < 4; i++)
        if (a[i] > a[res])
            res = i;
    return res;
}

int main(int argc, char *argv[]) {

    struct fann *ann = fann_create_from_file(argv[1]);
    struct fann_train_data *test_data = fann_read_train_from_file(argv[2]);

    int ans = 0;
    fann_reset_MSE(ann);
    for (int i = 0; i < fann_length_train_data(test_data); i++) {
        fann_type *calc_out = fann_run(ann, test_data->input[i]);
        fann_test(ann, test_data->input[i], test_data->output[i]);
        //printf("pred: %f %f %f %f\n", calc_out[0], calc_out[1], calc_out[2], calc_out[3]);
        //printf("true: %f %f %f %f\n", test_data->output[i][0], test_data->output[i][1], test_data->output[i][2], test_data->output[i][3]);
        if (test_data->output[i][max(calc_out)])
            ans++;
    }

    printf("MSE error on test data: %f\n", fann_get_MSE(ann));
    printf("bit fail on test data: %u\n", fann_get_bit_fail(ann));
    printf("%d %lf\n", ans, (double)ans / fann_length_train_data(test_data));

    // fann_destroy_train(test_data);
    // fann_destroy(ann);

    return 0;
}
