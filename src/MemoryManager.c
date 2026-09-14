#include "MemoryManager.h"
#include "algorithms/FirstFit.h"
#include "algorithms/BestFit.h"
#include "algorithms/WorstFit.h"
void initializeMemoryManager(MemoryManager *manager, int totalMemory) {
    manager->totalMemory = totalMemory;
    manager->blockCount = 1;

    manager->blocks[0].startAddress = 0;
    manager->blocks[0].size = totalMemory;
    manager->blocks[0].processId = -1;
    manager->blocks[0].free = 1;
}
int allocateMemory(MemoryManager *manager, int processId, int memoryRequired) {

    int index = firstFit(manager, memoryRequired);

    if (index == -1) {
        return -1;
    }

    if (manager->blocks[index].size == memoryRequired) {

        manager->blocks[index].processId = processId;
        manager->blocks[index].free = 0;

        return manager->blocks[index].startAddress;
    }

    if (manager->blockCount >= MAX_BLOCKS) {
        return -1;
    }

    for (int j = manager->blockCount; j > index + 1; j--) {
        manager->blocks[j] = manager->blocks[j - 1];
    }

    manager->blocks[index + 1].startAddress =
        manager->blocks[index].startAddress + memoryRequired;

    manager->blocks[index + 1].size =
        manager->blocks[index].size - memoryRequired;

    manager->blocks[index + 1].processId = -1;
    manager->blocks[index + 1].free = 1;

    manager->blocks[index].size = memoryRequired;
    manager->blocks[index].processId = processId;
    manager->blocks[index].free = 0;

    manager->blockCount++;

    return manager->blocks[index].startAddress;
}
int allocateMemoryBestFit(MemoryManager *manager, int processId, int memoryRequired) {

    int index = bestFit(manager, memoryRequired);

    if (index == -1) {
        return -1;
    }

    if (manager->blocks[index].size == memoryRequired) {

        manager->blocks[index].processId = processId;
        manager->blocks[index].free = 0;

        return manager->blocks[index].startAddress;
    }

    if (manager->blockCount >= MAX_BLOCKS) {
        return -1;
    }

    for (int j = manager->blockCount; j > index + 1; j--) {
        manager->blocks[j] = manager->blocks[j - 1];
    }

    manager->blocks[index + 1].startAddress =
        manager->blocks[index].startAddress + memoryRequired;

    manager->blocks[index + 1].size =
        manager->blocks[index].size - memoryRequired;

    manager->blocks[index + 1].processId = -1;
    manager->blocks[index + 1].free = 1;

    manager->blocks[index].size = memoryRequired;
    manager->blocks[index].processId = processId;
    manager->blocks[index].free = 0;

    manager->blockCount++;

    return manager->blocks[index].startAddress;
}
int allocateMemoryWorstFit(MemoryManager *manager, int processId, int memoryRequired) {

    int index = worstFit(manager, memoryRequired);

    if (index == -1) {
        return -1;
    }

    if (manager->blocks[index].size == memoryRequired) {

        manager->blocks[index].processId = processId;
        manager->blocks[index].free = 0;

        return manager->blocks[index].startAddress;
    }

    if (manager->blockCount >= MAX_BLOCKS) {
        return -1;
    }

    for (int j = manager->blockCount; j > index + 1; j--) {
        manager->blocks[j] = manager->blocks[j - 1];
    }

    manager->blocks[index + 1].startAddress =
        manager->blocks[index].startAddress + memoryRequired;

    manager->blocks[index + 1].size =
        manager->blocks[index].size - memoryRequired;

    manager->blocks[index + 1].processId = -1;
    manager->blocks[index + 1].free = 1;

    manager->blocks[index].size = memoryRequired;
    manager->blocks[index].processId = processId;
    manager->blocks[index].free = 0;

    manager->blockCount++;

    return manager->blocks[index].startAddress;
}
void deallocateMemory(MemoryManager *manager, int processId) {

    for (int i = 0; i < manager->blockCount; i++) {

        if (!manager->blocks[i].free &&
            manager->blocks[i].processId == processId) {

            manager->blocks[i].processId = -1;
            manager->blocks[i].free = 1;

            return;
        }
    }
}
void mergeFreeBlocks(MemoryManager *manager) {

    for (int i = 0; i < manager->blockCount - 1; i++) {

        if (manager->blocks[i].free &&
            manager->blocks[i + 1].free) {

            manager->blocks[i].size += manager->blocks[i + 1].size;

            for (int j = i + 1; j < manager->blockCount - 1; j++) {
                manager->blocks[j] = manager->blocks[j + 1];
            }

            manager->blockCount--;

            i--;
        }
    }
}