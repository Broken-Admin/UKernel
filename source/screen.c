#include "include/screen.h"
#include "include/charcolors.h"

char *vidmemptr = (char *)0xb8000; // pointer to video memory
unsigned int current_loc = 0;      // current char location

/*
Writes chars to video memory
*/
void kprint(const char *str)
{
    // When providing characterstring argument, #[BG_COLORCODE_4BIT][FG_COLORCODE_4BIT] can be added before text
    // which need be colored.
    // Example in *exitmsg in kernel.c, kernel_exit_handler()
    unsigned int currentcolor = 0x07; // fg color code of light gray on black bg
    unsigned int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '#' &&
            str[i + 1] != '#')
        {
            i++; // go to hexcodeone location
            // get the hex value code
            int charcodeone = str[i++];
            if (charcodeone >= 'A' && charcodeone <= 'F')
            {
                currentcolor = (charcodeone - 'A' + 0xA) * 16;
            }
            else if (charcodeone >= 'a' && charcodeone <= 'f')
            {
                currentcolor = (charcodeone - 'a' + 0xA) * 16;
            }
            else if (charcodeone >= '0' && charcodeone <= '9')
            {
                currentcolor = (charcodeone - '1' + 0x1) * 16;
            }
            int charcodetwo = str[i++];
            if (charcodetwo >= 'A' && charcodetwo <= 'F')
            {
                currentcolor += charcodetwo - 'A' + 0xA;
            }
            else if (charcodetwo >= 'a' && charcodetwo <= 'f')
            {
                currentcolor += charcodetwo - 'a' + 0xA;
            }
            else if (charcodetwo >= '0' && charcodetwo <= '9')
            {
                currentcolor += charcodetwo - '1' + 0x1;
            }
            else if (charcodetwo == '#')
            {
            }
            continue;
        }
        else if (str[i] == '#' &&
                 str[i + 1] == '#') // Handles "##"
        {
            i++;
        }
        else if (str[i] == '\n')
        {
            unsigned int line_size = CHAR_BYTE_SIZE * COLUMNS_IN_LINE;
            current_loc = current_loc + (line_size - current_loc % (line_size));
            i++;
            continue;
        }
        vidmemptr[current_loc++] = str[i++];     // print char
        vidmemptr[current_loc++] = currentcolor; // default light grey fg on black bg}
    }
}

/*
kprint() variant with single-color text
*/
void kprintcolored(const char *str, unsigned int color)
{
    unsigned int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '\n')
        { // check for \n symbol
            unsigned int line_size = CHAR_BYTE_SIZE * COLUMNS_IN_LINE;
            current_loc = current_loc + (line_size - current_loc % (line_size));
            i++;
            continue;
        }
        vidmemptr[current_loc++] = str[i++]; // print char
        vidmemptr[current_loc++] = color;    // set attrib-byte to user-defined color
    }
}

/*
Loop over the entire screen, filling video memory with empty chars
*/
void clear_screen(void)
{
    unsigned int i = 0;
    while (i < SCREENSIZE)
    {
        vidmemptr[i++] = ' ';
        vidmemptr[i++] = 0x07;
    }
}