#include "decc_code.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TOTAL_LEN (DECC_BUF_LEN + CONTROL_SUM_LEN)


// Function to introduce an error in one bit
void introduce_one_bit_error(uint8_t *data, int bit_pos)
{
    int byte_pos = bit_pos / 8;
    int bit_offset = bit_pos % 8;
    if (byte_pos < DECC_BUF_LEN)
    {
        data[byte_pos] ^= (1 << bit_offset); // Flip the specified bit
    }
}

// Function to print data in bit format
void print_bits(const uint8_t *data, size_t length)
{
    for (size_t i = 0; i < length; i++) {
        for (int j = 7; j >= 0; j--) {
            printf("%d", (data[i] >> j) & 1);
        }
        printf(" ");
    }
    printf("\n");
}

// Function to test the algorithm with one error
void test_algorithm_with_one_error(int bit_pos) {
    clock_t start, end;
    double elapsed;

    uint8_t test_data[TOTAL_LEN];

    for (int j = 0; j < DECC_BUF_LEN; j++) {
        test_data[j] = rand() % 256;
    }
    uint16_t sum = DECC_calculate_sum(test_data, DECC_BUF_LEN);
    *((uint16_t *)(test_data + DECC_BUF_LEN)) = sum;

    // Print original data
    printf("Data before error:\n");
    print_bits(test_data, TOTAL_LEN);

    uint8_t test_data_with_error[TOTAL_LEN];
    memcpy(test_data_with_error, test_data, TOTAL_LEN);

    introduce_one_bit_error(test_data_with_error, bit_pos);

    // Print data with error
    printf("Data with error in bit %d:\n", bit_pos);
    print_bits(test_data_with_error, TOTAL_LEN);

    start = clock();
    int result = DECC_check_data_updated(test_data_with_error, TOTAL_LEN);
    end = clock();

    elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    if (result == 0) {
        printf("DECC: Data with error in bit %d is correct\n", bit_pos);
    } else if (result == 1) {
        printf("DECC: Data with error in bit %d was corrected\n", bit_pos);
    } else {
        printf("DECC: Data with error in bit %d was not corrected\n", bit_pos);
    }
    printf("DECC: Execution time for error in bit %d: %f seconds\n", bit_pos, elapsed);
}

int main(int argc, char *argv[]) {
    int bit_pos;

    srand(time(NULL));

    if (argc == 2) {
        bit_pos = atoi(argv[1]);
        if (bit_pos < 0 || bit_pos >= DECC_BUF_LEN * 8) {
            fprintf(stderr, "Error: Bit position must be between 0 and %d\n", DECC_BUF_LEN * 8 - 1);
            return 1;
        }
    } else {
        bit_pos = rand() % (DECC_BUF_LEN * 8);
    }

    // Testing the updated algorithm
    test_algorithm_with_one_error(bit_pos);

    return 0;
}
