#ifndef LINKER_H
#define LINKER_H

#include <elf.h>
#include <link.h>

struct ELF_Info
{
    size_t size;
    struct ELF *ELF;
};

struct ELF
{
    ElfW(Ehdr) ehdr;
};

void ld(char *executable_name, char *object_path);
struct ELF_Info *load_object(char *path);

struct ELF_Info *get_executable(struct ELF_Info *object_ELFI);

void update_header(struct ELF_Info *executable_ELFI);
size_t get_entry_point(struct ELF_Info *executable_ELFI);
void update_section_header(struct ELF_Info *executable_ELFI);
void insert_program_header(struct ELF_Info *executable_ELFI);

void write_executable(char *executable_name, struct ELF_Info *executable_ELFI);
void unload_ELF(struct ELF_Info *ELFI);


#endif /* LINKER_H */
