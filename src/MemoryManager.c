#include "MemoryManager.h"

void initializeMemoryManager(MemoryManager *manager, int totalMemory) {
    manager->totalMemory = totalMemory;
    manager->blockCount = 1;

    manager->blocks[0].startAddress = 0;
    manager->blocks[0].size = totalMemory;
    manager->blocks[0].processId = -1;
    manager->blocks[0].free = 1;
}
int allocateMemory(MemoryManager *manager, int processId, int memoryRequired) {

    for (int i = 0; i < manager->blockCount; i++) {

        if (manager->blocks[i].free &&
            manager->blocks[i].size >= memoryRequired) {

            if (manager->blocks[i].size == memoryRequired) {

                manager->blocks[i].processId = processId;
                manager->blocks[i].free = 0;

                return manager->blocks[i].startAddress;
            }

            if (manager->blockCount >= MAX_BLOCKS) {
                return -1;
            }

            for (int j = manager->blockCount; j > i + 1; j--) {
                manager->blocks[j] = manager->blocks[j - 1];
            }

            manager->blocks[i + 1].startAddress =
                manager->blocks[i].startAddress + memoryRequired;

            manager->blocks[i + 1].size =
                manager->blocks[i].size - memoryRequired;

            manager->blocks[i + 1].processId = -1;
            manager->blocks[i + 1].free = 1;

            manager->blocks[i].size = memoryRequired;
            manager->blocks[i].processId = processId;
            manager->blocks[i].free = 0;

            manager->blockCount++;

            return manager->blocks[i].startAddress;
        }
    }

    return -1;
}