#include "memoryspeed.h"
#include "coremark.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main(void)
{
    printf("--BOARD TEST--\n");

    printf("\n-memspeed start-\n");
    memspeed_test_main();
    
    printf("\n-coremark start-\n");
    coremark_main();
    return 0;
}

