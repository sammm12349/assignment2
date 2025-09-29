CS 3503 - Assignment 2
This project implements six functions for converting numbers between octal, hexadecimal, and binary formats, as well it representing signed integers in different binary forms. The goal of this project to complete
all 60 test cases 
**oct_to_bin**  
Direct 3-bit octal to binary mapping.

- **oct_to_hex**  
  Converts octal to hexadecimal via binary conversion, removing leading zeros.

- **hex_to_bin**  
  Direct 4-bit hexadecimal to binary mapping.

- **to_sign_magnitude**  
  Converts signed integers into 32-bit sign-magnitude representation.

- **to_ones_complement**  
  Converts signed integers into 32-bit one's complement representation.

- **to_twos_complement**  
  Converts signed integers into 32-bit two's complement representation.

The program reads test cases from `A2_tests.txt`, executes them, and writes results to `output.txt`.

## Build Instructions
To compile the program fo mac:
enter: clang main.c convert.c -o assignment1_new
then enter ./assignment1_new
