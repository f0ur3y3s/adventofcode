#include <string.h>
#include "shared.h"

/**
 * @brief Strips the newline in a newline terminated string.
 *
 * @param to_strip A char array to strip
 */
void strsnl (char * to_strip)
{
    to_strip[strcspn(to_strip, "\n")] = '\0';
}