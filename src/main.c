#include <stdio.h>
#include "MemoryManager.h"

int main() {

    MemoryManager manager;

    initializeMemoryManager(&manager, 1000);

    printf("===== MEMORY ALLOCATION SIMULATOR =====\n\n");

    printf("Total Memory : %d KB\n", manager.totalMemory);
    printf("Block Count  : %d\n\n", manager.blockCount);

    printf("Memory Blocks:\n");

    for (int i = 0; i < manager.blockCount; i++) {
        printf("Block %d\n", i);
        printf("Start Address : %d\n", manager.blocks[i].startAddress);
        printf("Size          : %d KB\n", manager.blocks[i].size);
        printf("Process ID    : %d\n", manager.blocks[i].processId);
        printf("Status        : %s\n\n",
               manager.blocks[i].free ? "FREE" : "ALLOCATED");
    }
    int startAddress = allocateMemory(&manager, 1, 200);

printf("P1 allocated at address: %d\n\n", startAddress);


printf("Memory Blocks:\n");

for (int i = 0; i < manager.blockCount; i++) {
    printf("Block %d: Start=%d, Size=%d KB, PID=%d, Status=%s\n",
           i,
           manager.blocks[i].startAddress,
           manager.blocks[i].size,
           manager.blocks[i].processId,
           manager.blocks[i].free ? "FREE" : "ALLOCATED");
}
    return 0;
}