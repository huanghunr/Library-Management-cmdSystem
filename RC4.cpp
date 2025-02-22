#include "RC4.h"

unsigned char sbox[257] = { 0 };

// 初始化 s 表
void init_sbox(unsigned char* key) {
    unsigned int i, j, k;
    int tmp;

    for (i = 0; i < size; i++) {
        sbox[i] = i;
    }

    j =k = 0;
    for (i = 0; i < size; i++) {
        tmp = sbox[i];
        j = (j + tmp + key[i % 9]) % size;  
        sbox[i] = sbox[j];
        sbox[j] = tmp;
    }
}


void enc(unsigned char* key, unsigned char* data) {
    int i, j, k, R, tmp;

    init_sbox(key);

    j = k = 0;
    for (i = 0; i < strlen((char*)data); i++) {
        j = (j + 1) % size;
        k = (k + sbox[j]) % size;

        tmp = sbox[j];
        sbox[j] = sbox[k];
        sbox[k] = tmp;

        R = sbox[(sbox[j] + sbox[k]) % size];

        data[i] ^= R;
    }
}
