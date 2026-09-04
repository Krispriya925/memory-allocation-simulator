#include "Process.h"

void initializeProcess(Process *process, int id, int memory) {
    process->processId = id;
    process->memoryRequired = memory;
    process->startAddress = -1;
    process->endAddress = -1;
    process->allocated = 0;
}

void allocateProcess(Process *process, int startAddress) {
    process->startAddress = startAddress;
    process->endAddress = startAddress + process->memoryRequired - 1;
    process->allocated = 1;
}

void deallocateProcess(Process *process) {
    process->startAddress = -1;
    process->endAddress = -1;
    process->allocated = 0;
}