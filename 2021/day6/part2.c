#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include "intarr/intarr.h"

typedef struct node {
    int value;
    struct node *next;
} node_t;


void add_node(node_t** head, int value) {
    node_t *new_node = malloc(sizeof(node_t));
    new_node->value = value;
    new_node->next = *head;
    *head = new_node;
}

void print_list(node_t *head) {
    while (head != NULL) {
        printf("%d,", head->value);
        head = head->next;
    }
    printf("\n");
}

void free_list(node_t *head)
{
    node_t *next;
    while (head != NULL)
    {
        next = head->next;
        free(head);
        head = next;
    }
}

int list_size(node_t *head)
{
    int size = 0;
    while (head != NULL)
    {
        size++;
        head = head->next;
    }
    return size;
    // printf("Size of list: %d\n", size);
}

void simulate_lanternfish(node_t **head)
{
    for (int day = 1; day < 257; day++)
    {
        printf("Simulating day %d\n", day);
        node_t *current_node = *head;
        while (current_node != NULL)
        {
            if (current_node->value == 0)
            {
                add_node(head, 8);
                current_node->value = 6;
            }
            else
            {
                current_node->value -= 1;
            }
            current_node = current_node->next;
        }
        // print_list(*head);
    }
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

    // get line from file
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    getline(&line, &len, p_input_file);
    line[strcspn(line, "\n")] = 0;  // Remove trailing newline
    // printf("%s\n", line);

    // parse line
    size_t size = strlen(line);
    char *token = strtok(line, ",");

    node_t *head = NULL;

    while (token != NULL)
    {
        add_node(&head, atoi(token));
        token = strtok(NULL, ",");
    }

    // print_list(head);
    // simulate
    simulate_lanternfish(&head);

    printf("There are %d lanternfish in the lake.\n", list_size(head));

    free_list(head);
    // intarr_free(intarr);
    free(line);
    fclose(p_input_file);
    exit(EXIT_SUCCESS);
}