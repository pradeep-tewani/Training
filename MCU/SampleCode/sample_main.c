//This is string literal (constant data). This will be stored in ROM (flash memory)
const char *pMessage = "Hi there, Hello World"

// This is constant data and would be stored in ROM (flash memory)
const int value = 200;
// This is not a constant data. This will be stored in SRAM
char myData[50];

int main()
{
    for (i = 0; i < strlen(pMessage); i++)
    {
        /* This is the data copy from the flash to SRAM */
        myData[i] = *(pMessage + i);
    }
    for (;;);
}

