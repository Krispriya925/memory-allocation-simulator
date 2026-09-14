#include <stdio.h>
#include "MemoryManager.h"

int main() {

    MemoryManager manager;

    initializeMemoryManager(&manager, 1000);

    printf("===== MEMORY ALLOCATION SIMULATOR =====\n\n");

    printf("Total Memory : %d KB\n", manager.totalMemory);
    printf("Block Count  : %d\n\n", manager.blockCount);

    printf("Initial Memory Blocks:\n");

    for (int i = 0; i < manager.blockCount; i++) {
        printf("Block %d: Start=%d, Size=%d KB, PID=%d, Status=%s\n",
               i,
               manager.blocks[i].startAddress,
               manager.blocks[i].size,
               manager.blocks[i].processId,
               manager.blocks[i].free ? "FREE" : "ALLOCATED");
    }

    // Allocate three processes
    allocateMemory(&manager, 1, 200);
    allocateMemory(&manager, 2, 300);
    allocateMemory(&manager, 3, 100);

    printf("\nAfter allocating P1, P2 and P3:\n");

    for (int i = 0; i < manager.blockCount; i++) {
        printf("Block %d: Start=%d, Size=%d KB, PID=%d, Status=%s\n",
               i,
               manager.blocks[i].startAddress,
               manager.blocks[i].size,
               manager.blocks[i].processId,
               manager.blocks[i].free ? "FREE" : "ALLOCATED");
    }

    // Deallocate P1 and P3
    deallocateMemory(&manager, 1);
    deallocateMemory(&manager, 3);

    printf("\nAfter deallocating P1 and P3:\n");

    for (int i = 0; i < manager.blockCount; i++) {
        printf("Block %d: Start=%d, Size=%d KB, PID=%d, Status=%s\n",
               i,
               manager.blocks[i].startAddress,
               manager.blocks[i].size,
               manager.blocks[i].processId,
               manager.blocks[i].free ? "FREE" : "ALLOCATED");
    }

    // Test First Fit
    int p4 = allocateMemory(&manager, 4, 150);

    printf("\nP4 allocated at address: %d\n", p4);

    printf("\nFinal Memory Blocks:\n");

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