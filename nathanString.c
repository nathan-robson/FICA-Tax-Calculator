#include "nathanString.h"


/* compare 2 strings to each other, returns 0 on success */
int compStrings(char* a, char* b)
{
    while(*a == *b)
    {
        if((*a == '\0') || (*b == '\0'))
        {
            break;
        }

        a++;
        b++;
    }

    if((*a == '\0') && (*b == '\0')) { return 0; }
    else { return 1; }
}


/* copy a given string into another of the same size */
int copyString(char* dest, char* src)
{
    while(*src != '\0')
    {
        *dest = *src;
        src++;
        dest++;
    }

    *dest = '\0';
    return 0;
}
