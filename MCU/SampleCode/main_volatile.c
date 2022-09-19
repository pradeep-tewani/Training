#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#include <stdint.h>

#define SRAM_ADDRESS1   0x20000004Ul

int main()
{
    uint32_t value = 0;
    uint32_t *p = (uint32_t *)SRAM_ADDRESS1;

    while(1)
    {
        value = *p;
        if (value) break;
    }
    while(1);
}

