#include "cpuinfo.h"
#include "boardinfo.h"
#include "memoryspeed.h"
#include "coremark.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define ONLY_INFO 1

int main(void)
{
    printf("--BOARD TEST--\n");

    cpuinfo_main();
    print_all_temp();

#if !(ONLY_INFO)
    printf("\n-memspeed start-\n");
    memspeed_test_main();
    
    printf("\n-coremark start-\n");
    coremark_main();
#endif
    return 0;
}

