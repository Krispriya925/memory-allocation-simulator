#include "BestFit.h"

int bestFit(MemoryManager *manager, int memoryRequired) {

    int bestIndex = -1;

    for (int i = 0; i < manager->blockCount; i++) {

        if (manager->blocks[i].free &&
            manager->blocks[i].size >= memoryRequired) {

            if (bestIndex == -1 ||
                manager->blocks[i].size < manager->blocks[bestIndex].size) {

                bestIndex = i;
            }
        }
    }

    return bestIndex;
}