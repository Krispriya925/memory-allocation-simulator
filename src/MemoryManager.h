#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#define MAX_BLOCKS 100

typedef struct {
    int startAddress;
    int size;
    int processId;
    int free;
} MemoryBlock;

typedef struct {
    int totalMemory;
    MemoryBlock blocks[MAX_BLOCKS];
    int blockCount;
} MemoryManager;

void initializeMemoryManager(MemoryManager *manager, int totalMemory);
int allocateMemory(MemoryManager *manager, int processId, int memoryRequired);
#endif