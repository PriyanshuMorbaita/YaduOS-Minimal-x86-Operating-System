# YaduOS-Minimal-x86-Operating-System
YaduOS is a handcrafted operating system for x86, written in C and Assembly, designed to demonstrate core kernel and hardware interaction concepts.
YaduOS — Minimal x86 Operating System with Paging, Multitasking, File System, and User Program Execution

Bootloader & GDT/IDT Setup — Custom boot stage with descriptor tables for protected mode.

Interrupt & I/O Handling — Low-level interrupt service routines and hardware driver interfaces.

Paging & Virtual Memory — Demand-based paging for process isolation and memory efficiency.

Multitasking & Task Switching — Preemptive context switching using a custom task scheduler.

File System Support — Read/write access via a basic disk driver and filesystem layer.

User Program Execution — Load and run user-level applications in a protected environment.

Heap & Memory Management — Kernel heap allocation with paging integration.

This project is aimed at exploring how real operating systems work — from CPU initialization to running user applications — while keeping the code modular and well-structured for learning and experimentation.


## 📦 Requirements
- `make`
- `nasm`
- `gcc` (cross-compiler if targeting bare metal)
- `qemu` (for running the OS)

## 🛠 Build Instructions

To Clean the OS:
```bash
make clean
```
To Build the OS:
```bash
./build.sh
```
To Run the OS:
```bash
cd bin
qemu-system-x86_64 -hda bin/os.bin

