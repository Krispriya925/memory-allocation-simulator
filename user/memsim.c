#include "kernel/types.h"
#include "user/user.h"

#define MAX_BLOCKS 100

// ==================== DATA STRUCTURES ====================

struct MemoryBlock {
    int startAddress;
    int size;
    int processId;
    int free;
};

struct MemoryManager {
    int totalMemory;
    struct MemoryBlock blocks[MAX_BLOCKS];
    int blockCount;
};

// ==================== ALGORITHMS ====================

int
firstFit(struct MemoryManager *manager, int memoryRequired)
{
    int i;

    for (i = 0; i < manager->blockCount; i++) {

        if (manager->blocks[i].free &&
            manager->blocks[i].size >= memoryRequired) {

            return i;
        }
    }

    return -1;
}

int
bestFit(struct MemoryManager *manager, int memoryRequired)
{
    int bestIndex = -1;
    int i;

    for (i = 0; i < manager->blockCount; i++) {

        if (manager->blocks[i].free &&
            manager->blocks[i].size >= memoryRequired) {

            if (bestIndex == -1 ||
                manager->blocks[i].size <
                manager->blocks[bestIndex].size) {

                bestIndex = i;
            }
        }
    }

    return bestIndex;
}

int
worstFit(struct MemoryManager *manager, int memoryRequired)
{
    int worstIndex = -1;
    int i;

    for (i = 0; i < manager->blockCount; i++) {

        if (manager->blocks[i].free &&
            manager->blocks[i].size >= memoryRequired) {

            if (worstIndex == -1 ||
                manager->blocks[i].size >
                manager->blocks[worstIndex].size) {

                worstIndex = i;
            }
        }
    }

    return worstIndex;
}

// ==================== INITIALIZATION ====================

void
initializeMemoryManager(struct MemoryManager *manager, int totalMemory)
{
    manager->totalMemory = totalMemory;
    manager->blockCount = 1;

    manager->blocks[0].startAddress = 0;
    manager->blocks[0].size = totalMemory;
    manager->blocks[0].processId = -1;
    manager->blocks[0].free = 1;
}

// ==================== ALLOCATION ====================

