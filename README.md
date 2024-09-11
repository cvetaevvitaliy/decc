# Data Error Checking and Correction (DECC)

## Overview

This project implements a Data Error Checking and Correction (DECC) algorithm to detect and correct single-bit errors in a block of data.

## Files

- `decc_code.c`: Contains the implementation of the DECC algorithm.
- `decc_code.h`: Header file with function declarations for the DECC algorithm.
- `main.c`: Contains the `main` function for testing the DECC algorithm with a single-bit error.

## Building

To build the project, use the provided `Makefile`. Run the following command in the terminal:

```bash
make
```

This will generate an executable named `decc_test_program`.


### Running

To run the program, execute the following command:

```bash
./decc_test_program
```
or
```bash 
./decc_test_program 5
```
This command will introduce an error in bit position 5 of the data and test the error correction.

example output:
```bash 
Data before error:
11100010 01000111 01001010 01100101 11100010 10101100 01101101 11100010 01000100 01001011 
Data with error in bit 5:
11000010 01000111 01001010 01100101 11100010 10101100 01101101 11100010 01000100 01001011 
DECC: Data with error in bit 5 was corrected
DECC: Execution time for error in bit 5: 0.000004 seconds
```

### License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.