#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// int calcFirst(int x, int y)
// {
//     return ((x*x) + (3*x) + ((2*x)*y) + y + (y*y));
// }

// int calcSecond(int x, int y)
// {
//     return (x + y);
// }

void intToBinary(char output[64], int num) {
    // Ensure the output array is empty
    memset(output, 0, 64);

    int index = 63; // Start from the rightmost position in the array

    // Handle the case where num is 0
    if (num == 0) {
        output[index] = '0';
        return;
    }

    while (num > 0 && index >= 0) {
        output[index] = (num % 2) + '0'; // Convert the least significant bit to '0' or '1'
        num = num / 2; // Right-shift the number
        index--;
    }
}

int
main(int argc, char *argv[])
{
    // if (argc != 2)
    // {
    //     printf("Usage: %s [fav num] [x] [y]\n", argv[0]);
    //     exit(EXIT_FAILURE);
    // }

    char binary[64];
    int num = 42; // Change this to the desired integer
    intToBinary(binary, num);
    printf("Binary representation of %d is: %s\n", num, binary);
    // int first = calcFirst()
}