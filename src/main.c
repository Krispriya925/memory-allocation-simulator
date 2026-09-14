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

        // Test Best Fit

    MemoryManager bestFitManager;

    initializeMemoryManager(&bestFitManager, 1000);

    allocateMemoryBestFit(&bestFitManager, 1, 100);
    allocateMemoryBestFit(&bestFitManager, 2, 400);
    allocateMemoryBestFit(&bestFitManager, 3, 200);
    allocateMemoryBestFit(&bestFitManager, 4, 100);

    deallocateMemory(&bestFitManager, 1);
    deallocateMemory(&bestFitManager, 3);

    printf("\n===== BEST FIT TEST =====\n");

    printf("\nMemory before P5 allocation:\n");

    for (int i = 0; i < bestFitManager.blockCount; i++) {
        printf("Block %d: Start=%d, Size=%d KB, PID=%d, Status=%s\n",
               i,
               bestFitManager.blocks[i].startAddress,
               bestFitManager.blocks[i].size,
               bestFitManager.blocks[i].processId,
               bestFitManager.blocks[i].free ? "FREE" : "ALLOCATED");
    }

    int p5 = allocateMemoryBestFit(&bestFitManager,5, 150);

    printf("\nP5 allocated at address: %d\n", p5);

    printf("\nMemory after P5 allocation:\n");

    for (int i = 0; i < bestFitManager.blockCount; i++) {
        printf("Block %d: Start=%d, Size=%d KB, PID=%d, Status=%s\n",
               i,
               bestFitManager.blocks[i].startAddress,
               bestFitManager.blocks[i].size,
               bestFitManager.blocks[i].processId,
               bestFitManager.blocks[i].free ? "FREE" : "ALLOCATED");
    }
        // Compare First Fit and Best Fit

    MemoryManager comparisonManager;

    initializeMemoryManager(&comparisonManager, 1000);

    allocateMemory(&comparisonManager, 1, 100);
    allocateMemory(&comparisonManager, 2, 300);
    allocateMemory(&comparisonManager, 3, 200);
    allocateMemory(&comparisonManager, 4, 100);

    deallocateMemory(&comparisonManager, 1);
    deallocateMemory(&comparisonManager, 2);

    printf("\n===== FIRST FIT vs BEST FIT =====\n");

    printf("\nMemory before allocation:\n");

    for (int i = 0; i < comparisonManager.blockCount; i++) {
        printf("Block %d: Start=%d, Size=%d KB, PID=%d, Status=%s\n",
               i,
               comparisonManager.blocks[i].startAddress,
               comparisonManager.blocks[i].size,
               comparisonManager.blocks[i].processId,
               comparisonManager.blocks[i].free ? "FREE" : "ALLOCATED");
    }
        // Test Worst Fit

    MemoryManager worstFitManager;

    initializeMemoryManager(&worstFitManager, 1000);

    allocateMemoryWorstFit(&worstFitManager, 1, 100);
    allocateMemoryWorstFit(&worstFitManager, 2, 300);
    allocateMemoryWorstFit(&worstFitManager, 3, 100);
    allocateMemoryWorstFit(&worstFitManager, 4, 200);

    deallocateMemory(&worstFitManager, 1);
    deallocateMemory(&worstFitManager, 3);

    printf("\n===== WORST FIT TEST =====\n");

    printf("\nMemory before P5 allocation:\n");

    for (int i = 0; i < worstFitManager.blockCount; i++) {
        printf("Block %d: Start=%d, Size=%d KB, PID=%d, Status=%s\n",
               i,
               worstFitManager.blocks[i].startAddress,
               worstFitManager.blocks[i].size,
               worstFitManager.blocks[i].processId,
               worstFitManager.blocks[i].free ? "FREE" : "ALLOCATED");
    }

    int p5Worst = allocateMemoryWorstFit(&worstFitManager, 5, 150);

    printf("\nP5 allocated at address: %d\n", p5Worst);

    printf("\nMemory after P5 allocation:\n");

    for (int i = 0; i < worstFitManager.blockCount; i++) {
        printf("Block %d: Start=%d, Size=%d KB, PID=%d, Status=%s\n",
               i,
               worstFitManager.blocks[i].startAddress,
               worstFitManager.blocks[i].size,
               worstFitManager.blocks[i].processId,
               worstFitManager.blocks[i].free ? "FREE" : "ALLOCATED");
    }
    return 0;
}