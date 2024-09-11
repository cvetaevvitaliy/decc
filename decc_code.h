#ifndef DECC_CODE_H
#define DECC_CODE_H

#include <stdint.h>
#include <stddef.h>

#define DECC_BUF_LEN 8 // Length of data (64 bits)
#define CONTROL_SUM_LEN sizeof(uint16_t)

// Function prototypes
uint16_t DECC_calculate_sum(const uint8_t *data, size_t length);
int DECC_check_data_updated(uint8_t *data, size_t length);

#endif // DECC_CODE_H
