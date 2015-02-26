#include <stdio.h>

#include "fann.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s filename [target]\n", argv[0]);
        return 1;
    }

    const unsigned int num_layers = 3;
    const unsigned int num_neurons_hidden = 5;
    const float desired_error = (const float) 0.02; /* ? */
    struct fann *ann;
    struct fann_train_data *train_data, *test_data;
    
    puts("creating network...");
    train_data = fann_read_train_from_file(argv[1]);
    ann = fann_create_standard(num_layers, train_data->num_input, num_neurons_hidden, train_data->num_output);

    puts("training network...");
    fann_set_training_algorithm(ann, FANN_TRAIN_INCREMENTAL);
    //fann_set_learning_momentum(ann, 0.4f);

    fann_train_on_data(ann, train_data, 3000, 10, desired_error);

    if (argc == 3) fann_save(ann, argv[2]);
    else fann_save(ann, "result.net");

    puts("done!");

    //fann_destory_train(train_data);
    //fann_destory(ann);

    return 0;
}
