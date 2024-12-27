/**
 * Author : Yekuuun
 * Github : https://github.com/Yekuuun
 * 
 * Notes : base demo usage.
 */

#include "morty.h"

/**
 * Recreate base string from obsfuscated string generated in gen.c
 */
LPSTR RecreateBaseString(IN PBYTE obfuscated, IN SIZE_T sObfuscatedSize, IN PBYTE pKey, IN SIZE_T sKeySize){
    LPSTR result = (LPSTR)malloc((sObfuscatedSize + 1)*sizeof(CHAR));
    if(result == NULL){
        printf("[!] Error allocating memory \n");
        return NULL;
    }

    for(size_t i = 0, j = 0; i < sObfuscatedSize; i++, j++){
        if(j > sKeySize){
            j = 0;
        }

        result[i] = (CHAR)(obfuscated[i] ^ pKey[j]);
    }

    result[sObfuscatedSize] = '\0';
    return result;
}

//DEMO.
int main(int argc, char *argv[]){
    if(argc != 2){
        printf("[!] Error : must use one argument => <str_to_obfuscate> \n");
        return EXIT_FAILURE;
    }

    LPCSTR baseStr = argv[1];

    printf("[*] Obfuscating base string... \n");
    unsigned char* hex_ascii_xor = string_to_ascii(baseStr, xor_input_key, sizeof(xor_input_key));

    if(hex_ascii_xor == NULL){
        printf("[!] Error obfuscating string");
        return EXIT_FAILURE;
    }
    print_hex_data("obfuscated str : ", hex_ascii_xor, strlen(baseStr));

    printf("\n[*] Press <ENTER> to recreate base string...");
    getchar();
    
    SIZE_T len = strlen(baseStr);
    LPSTR  clearStr = RecreateBaseString(hex_ascii_xor, len, xor_input_key, sizeof(xor_input_key));

    if(clearStr != NULL){
        printf("[*] New string : %s \n", clearStr);
        free(clearStr);
    }

    return EXIT_SUCCESS;
}
