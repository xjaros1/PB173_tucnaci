#ifndef AES_FUNCS_H
#define AES_FUNCS_H

#define BAD_FILE_FORMAT -3
#define BAD_CHECK_SUM -4
#define BAD_KEY_USED -5
#define BAD_FILES_USED -6
#define BUFFER_SIZE 1024*1024

#include <stdlib.h>
#include <polarssl/aes.h>
#include <stdio.h>

typedef unsigned int uint;

typedef unsigned char u_char;

/**
 *  @brief  AES file structure.
 */
typedef struct
{

    FILE * input;
    size_t size_of_data;

    size_t begin_data;
    size_t end_data;

    aes_context * c;

    unsigned char * key;
    unsigned char * vector;
    int type;

} aes_file;

/**
 * @brief   generate_rand_bits
 *          Generates random string
 *          which can be used as encrypt key or
 *          initialization vector.
 *
 * @param   size How many bits will be generated.
 *
 * @return  String which constains the randomly generated bytes
 */

unsigned char * generate_rand_bits(size_t size);

/**
 * @brief   aes_file_parse_enc
 *          Prepares the aes_file structure and sets all nescessary parameters.
 *
 * @param   data aes_file structure to initialize
 * @param   input File which contains data to encrypt
 * @param   key_file File which contains key used for aes encryption.
 *
 * @return  Zero if was successfull or one of the fail return codes.
 */
int aes_file_parse_enc(aes_file * data, FILE * input, FILE * key_file);

/**
 * @brief   aes_file_parse_dec
 *          Prepares the aes_file
 *          structure for decryption.
 *
 * @param   data aes_file structure to be initialized
 * @param   input Encrypted input file
 * @param   key_file Key used for decryption
 *
 * @return  Zero if was successfull or one of the fail return codes.
 */
int aes_file_parse_dec(aes_file * data, FILE * input, FILE * key_file);


/**
 * @brief   aes_crypt_file
 *          The main function which \
 * @param   data
 * @param   output
 *
 * @return
 */
int aes_crypt_file(aes_file * data, FILE *output);


/**
 * @brief hmac_check
 * @param data
 * @return
 */
int hmac_check(aes_file *data);

/**
 * @brief key_check
 * @param data
 * @param end_ptr
 * @return
 */
int key_check(aes_file * data, unsigned char *end_ptr);

/**
 * @brief generate_aes_key
 * @param file_name
 * @return
 */
int generate_aes_key(char *file_name);

/**
 * @brief padd_pkcs7
 * @param mod
 * @param size
 * @return
 */
int padd_pkcs7(unsigned char * mod, int size);

/**
 * @brief get_num_of_padd
 * @param mod
 * @param size
 * @return
 */
int get_num_of_padd(unsigned char* mod, int size);

/**
 * @brief hmac_count
 * @param in
 * @param is_check
 * @param key
 * @return
 */
unsigned char * hmac_count(FILE * in, int is_check , unsigned char * key);

/**
 * @brief read_key_file
 * @param key_file
 * @param out
 * @return
 */
int read_key_file(FILE * key_file, unsigned char * out);

/**
 * @brief aes_start_encrypt
 * @param input_name
 * @param out
 * @param key_file_n
 * @return
 */
int aes_start_encrypt(const char * input_name, const char *out, const char * key_file_n);

/**
 * @brief aes_start_decrypt
 * @param input_name
 * @param out
 * @param key_file_n
 * @return
 */
int aes_start_decrypt(const char *input_name, const char *out, const char *key_file_n);

/**
 * @brief get_size_of_file
 * @param f
 * @return size of file
 */
size_t get_size_of_file(FILE * f);


#endif // AES_FUNCS_H
