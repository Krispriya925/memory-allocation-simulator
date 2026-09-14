#include "WorstFit.h"

int worstFit(MemoryManager *manager, int memoryRequired) {

    int worstIndex = -1;

    for (int i = 0; i < manager->blockCount; i++) {

        if (manager->blocks[i].free &&
            manager->blocks[i].size >= memoryRequired) {

            if (worstIndex == -1 ||
                manager->blocks[i].size > manager->blocks[worstIndex].size) {

                worstIndex = i;
            }
        }
    }

    return worstIndex;
}
