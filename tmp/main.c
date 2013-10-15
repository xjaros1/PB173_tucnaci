#include <stdio.h>
#include "aes_funcs.h"
#include "minunit.h"

int tests_run = 0;


int compare_files(const char * f1, const char * f2)
{
    size_t s1, s2;
    FILE * file1, *file2;

    file1 = fopen(f1, "r");
    file2 = fopen(f2, "r");

    s1 = get_size_of_file(file1);
    s2 = get_size_of_file(file2);

    if(s1!=s2)
    {
        return s1-s2;
    }

    unsigned char str1[s1], str2[s2];
    fread(str1, sizeof(unsigned char), s1, file1);
    fread(str2, sizeof(unsigned char), s2, file2);

    return strncmp((char*) str1, (char*)str2, s1);
}

char * test_ok_key_format()
{
    FILE  * key1, *key2, *key3;

    key1 = fopen("test_files/klic1","r");
    key2 = fopen("test_files/klic2","r");
    key3 = fopen("test_files/klic3","r");

    u_char key[16];
    MU_ASSERT("Test of 1st key.", read_key_file(key1,key)==0);
    MU_ASSERT("Test of 2nd key.", read_key_file(key2, key)==0);
    MU_ASSERT("Test of 3rd key.", read_key_file(key3, key)==0);

    fclose(key1);
    fclose(key2);
    fclose(key3);

    return NULL;

}


char * test_key_bad_format()
{
    FILE * long_key, *empty_key, *bad_format_key;
    u_char key[16];

    long_key = fopen("test_files/long_key","r");
    MU_ASSERT("Test of long key.", read_key_file(long_key,key)==BAD_FILE_FORMAT);
    fclose(long_key);

    empty_key = fopen("test_files/empty_key","r");
    MU_ASSERT("Test of empty key file.", read_key_file(empty_key,key)==BAD_FILE_FORMAT);
    fclose(empty_key);

    bad_format_key = fopen("test_files/bad_format_key","r");
    MU_ASSERT("Test of bad format key file.", read_key_file(bad_format_key,key)==BAD_FILE_FORMAT);
    fclose(bad_format_key);

    return NULL;

}

char * test_not_exists_file(int(*test_func)(const char *, const char *, const char *))
{
    MU_ASSERT("Not existing input", test_func("test_files/not_exists", "test_files/not_exists_out",
              "test_files/not_exists_test_key")==BAD_FILES_USED);
    MU_ASSERT("Not writeable output", test_func("test_files/not_exists_test_data",
              "test_files/not_exists_test_inacc_file","test_files/not_exists_test_key" )==BAD_FILES_USED);

    MU_ASSERT("Key file not exists", test_func("test_files/not_exists_test_data",
             "test_files/not_exists_out", "test_files/not_exists_key")==BAD_FILES_USED);

    MU_ASSERT("Not acces to input", test_func("test_files/not_exists_test_inacc_file",
               "test_files/whatever", "test_files/not_exists_test_key")==BAD_FILES_USED);

    MU_ASSERT("Not acces to key file", test_func("test_files/not_exists_test_data",
              "test_files/whatever", "test_files/not_exists_test_inacc_file")==BAD_FILES_USED);
    return NULL;
}

char * test_encryption_file_not_exists_or_premision_denied()
{
    return test_not_exists_file(aes_start_encrypt);
}

char * test_decryption_file_ne_or_pd()
{
    return test_not_exists_file(aes_start_decrypt);
}

char * test_encryption()
{
    MU_ASSERT("Encryption of file not passed", aes_start_encrypt("test_files/encrypt_test_data",
              "test_files/encrypt_test_output", "test_files/klic1")==0);
    puts("");
    return NULL;
}

char * test_decryption()
{
    MU_ASSERT("Decryption of correct file failed",
              aes_start_decrypt("test_files/encrypt_test_output", "output", "test_files/klic1")==0);

    MU_ASSERT("The encrypted and decrypted file are different",
              compare_files("output", "test_files/encrypt_test_data")==0);


    MU_ASSERT("The corrupted file was decrypted",
              aes_start_decrypt("test_files/decrypt_test_corr_input", "output", "test_files/klic1")==BAD_CHECK_SUM);

    MU_ASSERT("The wrong key was used to decrypt and not decetded",
              aes_start_decrypt("test_files/encrypt_test_output", "output", "test_files/klic2")==BAD_KEY_USED);

    return NULL;
}

char * test_all()
{
    MU_RUN_TEST(test_ok_key_format);
    MU_RUN_TEST(test_key_bad_format);
    MU_RUN_TEST(test_encryption_file_not_exists_or_premision_denied);
    MU_RUN_TEST(test_decryption_file_ne_or_pd);
    MU_RUN_TEST(test_encryption);
    MU_RUN_TEST(test_decryption);
    return 0;
}

int main(void)
{
    char * result = test_all();

    printf("Number of tests run: %d\n", tests_run);
    if(result) printf("Failed test: %s\n", result);
    else printf("All tests passed\n");
    return 0;
}

