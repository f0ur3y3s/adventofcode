#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *cid;
    int value;
} reg_t;


void
initRegs(reg_t bunny_reg[4], size_t size)
{
    bunny_reg[0].cid = 'a';
    bunny_reg[0].value = 0;
    bunny_reg[1].cid = 'b';
    bunny_reg[1].value = 0;
    bunny_reg[2].cid = 'c';
    bunny_reg[2].value = 0;
    bunny_reg[3].cid = 'd';
    bunny_reg[4].value = 0;
}

void
copyReg(reg_t *bunny_reg, int value)
{
    bunny_reg->value = value;
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

    char line[16];
    char *token;
    int num;
    char var;
    reg_t bunny_reg[4];
    initRegs(bunny_reg, sizeof(bunny_reg)/sizeof(reg_t));

    while(fscanf(p_input_file, "%[^\n]\n", line) != EOF)
    {
        token = strtok(line, " ");
        if (strcmp(token, "cpy") == 0)
        {
            token = strtok(NULL, " ");
            sscanf(token, "%d", &num);
            token = strtok(NULL, " ");
            sscanf(token, "%c", &var);
            
            printf("COPY %d into %c\n", num, var);
        }
        else if (strcmp(token, "inc") == 0)
        {
            token = strtok(NULL, " ");
            printf("Incrementing %s\n", token);
        }
        else if (strcmp(token, "dec") == 0)
        {
            token = strtok(NULL, " ");
            printf("Decrementing %s\n", token);

        }
        else if (strcmp(token, "jnz") == 0)
        {
            token = strtok(NULL, " ");
            sscanf(token, "%c", &var);
            token = strtok(NULL, " ");
            sscanf(token, "%d", &num);
            if (num != 0)
            {

            }
            printf("Jump var %c by %d\n", var, num);

        }
        else {
            printf("Unknown instruction: %s\n", token);
            continue;
        }
    }
}