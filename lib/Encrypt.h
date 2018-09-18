//
// Created by zeno on 18-9-13.
//

#ifndef UNTITLED_ENCRYPT_H
#define UNTITLED_ENCRYPT_H

#include <tomcrypt.h>

#define PASSWD "vaSWm5XaPaezrwsN9sGGfVQ1sCQFrAWDZSZI7M02NZJrWtgUXiqAQKp3SdYY5DB2jvFhfWn6wK4ARldwlMqrAOmFI2wKd8auZiz"

class Encrypt {

public:
    Encrypt();
    ~Encrypt();

    void encrypt(char *, char *);
    void decrypt(char *, char *);

private:
    int errno;
    unsigned char plaintext[512],ciphertext[512];
    unsigned char tmpkey[512],key[MAXBLOCKSIZE],IV[MAXBLOCKSIZE];
    unsigned char inbuf[512]; /* i/o block size */
    unsigned long outlen, y, ivsize, x;
    symmetric_CTR ctr;
    int cipher_idx, hash_idx, ks;
    //char *infile, *outfile, *cipher;
    prng_state prng;
    FILE *fdin, *fdout;

    void register_algs();
    void setIO(char *, char *);

};


#endif //UNTITLED_ENCRYPT_H
