#include <stdio.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <string.h>


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
    char password[9] = "";
    int password_index = 0;
    for (int inc = 0; inc < 100000000; inc++)
    {
        if (strlen(password) == 8)
        {
            break;
        }
        char string[100];
        sprintf(string, "%s%d", input, inc);
        str2MD5(string, strlen(string), md5string);
        if (!strncmp(md5string, "00000", 5))
        {
            password[password_index] = md5string[5];
            password_index++;
            printf("Password: %s\tFound at %d\n", password, inc);
        }
    }
}