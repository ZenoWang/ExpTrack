//
// Created by zeno on 18-9-13.
//

#include "Encrypt.h"

Encrypt::Encrypt() {
    register_algs();

    strcpy((char *)tmpkey, PASSWD);

    printf("tmpkey=%s\n",tmpkey);

    outlen = sizeof(key);
    if ((errno = hash_memory(hash_idx,tmpkey,strlen((char *)tmpkey),key,&outlen)) != CRYPT_OK) {
        printf("Error hashing key: %s\n", error_to_string(errno));
        exit(-1);
    }

    char cipher[10];
    strcpy(cipher, "blowfish");

    cipher_idx = find_cipher(cipher);
    if (cipher_idx == -1) {
        printf("Invalid cipher.\n");
        exit(-1);
    }

    hash_idx = find_hash("sha256");
    if (hash_idx == -1) {
        printf("LTC_SHA256 not found...?\n");
        exit(-1);
    }

    ivsize = cipher_descriptor[cipher_idx].block_length;
    ks = hash_descriptor[hash_idx].hashsize;
    if (cipher_descriptor[cipher_idx].keysize(&ks) != CRYPT_OK) {
        printf("Invalid keysize???\n");
        exit(-1);
    }

}

void Encrypt::register_algs()
{

#ifdef LTC_RIJNDAEL
    register_cipher (&aes_desc);
#endif
#ifdef LTC_BLOWFISH
    register_cipher (&blowfish_desc);
#endif
#ifdef LTC_XTEA
    register_cipher (&xtea_desc);
#endif
#ifdef LTC_RC5
    register_cipher (&rc5_desc);
#endif
#ifdef LTC_RC6
    register_cipher (&rc6_desc);
#endif
#ifdef LTC_SAFERP
    register_cipher (&saferp_desc);
#endif
#ifdef LTC_TWOFISH
    register_cipher (&twofish_desc);
#endif
#ifdef LTC_SAFER
    register_cipher (&safer_k64_desc);
    register_cipher (&safer_sk64_desc);
    register_cipher (&safer_k128_desc);
    register_cipher (&safer_sk128_desc);
#endif
#ifdef LTC_RC2
    register_cipher (&rc2_desc);
#endif
#ifdef LTC_DES
    register_cipher (&des_desc);
    register_cipher (&des3_desc);
#endif
#ifdef LTC_CAST5
    register_cipher (&cast5_desc);
#endif
#ifdef LTC_NOEKEON
    register_cipher (&noekeon_desc);
#endif
#ifdef LTC_SKIPJACK
    register_cipher (&skipjack_desc);
#endif
#ifdef LTC_KHAZAD
    register_cipher (&khazad_desc);
#endif
#ifdef LTC_ANUBIS
    register_cipher (&anubis_desc);
#endif

    if (register_hash(&sha256_desc) == -1) {
        printf("Error registering LTC_SHA256\n");
        exit(-1);
    }

    if (register_prng(&yarrow_desc) == -1) {
        printf("Error registering yarrow PRNG\n");
        exit(-1);
    }

    if (register_prng(&sprng_desc) == -1) {
        printf("Error registering sprng PRNG\n");
        exit(-1);
    }
}

void Encrypt::setIO(char *infile, char *outfile) {
    /* file handles setup */
    fdin = fopen(infile,"rb");
    if (fdin == NULL) {
        perror("Can't open input for reading");
        exit(-1);
    }

    fdout = fopen(outfile,"wb");
    if (fdout == NULL) {
        perror("Can't open output for writing");
        exit(-1);
    }

}

void Encrypt::encrypt(char *infile, char *outfile) {
    setIO(infile, outfile);

    if ((errno = rng_make_prng(128, find_prng("yarrow"), &prng, NULL)) != CRYPT_OK) {
        printf("Error setting up PRNG, %s\n", error_to_string(errno));
    }

    /* You can use rng_get_bytes on platforms that support it */
    /* x = rng_get_bytes(IV,ivsize,NULL);*/
    x = yarrow_read(IV,ivsize,&prng);
    if (x != ivsize) {
        printf("Error reading PRNG for IV required.\n");
        exit(-1);
    }

    if (fwrite(IV,1,ivsize,fdout) != ivsize) {
        printf("Error writing IV to output.\n");
        exit(-1);
    }

    if ((errno = ctr_start(cipher_idx,IV,key,ks,0,CTR_COUNTER_LITTLE_ENDIAN,&ctr)) != CRYPT_OK) {
        printf("ctr_start error: %s\n",error_to_string(errno));
        exit(-1);
    }

    do {
        y = fread(inbuf,1,sizeof(inbuf),fdin);

        if ((errno = ctr_encrypt(inbuf,ciphertext,y,&ctr)) != CRYPT_OK) {
            printf("ctr_encrypt error: %s\n", error_to_string(errno));
            exit(-1);
        }

        if (fwrite(ciphertext,1,y,fdout) != y) {
            printf("Error writing to output.\n");
            exit(-1);
        }
    } while (y == sizeof(inbuf));
    fclose(fdout);
    fclose(fdin);

}

void Encrypt::decrypt(char *infile, char *outfile) {
    setIO(infile, outfile);

    /* Need to read in IV */
    if (fread(IV,1,ivsize,fdin) != ivsize) {
        printf("Error reading IV from input.\n");
        exit(-1);
    }

    if ((errno = ctr_start(cipher_idx,IV,key,ks,0,CTR_COUNTER_LITTLE_ENDIAN,&ctr)) != CRYPT_OK) {
        printf("ctr_start error: %s\n",error_to_string(errno));
        exit(-1);
    }

    /* IV done */
    do {
        y = fread(inbuf,1,sizeof(inbuf),fdin);

        if ((errno = ctr_decrypt(inbuf,plaintext,y,&ctr)) != CRYPT_OK) {
            printf("ctr_decrypt error: %s\n", error_to_string(errno));
            exit(-1);
        }

        if (fwrite(plaintext,1,y,fdout) != y) {
            printf("Error writing to file.\n");
            exit(-1);
        }
    } while (y == sizeof(inbuf));
    fclose(fdin);
    fclose(fdout);

}

Encrypt::~Encrypt() {

}
