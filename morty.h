#pragma once

#include <stdio.h>
#include <windows.h>

/**
 * Base input key for xor encryption.
 */
unsigned char xor_input_key[] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05
};


/**
 * Base print hex data.
 */
static inline void print_hex_data(const char *str, unsigned char *data, size_t size){
    printf("[*] unsigned char %s[]{", str);

    for(int i = 0; i < size; i++){
        if(i % 16 == 0){
            printf("\n\t");
        }

        if (i < size - 1) {
            printf("0x%0.2X, ", data[i]);
        }
    	else {
      	    printf("0x%0.2X ", data[i]);
        }
    }

    printf("\n};\n");
}

/**
 * Convert a string to an unsigned char* tab of ASCII reprensentation + XOR.
 */
static inline unsigned char* string_to_ascii(IN const char *str, IN unsigned char* pKey, IN size_t sKeySize){
    if(str == NULL || pKey == NULL)
        return NULL;

    size_t len = strlen(str);

    unsigned char* hex = (unsigned char*)malloc(len * sizeof(unsigned char));
    if(hex == NULL){
        printf("[!] Error allocating memory.\n");
        return NULL;
    }

    for(size_t i = 0, j = 0; i < len; i++, j++){
        if(j > sKeySize)
            j = 0;

        hex[i] = (unsigned char)(str[i] ^ pKey[j]);
    }

    return hex;
}