int
allocateMemory(struct MemoryManager *manager,
               int processId,
               int memoryRequired)
{
    int index;
    int j;

    index = firstFit(manager, memoryRequired);

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

    for (j = manager->blockCount; j > index + 1; j--) {
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

int
allocateMemoryBestFit(struct MemoryManager *manager,
                      int processId,
                      int memoryRequired)
{
    int index;
    int j;

    index = bestFit(manager, memoryRequired);

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

    for (j = manager->blockCount; j > index + 1; j--) {
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

int
allocateMemoryWorstFit(struct MemoryManager *manager,
                       int processId,
                       int memoryRequired)
{
    int index;
    int j;

    index = worstFit(manager, memoryRequired);

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

    for (j = manager->blockCount; j > index + 1; j--) {
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

// ==================== PROCESS CHECK ====================

int
processExists(struct MemoryManager *manager, int processId)
{
    int i;

    for (i = 0; i < manager->blockCount; i++) {

        if (!manager->blocks[i].free &&
            manager->blocks[i].processId == processId) {

            return 1;
        }
    }

    return 0;
}

// ==================== MERGING ====================

void
mergeFreeBlocks(struct MemoryManager *manager)
{
    int i;
    int j;

    for (i = 0; i < manager->blockCount - 1; i++) {

        if (manager->blocks[i].free &&
            manager->blocks[i + 1].free) {

            manager->blocks[i].size +=
                manager->blocks[i + 1].size;

            for (j = i + 1;
                 j < manager->blockCount - 1;
                 j++) {

                manager->blocks[j] =
                    manager->blocks[j + 1];
            }

            manager->blockCount--;

            i--;
        }
    }
}

// ==================== DEALLOCATION ====================

int
deallocateMemory(struct MemoryManager *manager, int processId)
{
    int i;

    for (i = 0; i < manager->blockCount; i++) {

        if (!manager->blocks[i].free &&
            manager->blocks[i].processId == processId) {

            manager->blocks[i].processId = -1;
            manager->blocks[i].free = 1;

            mergeFreeBlocks(manager);

            return 1;
        }
    }

    return 0;
}

// ==================== DISPLAY MEMORY ====================

void
displayMemory(struct MemoryManager *manager)
{
    int i;

    printf("\n===== MEMORY STATUS =====\n");

    for (i = 0; i < manager->blockCount; i++) {

        printf(
            "Block %d: Start=%d, Size=%d KB, PID=%d, Status=%s\n",
            i,
            manager->blocks[i].startAddress,
            manager->blocks[i].size,
            manager->blocks[i].processId,
            manager->blocks[i].free ? "FREE" : "ALLOCATED"
        );
    }
}

// ==================== EXTERNAL FRAGMENTATION ====================

int
calculateExternalFragmentation(struct MemoryManager *manager)
{
    int totalFreeMemory = 0;
    int largestFreeBlock = 0;
    int i;

    for (i = 0; i < manager->blockCount; i++) {

        if (manager->blocks[i].free) {

            totalFreeMemory += manager->blocks[i].size;

            if (manager->blocks[i].size >
                largestFreeBlock) {

                largestFreeBlock =
                    manager->blocks[i].size;
            }
        }
    }

    return totalFreeMemory - largestFreeBlock;
}

// ==================== STATISTICS ====================

void
displayStatistics(struct MemoryManager *manager)
{
    int allocatedMemory = 0;
    int allocatedProcesses = 0;
    int freeBlocks = 0;
    int freeMemory;
    int externalFragmentation;
    int i;

    for (i = 0; i < manager->blockCount; i++) {

        if (manager->blocks[i].free) {
            freeBlocks++;
        }
        else {
            allocatedMemory += manager->blocks[i].size;
            allocatedProcesses++;
        }
    }

    freeMemory =
        manager->totalMemory - allocatedMemory;

    externalFragmentation =
        calculateExternalFragmentation(manager);

    printf("\n===== MEMORY STATISTICS =====\n");

    printf("Total Memory: %d KB\n",
           manager->totalMemory);

    printf("Allocated Memory: %d KB\n",
           allocatedMemory);

    printf("Free Memory: %d KB\n",
           freeMemory);

    printf("Allocated Processes: %d\n",
           allocatedProcesses);

    printf("Free Blocks: %d\n",
           freeBlocks);

    printf("External Fragmentation: %d KB\n",
           externalFragmentation);
}

// ==================== MAIN ====================

int
readInt(void)
{
    char buf[20];
    int n;
    int i;
    int value = 0;
    int sign = 1;

    n = read(0, buf, sizeof(buf));

    if (n <= 0)
        return 0;

    for (i = 0; i < n; i++) {

        if (buf[i] == '-') {
            sign = -1;
        }
        else if (buf[i] >= '0' && buf[i] <= '9') {
            value = value * 10 + (buf[i] - '0');
        }
        else if (buf[i] == '\n') {
            break;
        }
    }

    return value * sign;
}

int
main(void)
{
    struct MemoryManager manager;

    int totalMemory;
    int algorithmChoice;
    int processId;
    int memoryRequired;
    int address;
    int choice;
    int result;

    printf("====================================\n");
    printf("     MEMORY ALLOCATION SIMULATOR\n");
    printf("====================================\n");

    printf("\nEnter total memory (KB): ");
    totalMemory = readInt();

    initializeMemoryManager(&manager, totalMemory);

    printf("\nChoose Allocation Algorithm:\n");
    printf("1. First Fit\n");
    printf("2. Best Fit\n");
    printf("3. Worst Fit\n");

    printf("\nEnter your choice: ");
    algorithmChoice = readInt();

    if (algorithmChoice == 1) {
        printf("\nSelected Algorithm: First Fit\n");
    }
    else if (algorithmChoice == 2) {
        printf("\nSelected Algorithm: Best Fit\n");
    }
    else if (algorithmChoice == 3) {
        printf("\nSelected Algorithm: Worst Fit\n");
    }
    else {
        printf("\nInvalid algorithm choice!\n");
        exit(0);
    }

    while (1) {

        printf("\n===== MENU =====\n");
        printf("1. Allocate Process\n");
        printf("2. Deallocate Process\n");
        printf("3. Display Memory\n");
	printf("4. Display Statistics\n");
	printf("5. Exit\n");
        printf("\nEnter your choice: ");
        choice = readInt();

        if (choice == 1) {

            printf("\nEnter Process ID: ");
            processId = readInt();

            if (processExists(&manager, processId)) {

                printf("\nProcess P%d already exists!\n",
                       processId);

                continue;
            }

            printf("Enter memory required (KB): ");
            memoryRequired = readInt();

            if (memoryRequired <= 0) {

                printf("\nInvalid memory size! ");
                printf("Memory must be greater than 0 KB.\n");

                continue;
            }

            if (memoryRequired > manager.totalMemory) {

                printf("\nRequested memory exceeds total memory!\n");

                continue;
            }

            if (algorithmChoice == 1) {

                address = allocateMemory(
                    &manager,
                    processId,
                    memoryRequired
                );
            }
            else if (algorithmChoice == 2) {

                address = allocateMemoryBestFit(
                    &manager,
                    processId,
                    memoryRequired
                );
            }
            else {

                address = allocateMemoryWorstFit(
                    &manager,
                    processId,
                    memoryRequired
                );
            }

            if (address == -1) {

                printf("\nMemory allocation failed for P%d!\n",
                       processId);
            }
            else {

                printf("\nProcess P%d allocated successfully!\n",
                       processId);

                printf("Starting Address: %d KB\n",
                       address);
            }
        }

        else if (choice == 2) {

            printf("\nEnter Process ID to deallocate: ");
            processId = readInt();

            result = deallocateMemory(
                &manager,
                processId
            );

            if (result == 1) {

                printf(
                    "\nProcess P%d deallocated successfully!\n",
                    processId
                );
            }
            else {

                printf(
                    "\nProcess P%d not found!\n",
                    processId
                );
            }
        }

        else if (choice == 3) {

            displayMemory(&manager);
        }

	else if (choice == 4) {

 	    displayStatistics(&manager);
	}

	else if (choice == 5) {

    	    printf("\nExiting simulator...\n");
    	    break;
	}
        else {

            printf("\nInvalid choice!\n");
        }
    }

    exit(0);
}
