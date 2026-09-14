#include "FirstFit.h"

int firstFit(MemoryManager *manager, int memoryRequired) {

    for (int i = 0; i < manager->blockCount; i++) {

        if (manager->blocks[i].free &&
            manager->blocks[i].size >= memoryRequired) {

            return i;
        }
    }

    return -1;
}