#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

typedef struct {
    char *letters;
    int num_letters;
} segment_t;

typedef struct {
    segment_t **segments;
    int capacity;
} digits_t;

int compare_strings(const char* large_str, const char* small_str);


digits_t * digits_create(void)
{
    digits_t * new_digits = malloc(sizeof(digits_t));
    new_digits->capacity = 10;
    new_digits->segments = malloc(new_digits->capacity * sizeof(segment_t *));
    for (int idx = 0; idx < new_digits->capacity; idx++)
    {
        new_digits->segments[idx] = malloc(sizeof(segment_t)); // Allocate memory for each segment
        new_digits->segments[idx]->letters = NULL; // Initialize to NULL

        switch(idx)
        {
            case 0:
                new_digits->segments[idx]->num_letters = 6;
            break;
            case 1:
                new_digits->segments[idx]->num_letters = 2;
            break;
            case 2:
                new_digits->segments[idx]->num_letters = 5;
            break;
            case 3:
                new_digits->segments[idx]->num_letters = 5;
            break;
            case 4:
                new_digits->segments[idx]->num_letters = 4;
            break;
            case 5:
                new_digits->segments[idx]->num_letters = 5;
            break;
            case 6:
                new_digits->segments[idx]->num_letters = 6;
            break;
            case 7:
                new_digits->segments[idx]->num_letters = 3;
            break;
            case 8:
                new_digits->segments[idx]->num_letters = 7;
            break;
            case 9:
                new_digits->segments[idx]->num_letters = 6;
            break;
        }
    }
    return new_digits;
}

void digits_print(digits_t *digits_arr)
{
    for (int idx = 0; idx < digits_arr->capacity; idx++)
    {
        printf("Number: %d, Segments: ", idx);
        printf("%s", digits_arr->segments[idx]->letters);
        printf("\n");
    }
}

void digits_free(digits_t *digits_arr)
{
    for (int idx = 0; idx < digits_arr->capacity; idx++)
    {
        free(digits_arr->segments[idx]->letters);
        free(digits_arr->segments[idx]);
    }
    free(digits_arr->segments);
    free(digits_arr);
}

int digits_find(digits_t *digits_arr, char *letters)
{
    for (int idx = 0; idx < digits_arr->capacity; idx++)
    {
        if (compare_strings(digits_arr->segments[idx]->letters, letters) == strlen(digits_arr->segments[idx]->letters))
        {
            // If the letters match, return the associated number
            return idx;
        }
    }

    // If no match is found, return -1 to indicate failure
    return -1;
}


void string_sort(char *str, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (str[j] > str[j + 1]) {
                char temp = str[j];
                str[j] = str[j + 1];
                str[j + 1] = temp;
            }
        }
    }
}

// int compare_strings(const char* large_str, const char* small_str) {
//     int largelen = strlen(large_str);
//     int smalllen = strlen(small_str);
//     // If the smaller string is empty, it's considered to be found in the larger string.
//     if (smalllen == 0) {
//         return 1;
//     }
//     if (largelen < smalllen) {
//         return 0; // The smaller string cannot be found in the larger string.
//     }
//     // Create a character count array for the larger string.
//     int char_count[256] = {0}; // Assuming ASCII characters.
//     // Count characters in the larger string.
//     for (int i = 0; i < largelen; i++) {
//         char_count[(int)large_str[i]]++;
//     }
//     // Check if all characters in the smaller string are found in the larger string.
//     for (int i = 0; i < smalllen; i++) {
//         if (char_count[(int)small_str[i]] == 0) {
//             return 0; // Character not found.
//         }
//         char_count[(int)small_str[i]]--;
//     }
//     return 1; // All characters in the smaller string are found.
// }

