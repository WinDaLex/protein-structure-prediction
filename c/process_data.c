#include <stdio.h> 
#include <string.h>

const char BASIC_AMINO_ACIDS[20] = {
        'A', 'R', 'N', 'D', 'C', 'E', 'Q', 'G', 'H', 'I', 'L', 'K', 'M', 'F',
        'P', 'S', 'T', 'W', 'Y', 'V'};
const char HETC[4] = {'H', 'E', 'T', 'C'};

const int MAX_INPUT_LENGTH = 100002;

int main(int argc, char *argv[]) {
    if (argc < 5) {
        fprintf(stderr, "usage: %s source target window_size num_examples\n", argv[0]);
        return 1;
    }

    const char *source = argv[1];
    const char *target = argv[2];
    unsigned int window_size;
    if (sscanf(argv[3], "%u", &window_size) != 1) {
        fprintf(stderr, "error: argument window_size should be a unsigned integer\n");
        return 2;
    } else if (window_size <= 0 || window_size % 2 == 0) {
        fprintf(stderr, "error: argument window_size should be odd positive number\n");
        return 2;
    }

    int num_examples = -1;
    if ((sscanf(argv[4], "%d", &num_examples) != 1) || num_examples <= 0) {
        fprintf(stderr, "num_examples should not be positive integer\n");
        return 3;
    }


    FILE *source_file = fopen(source, "r");
    if (!source_file) {
        fprintf(stderr, "Cannot access the file '%s'\n", source);
        return 3;
    }

    char primary[MAX_INPUT_LENGTH], hetc[MAX_INPUT_LENGTH];

    FILE *target_file = fopen(target, "w");
    fprintf(target_file, "%d %d %d\n", num_examples, window_size * 20, 4);

    fscanf(source_file, "%*s %*s %*s");
    while (fscanf(source_file, "%*s %*s %s %s", primary, hetc) != EOF && num_examples--) {
        size_t len = strlen(primary);
        for (int i = 1; i < len - 1; i++) {
            for (int j = i - (int)window_size / 2; j <= i + (int)window_size / 2; j++) {
                for (int k = 0; k < 20; k++) {
                    fputc(primary[j < 1 || j >= len - 1 ? 0 : j] == BASIC_AMINO_ACIDS[k] ? '1' : '0', target_file);
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

    return 0;
}
