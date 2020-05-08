#include <stdio.h>

int main(int argc, char *argv[])
{
    unsigned long address;
    unsigned long page;
    unsigned long offset;

    const unsigned long pagesize = 4096;

    address = atoi(argv[1]);
    page = address / pagesize;
    offset = address % pagesize;

    printf("The address %lu contains:\n", address);
    printf("page number = %lu\n", page);
    printf("offset = %lu\n", offset);


    return 0;
}

