/* Includes --------------------------------------------------------------- */
#include <stdio.h>
#include <string.h>

#include "configurator.h"

/* Main --------------------------------------------------------------- */

int main(void)
{
    int error = 0;
    printf("Hello world!!!\n");
    error = configurator_close(0);
    if (error != 0)
    {
        printf("ERROR: %s", strerror(error));
    }
    return 0;
}