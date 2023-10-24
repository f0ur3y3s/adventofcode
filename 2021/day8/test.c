#include <stdio.h>
#include <string.h>

void sortString(char str[]) {
    int n = strlen(str);
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

int main() {
    char str1[] = "cdfbe";
    char str2[] = "cdfgeb";

    sortString(str1);
    sortString(str2);

    int compareResult = strcmp(str1, str2);

    if (compareResult < 0) {
        printf("The minimum string is: %s\n", str1);
        printf("The maximum string is: %s\n", str2);
    } else if (compareResult > 0) {
        printf("The minimum string is: %s\n", str2);
        printf("The maximum string is: %s\n", str1);
    } else {
        printf("Both strings are equal.\n");
    }

    return 0;
}
