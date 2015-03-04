/*
 * train a neural network model
 */

#include <stdio.h>

#include "fann.h"


int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s filename [target]\n", argv[0]);
        return -1;
    }

    const char *training_file = argv[1];
    const char *target_file = "a.net";
    if (argc >= 3) target_file = argv[2];

    const unsigned int num_layers = 3;
    const unsigned int num_neurons_hidden = 60;
    
    puts("Creating network...");

    struct fann_train_data *train_data = fann_read_train_from_file(training_file);
    struct fann *ann = fann_create_standard(num_layers, train_data->num_input, num_neurons_hidden, train_data->num_output);

    puts("Training network...");

    fann_set_training_algorithm(ann, FANN_TRAIN_INCREMENTAL);
    fann_set_learning_momentum(ann, 0.0f);

    const unsigned int max_epochs = 3000;
    const unsigned int epochs_between_reports = 10;
    const float desired_error = (const float) 0.02;

    fann_train_on_data(ann, train_data, max_epochs, epochs_between_reports, desired_error);

    fann_save(ann, target_file);

    puts("Done!");

    fann_destroy_train(train_data);
    fann_destroy(ann);

    return 0;
}
