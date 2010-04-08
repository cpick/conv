#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    int c;

    while(EOF != (c = fgetc(stdin)))
    {
        printf("%d", c);
    }

    if(ferror(stdin))
    {
        fprintf(stderr, "%s: fgetc failed: %d %s", __func__, errno, 
                strerror(errno));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
