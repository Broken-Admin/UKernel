/*
execution of the kernel begins and ends here
*/
#include "include/screen.h"
#include "include/charcolors.h"

const char *kernelName = "Ultranium Kernel"; // define kernel name
const char *kernelVersion = "v0.01 Alpha";   // define kernel version

void kernel_exit_handler(void)
{
    const char *exitmsg = "\n[#0AINFO#07] Kernel code execution finished, halt";
    kprint(exitmsg);
    return;
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
