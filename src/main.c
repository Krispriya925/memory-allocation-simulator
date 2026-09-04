#include <stdio.h>
#include "Process.h"

int main() {

    Process p1;

    initializeProcess(&p1, 1, 200);

    printf("Process ID       : %d\n", p1.processId);
    printf("Memory Required  : %d KB\n", p1.memoryRequired);
    printf("Allocated        : %s\n",
           p1.allocated ? "Yes" : "No");

    printf("\nAllocating memory...\n");

    allocateProcess(&p1, 500);

    printf("Start Address    : %d\n", p1.startAddress);
    printf("End Address      : %d\n", p1.endAddress);
    printf("Allocated        : %s\n",
           p1.allocated ? "Yes" : "No");

    printf("\nDeallocating memory...\n");

    deallocateProcess(&p1);

    printf("Start Address    : %d\n", p1.startAddress);
    printf("End Address      : %d\n", p1.endAddress);
    printf("Allocated        : %s\n",
           p1.allocated ? "Yes" : "No");

    return 0;
}