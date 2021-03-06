/*
execution of the kernel begins and ends here
*/
#include "include/screen.h"
#include "include/charcolors.h"

const char *kernelName = "Ultranium Kernel"; // define kernel name
const char *kernelVersion = "v0.01 Alpha";   // define kernel version

void kernel_exit_handler(void)
{
    const char *bracket1 = "\n[";
    const char *bracket2 = "] ";
    const char *infosign = "INFO";
    const char *exitmsg = "Kernel code execution finished, halt";
    kprint(bracket1);
    kprintcolored(infosign, CHAR_FG_LIGHTGREEN);
    kprint(bracket2);
    kprint(exitmsg);
    return;
    /*
    TODO: Clean up this code. Perhaps make a function that will write colored text inside brackets.
    */
}

void kmain(void)
{
    clear_screen();
    kprint(kernelName);
    kprint(" "); // space between kernel name and version
    kprint(kernelVersion);
    kprint("\n");
    /*
    TODO: Add functionality
    */
    kernel_exit_handler(); // call on-exit procedure
    return;
}
