#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

// prototypes
void oct_to_bin(const char *oct, char *out);
void oct_to_hex(const char *oct, char *out);
void hex_to_bin(const char *hex, char *out);
void to_sign_magnitude(int32_t n, char *out);
void to_ones_complement(int32_t n, char *out);
void to_twos_complement(int32_t n, char *out);

typedef struct {
    char function_name[50];
    char input[100];
    char expected[200];
} TestCase;

int main() {
    FILE *f = fopen("a2_test.txt", "r");
    if (!f) {
        perror("a2_test.txt");
        return 1;
    }

    char line[300];
    char actual[300];
    int test_num = 0, passed = 0;

    while (fgets(line, sizeof(line), f)) {
        if (line[0] == '#' || strlen(line) < 2) continue;

        TestCase t;
        int count = sscanf(line, "%s %s %s", t.function_name, t.input, t.expected);
        if (count < 3) continue;

        test_num++;
        actual[0] = '\0';

        if (strcmp(t.function_name, "oct_to_bin") == 0) {
            oct_to_bin(t.input, actual);
        } else if (strcmp(t.function_name, "oct_to_hex") == 0) {
            oct_to_hex(t.input, actual);
        } else if (strcmp(t.function_name, "hex_to_bin") == 0) {
            hex_to_bin(t.input, actual);
        } else if (strcmp(t.function_name, "to_sign_magnitude") == 0) {
            int32_t n = atoi(t.input);
            to_sign_magnitude(n, actual);
        } else if (strcmp(t.function_name, "to_ones_complement") == 0) {
            int32_t n = atoi(t.input);
            to_ones_complement(n, actual);
        } else if (strcmp(t.function_name, "to_twos_complement") == 0) {
            int32_t n = atoi(t.input);
            to_twos_complement(n, actual);
        }

        int ok = strcmp(actual, t.expected) == 0;
        printf("Test %d: %s(\"%s\") -> Expected: \"%s\", Got: \"%s\" [%s]\n",
               test_num, t.function_name, t.input, t.expected, actual,
               ok ? "PASS" : "FAIL");
        if (ok) passed++;
    }

    printf("Summary: %d/%d tests passed\n", passed, test_num);
    fclose(f);
    return 0;
}
