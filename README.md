# Memory Allocation Simulator

An interactive **memory allocation simulator implemented as a user-space program in the xv6 operating system**.

The project demonstrates how classical dynamic memory allocation strategies work by managing a simulated memory space and allocating/deallocating memory for processes.

## Features

* First Fit memory allocation
* Best Fit memory allocation
* Worst Fit memory allocation
* Dynamic memory allocation and deallocation
* Process ID validation
* Duplicate process detection
* Free-block merging after deallocation
* Exact-fit allocation
* Allocation failure handling
* Memory usage statistics
* External fragmentation calculation
* Interactive command-line interface
* Runs directly inside xv6

## Allocation Algorithms

### First Fit

Searches the memory blocks from the beginning and allocates the **first free block** large enough to satisfy the requested memory size.

### Best Fit

Searches all available free blocks and allocates the **smallest block** that can satisfy the request.

### Worst Fit

Searches all available free blocks and allocates the **largest free block** available for the request.

## Memory Management

The simulator maintains a list of memory blocks. Each block stores:

* Starting address
* Block size
* Process ID
* Allocation status

When a process requests memory, the selected allocation algorithm searches the available free blocks.

If a block is larger than the requested memory, it is split into:

```text
Allocated Block + Remaining Free Block
```

When a process is deallocated, its block becomes free. Adjacent free blocks are then merged to reduce fragmentation.

## External Fragmentation

External fragmentation is calculated as:

```text
External Fragmentation
= Total Free Memory - Largest Free Block
```

For example:

```text
| P1 | FREE 300 KB | P2 | FREE 200 KB |
```

Total free memory:

```text
300 + 200 = 500 KB
```

Largest free block:

```text
300 KB
```

Therefore:

```text
External Fragmentation = 500 - 300
                        = 200 KB
```

## xv6 Integration

The simulator is implemented as a **user-space program in xv6**.

The main implementation is:

```text
user/memsim.c
```

It uses xv6's user-space interfaces such as `printf()`, `read()`, and `exit()` instead of relying on standard C library functions unavailable in xv6.

The xv6 kernel's own memory allocator (`kalloc.c`) is not modified. The project provides a separate simulated memory-management environment in user space.

## Project Structure

```text
memory-allocation-simulator/
│
├── .github/
│   └── workflows/
│       └── test.yml
│
├── kernel/              # xv6 kernel source
├── mkfs/                # xv6 file-system utility
├── user/
│   ├── memsim.c         # Memory allocation simulator
│   └── ...               # Other xv6 user programs
│
├── Makefile             # xv6 build configuration
├── README               # xv6 documentation
├── README.md            # Project documentation
├── LICENSE
└── test-xv6.py
```

## Running the Project

### 1. Build xv6

From the project root:

```bash
make
```

### 2. Start xv6

```bash
make qemu
```

### 3. Run the simulator

Inside the xv6 shell:

```text
$ memsim
```

The simulator provides an interactive menu for selecting the memory allocation algorithm and performing allocation, deallocation, memory display, and statistics operations.

## Example

A typical memory layout may look like:

```text
| P1 100 KB | P2 200 KB | FREE 300 KB | P3 400 KB |
```

After deallocating a process:

```text
| P1 100 KB | FREE 200 KB | FREE 300 KB | P3 400 KB |
```

Adjacent free blocks can then be merged:

```text
| P1 100 KB | FREE 500 KB | P3 400 KB |
```

The simulator reports the resulting memory utilization and external fragmentation.

## Error Handling

The simulator handles common invalid operations, including:

* Duplicate process IDs
* Zero or negative memory requests
* Requests larger than total memory
* Allocation when no suitable block exists
* Deallocation of a nonexistent process
* Invalid menu choices
* Invalid allocation algorithm selection

## Technologies Used

* **C**
* **xv6-riscv**
* **RISC-V**
* **QEMU**
* **Linux / WSL**
* **Git & GitHub**

## Purpose

The project is designed to provide a practical understanding of:

* Dynamic memory allocation
* Memory partitioning
* First Fit, Best Fit, and Worst Fit
* Memory deallocation
* Free-block merging
* External fragmentation
* User-space programming in an operating system environment

