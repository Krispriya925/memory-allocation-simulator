#ifndef PROCESS_H
#define PROCESS_H

typedef struct {
    int processId;
    int memoryRequired;
    int startAddress;
    int endAddress;
    int allocated;
} Process;
void initializeProcess(Process *process, int id, int memory);
void allocateProcess(Process *process, int startAddress);
void deallocateProcess(Process *process);

#endif