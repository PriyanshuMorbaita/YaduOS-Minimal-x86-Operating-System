#ifndef ELFLOADER_H
#define ELFLOADER_H

#include "elf.h"
#include "config.h"

struct elf_file{
    char filename[PEACHOS_MAX_PATH];
    int in_memory_size;
    void* elf_memory;
    
    void* virtual_base_address;
    void* virtual_end_address;

    void* physical_base_address;
    void* physical_end_address; 
};


void elf_close(struct elf_file* elf_file);
int elf_load(const char* filename, struct elf_file** file_out);

void* elf_virtual_base(struct  elf_file* elf_file);
void* elf_virtual_end(struct  elf_file* elf_file);
void* elf_physical_end(struct  elf_file* elf_file);
void* elf_physical_base(struct  elf_file* elf_file);

void elf_file_free(struct elf_file* elf_file);
struct elf_file* elf_file_new();
struct elf_header* elf_header(struct elf_file* file);
void* elf_memory(struct elf_file* file);
struct elf32_shdr* elf_sheader(struct elf_header* elf_header);
struct elf32_phdr* elf_pheader(struct elf_header* elf_header);
struct elf32_shdr* elf_section(struct elf_header* elf_header, int index);
void* elf_phdr_phys_address(struct elf_file* file, struct elf32_phdr* phdr);

#endif