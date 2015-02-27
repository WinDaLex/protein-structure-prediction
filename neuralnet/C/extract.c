/*
 * extract.c: Extract data from source file to target file according to
 * window_size and num_examples.
 */

#include <stdio.h> 
#include <string.h>

const char BASIC_AMINO_ACIDS[20] = {
        'A', 'R', 'N', 'D', 'C', 'E', 'Q', 'G', 'H', 'I', 'L', 'K', 'M', 'F',
        'P', 'S', 'T', 'W', 'Y', 'V'
};
const char HETC[4] = {'H', 'E', 'T', 'C'};

const int MAX_INPUT_LENGTH = 100002;

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "usage: %s source target window_size [num_examples]\n", argv[0]);
        return -1;
    }

    const char *source = argv[1];
    const char *target = argv[2];

    int window_size;
    sscanf(argv[3], "%d", &window_size);

    int num_examples = -1;
    if (argc >= 4) sscanf(argv[4], "%d", &num_examples);

    FILE *source_file = fopen(source, "r");
    if (!source_file) {
        fprintf(stderr, "Cannot access the file '%s'\n", source);
        return -2;
    }

    puts("Extracting data...");

    FILE *target_file = fopen(target, "w");
    fprintf(target_file, "? %d %d\n", window_size * 20, 4);

    char primary[MAX_INPUT_LENGTH], hetc[MAX_INPUT_LENGTH];
    fscanf(source_file, "%*s %*s %*s");
    while (fscanf(source_file, "%*s %*s %s %s", primary, hetc) != EOF && num_examples--) {
        size_t len = strlen(primary);
        for (int i = 1; i < len - 1; i++) {

            for (int j = i - window_size / 2; j <= i + window_size / 2; j++) {
                for (int k = 0; k < 20; k++) {
                    int pos = j < 1 || j >= len - 1 ? 0 : j;
                    fputc(primary[pos] == BASIC_AMINO_ACIDS[k] ? '1' : '0', target_file);
                    fputc(' ', target_file);
                }
            }
            fputc('\n', target_file);

            for (int j = 0; j < 4; j++) {
                fputc(hetc[i] == HETC[j] ? '1' : '0', target_file);
                fputc(' ', target_file);
            }
            fputc('\n', target_file);
        }
    }

    fclose(source_file);
    fclose(target_file);

    puts("Done! Do not forget to change the num_examples in the file!");

    return 0;
}
