#include <stdio.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <string.h>

// run this on 20.04 or 22.04 with libssl-dev on openssl3.0+
void
str2MD5(char *string, size_t length, char *output)
{
    unsigned char digest[EVP_MAX_MD_SIZE];
    EVP_Digest((unsigned char*)string, length, digest, NULL, EVP_md5(), NULL);
    char mdString[33];
    for(int i = 0; i < 16; i++)
        sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
    strncpy(output, mdString, 32);
}

int
main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s [file]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *p_input_file;
    p_input_file = fopen(argv[1],"r");
    if (!p_input_file)
    {
        printf("Error opening file.\n");
        exit(EXIT_FAILURE);
    }

    char input[10];
    fscanf(p_input_file, "%s", input);
    fclose(p_input_file);
    char md5string[33];
    for (int inc = 0; inc < 100000000; inc++)
    {
        char string[100];
        sprintf(string, "%s%d", input, inc);
        str2MD5(string, strlen(string), md5string);
        if (!strncmp(md5string, "00000", 5))
        {
            printf("Part 1: %d\n", inc);
            continue;
        }
        if (!strncmp(md5string, "000000", 6))
        {
            printf("Part 2: %d\n", inc);
            exit(1);
        }
    }
}