#include <stdio.h>
#include <string.h>
#include "linker.h"

int main(int argc, char *argv[])
{
    if (argc >=4 && !strcmp(argv[1], "-o"))
    {
            ld(argv[2], argv[3]);
            return 0;
    }

    printf("ca parse archi pas\n");
    return 1;
}