int compare_strings(const char* large_str, const char* small_str) {
    int largelen = strlen(large_str);
    int smalllen = strlen(small_str);

    int match_count = 0; // Initialize match count to 0.

    // If the smaller string is empty, it's considered to be found in the larger string.
    if (smalllen == 0) {
        return largelen;
    }

    if (largelen < smalllen) {
        return 0; // The smaller string cannot be found in the larger string.
    }

    // Create a character count array for the larger string.
    int char_count[256] = {0}; // Assuming ASCII characters.

    // Count characters in the larger string.
    for (int i = 0; i < largelen; i++) {
        char_count[(int)large_str[i]]++;
    }

    // Check if all characters in the smaller string are found in the larger string.
    for (int i = 0; i < smalllen; i++) {
        if (char_count[(int)small_str[i]] == 0) {
            // Do not return early.
        } else {
            char_count[(int)small_str[i]]--;
            match_count++; // Increment the match count.
        }
    }

    return match_count; // Return the final match count.
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

    digits_t *digit_arr = NULL;
    // digits_print(digit_arr);

    char *buffer = NULL;
    size_t len = 0;
    ssize_t read = 0;
    char wiring[100];
    char digits[100];
    char *token = NULL;
    int length = 0;
    char *wiring_analysis;
    int final = 0;
    
    while((read = getline(&buffer, &len, p_input_file)) > 0)
    {
        digit_arr = digits_create();
        sscanf(buffer, "%[^|]| %[^\n]\n", wiring, digits);
        printf("%s\n", digits);
        wiring_analysis = strdup(wiring);
        token = strtok(wiring_analysis, " ");
        int segment_idx = -1;
        while (token)
        {
            // printf("%s\n", token);
            length = strlen(token);
            switch (length)
            {
                case 2: // 1
                    segment_idx = 1;
                break;
                case 3: // 7
                    segment_idx = 7;
                break;
                case 4: // 4
                    segment_idx = 4;
                break;
                case 7: // 8
                    segment_idx = 8;
                break;
            }
            if (segment_idx != -1 && !digit_arr->segments[segment_idx]->letters)
            {
                digit_arr->segments[segment_idx]->letters = strdup(token);
            }
            token = strtok(NULL, " ");
        }
        free(wiring_analysis);
        free(token);
        digits_print(digit_arr);



        wiring_analysis = strdup(wiring);
        token = strtok(wiring_analysis, " ");
        segment_idx = -1;
        while (token)
        {
            printf("%s\n", token);
            digits_print(digit_arr);

            length = strlen(token);
            switch (length)        // based on 1,4,7,8 which wire is connect to which side

            {
                case 5:
                    if (3 == compare_strings(token, digit_arr->segments[7]->letters))
                    {
                        segment_idx = 3;
                    }
                    else
                    {
                        if (3 == compare_strings(token, digit_arr->segments[4]->letters))
                        {
                            segment_idx = 5;
                        }
                        else
                        {
                            segment_idx = 2;
                        }
                    }
                break;
                case 6:
                    if (4 == compare_strings(token, digit_arr->segments[4]->letters))
                    {
                        segment_idx = 9;
                    }
                    else
                    {
                        if (3 == compare_strings(token, digit_arr->segments[7]->letters))
                        {
                            segment_idx = 0;
                        }
                        else
                        {
                            segment_idx = 6;
                        }        // based on 1,4,7,8 which wire is connect to which side

                    }
                break;
            }
            if (segment_idx != -1 && !digit_arr->segments[segment_idx]->letters)
            {
                digit_arr->segments[segment_idx]->letters = strdup(token);
            }
            token = strtok(NULL, " ");
        }
        free(token);
        digits_print(digit_arr);

        token = strtok(digits, " ");
        int place = 1000;
        int constructor = 0;
        while (token)
        {
            int ret = digits_find(digit_arr, token);
            constructor += place * ret;
            place /= 10;
            // printf("%d\n", ret);
            // lookup the string in each digits
            token = strtok(NULL, " ");
        }
        printf("constructor: %d\n", constructor);
        final += constructor;
        digits_free(digit_arr);
    }

    printf("Final: %d\n", final);
    free(buffer);
    free(wiring_analysis);
    free(token);
    // digits_free(digit_arr);
    fclose(p_input_file);
}

// struct should be as follows:
// digit: 0 | letters: [], num_letters: 6
// digit: 1 | letters: [], num_letters: 2
// digit: 2 | letters: [], num_letters: 
// digit: 3 | letters: [], num_letters: 
// digit: 4 | letters: [], num_letters: 4
// digit: 5 | letters: [], num_letters: 
// digit: 6 | letters: [], num_letters: 
// digit: 7 | letters: [], num_letters: 3
// digit: 8 | letters: [], num_letters: 8
// digit: 9 | letters: [], num_letters: 

// we only know 1,4,7,8
// can we reduce to those four numbers?

// 0 -> 8 contains 0
// 2 -> contains only 1 of 1
// 3 -> 
// 5 -> contains only 1 of 1
// 6 -> contains 5
// 9 -> contains 4

//   0:      1:      2:      3:      4:
//  aaaa    ....    aaaa    aaaa    ....
// b    c  .    c  .    c  .    c  b    c
// b    c  .    c  .    c  .    c  b    c
//  ....    ....    dddd    dddd    dddd
// e    f  .    f  e    .  .    f  .    f
// e    f  .    f  e    .  .    f  .    f
//  gggg    ....    gggg    gggg    ....

//   5:      6:      7:      8:      9:
//  aaaa    aaaa    aaaa    aaaa    aaaa
// b    .  b    .  .    c  b    c  b    c
// b    .  b    .  .    c  b    c  b    c
//  dddd    dddd    ....    dddd    dddd
// .    f  e    f  .    f  e    f  .    f
// .    f  e    f  .    f  e    f  .    f
//  gggg    gggg    ....    gggg    gggg