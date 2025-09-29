#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>   // for toupper
#include <stdlib.h>  // for abs

// Division Method 
void div_convert(uint32_t n, int base, char *out) {
    char temp[65];
    int pos = 0;

    if (n == 0) {
        strcpy(out, "0");
        return;
    }

    while (n > 0) {
        int remainder = n % base;
        n /= base;
        temp[pos++] = (remainder < 10) ? ('0' + remainder) : ('A' + remainder - 10);
    }

    // Reverse the result
    for (int i = 0; i < pos; i++) {
        out[i] = temp[pos - i - 1];
    }
    out[pos] = '\0';
}

// Subtraction Method
void sub_convert(uint32_t n, int base, char *out) {
    char temp[65];
    int pos = 0;

    if (n == 0) {
        strcpy(out, "0");
        return;
    }

    uint32_t power = 1;
    while (power <= n / base) power *= base;

    while (power > 0) {
        int digit = n / power;
        temp[pos++] = (digit < 10) ? ('0' + digit) : ('A' + digit - 10);
        n -= digit * power;
        power /= base;
    }

    temp[pos] = '\0';
    strcpy(out, temp);
}

//Print Bit Manipulation Tables 
void print_tables(uint32_t n) {
    char bin[65], oct[65], hex[65];

    // Original
    div_convert(n, 2, bin);
    div_convert(n, 8, oct);
    div_convert(n, 16, hex);
    printf("Original: Binary=%s Octal=%s Decimal=%u Hex=%s\n", bin, oct, n, hex);

    // Left shift by 3
    uint32_t shifted = n << 3;
    div_convert(shifted, 2, bin);
    div_convert(shifted, 8, oct);
    div_convert(shifted, 16, hex);
    printf("Left Shift by 3: Binary=%s Octal=%s Decimal=%u Hex=%s\n", bin, oct, shifted, hex);

    // AND with 0xFF
    uint32_t masked = n & 0xFF;
    div_convert(masked, 2, bin);
    div_convert(masked, 8, oct);
    div_convert(masked, 16, hex);
    printf("AND with 0xFF: Binary=%s Octal=%s Decimal=%u Hex=%s\n", bin, oct, masked, hex);




}
void oct_to_bin(const char *oct, char *out) {
    int pos = 0;
    for (int i = 0; oct[i] != '\0'; i++) {
        int digit = oct[i] - '0';
        out[pos++] = (digit & 4) ? '1' : '0';
        out[pos++] = (digit & 2) ? '1' : '0';
        out[pos++] = (digit & 1) ? '1' : '0';
    }
    out[pos] = '\0';
}

// oct to hex
void oct_to_hex(const char *oct, char *out) {
    char bin[256];
    oct_to_bin(oct, bin);

    int len = strlen(bin);
    int pad = (4 - (len % 4)) % 4;
    char padded[260];
    for (int i = 0; i < pad; i++) padded[i] = '0';
    strcpy(padded + pad, bin);

    int pos = 0;
    for (int i = 0; i < pad + len; i += 4) {
        int val = 0;
        for (int j = 0; j < 4; j++) {
            val = (val << 1) | (padded[i + j] - '0');
        }
        out[pos++] = (val < 10) ? '0' + val : 'A' + val - 10;
    }
    out[pos] = '\0';
     
    int start = 0;
    while (out[start] == '0' && out[start+1] != '\0') start++;
    if (start > 0) memmove(out, out + start, strlen(out + start) + 1);
}

// hex to bin
void hex_to_bin(const char *hex, char *out) {
    int pos = 0;
    for (int i = 0; hex[i] != '\0'; i++) {
        char c = toupper(hex[i]);
        int val;
        if (c >= '0' && c <= '9') val = c - '0';
        else if (c >= 'A' && c <= 'F') val = 10 + (c - 'A');
        else continue;
        out[pos++] = (val & 8) ? '1' : '0';
        out[pos++] = (val & 4) ? '1' : '0';
        out[pos++] = (val & 2) ? '1' : '0';
        out[pos++] = (val & 1) ? '1' : '0';
    }
    out[pos] = '\0';
}

// 32-bit binary string
static void to_32bit_binary(uint32_t value, char *out) {
    for (int i = 31; i >= 0; i--) {
        out[31 - i] = ((value >> i) & 1) ? '1' : '0';
    }
    out[32] = '\0';
}

// to sign magnitude
void to_sign_magnitude(int32_t n, char *out) {
    if (n >= 0) {
        to_32bit_binary((uint32_t)n, out);
    } else {
        uint32_t mag = (uint32_t)abs(n);
        to_32bit_binary(mag, out);
        out[0] = '1';
    }
}

//  to_ones_complement
void to_ones_complement(int32_t n, char *out) {
    if (n >= 0) {
        to_32bit_binary((uint32_t)n, out);
    } else {
        uint32_t val = (uint32_t)(-n);
        char temp[33];
        to_32bit_binary(val, temp);
        for (int i = 0; i < 32; i++) {
            out[i] = (temp[i] == '0') ? '1' : '0';
        }
        out[32] = '\0';
    }
}

// to_twos_complement
void to_twos_complement(int32_t n, char *out) {
    uint32_t val = (uint32_t)n;
    to_32bit_binary(val, out);
}
