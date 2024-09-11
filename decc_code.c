#include "decc_code.h"
#include <stddef.h>

// Function to count the number of set bits
static int get_num_set_bits(const uint8_t d)
{
    int count = 0;
    for(size_t i = 0; i < 8; i++)
    {
        if(d & (1 << i))
        {
            count++;
        }
    }
    return count;
}

// Function to get the position of the first set bit
static int get_num_of_first_set_bit(const uint8_t d)
{
    for(size_t i = 0; i < 8; i++)
    {
        if(d & (1 << i))
        {
            return i;
        }
    }
    return -1;
}

// Function to calculate the checksum
uint16_t DECC_calculate_sum(const uint8_t *data, size_t length)
{
    if (data == NULL || length < DECC_BUF_LEN)
    {
        return 0; // Error: Invalid data pointer or length
    }

    uint8_t x = 0;
    uint8_t y = 0;

    for(size_t i = 0; i < DECC_BUF_LEN; i++)
    {
        x ^= data[i];
        y |= (((get_num_set_bits(data[i])) & 1) ? (1 << i) : 0);
    }
    return (uint16_t)((x << 8) | y);
}

// Improved data checking and correction algorithm
int DECC_check_data_updated(uint8_t *data, size_t length)
{
    if (data == NULL || length < DECC_BUF_LEN + CONTROL_SUM_LEN) {
        return -1; // Error: Invalid data pointer or length
    }

    const uint16_t received_sum = *(uint16_t*)(&data[DECC_BUF_LEN]);
    const uint16_t calculated_sum = DECC_calculate_sum(data, DECC_BUF_LEN);
    const uint8_t x = (uint8_t)((received_sum ^ calculated_sum) >> 8);
    const uint8_t y = (uint8_t)((received_sum ^ calculated_sum) & 0xFF);

    if(x == 0 && y == 0)
    {
        return 0;
    }

    if (get_num_set_bits(x) == 1 && get_num_set_bits(y) == 1)
    {
        int bit_pos = get_num_of_first_set_bit(y);
        if (bit_pos >= 0 && bit_pos < DECC_BUF_LEN)
        {
            data[bit_pos] ^= x;
            return 1;
        }
    }

    return -1;
}
