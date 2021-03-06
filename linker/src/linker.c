#include "linker.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


void ld(char *executable_name, char *object_path)
{
    struct ELF_Info *object_ELFI = load_object(object_path);
    struct ELF_Info *executable_ELFI = get_executable(object_ELFI);
    write_executable(executable_name, executable_ELFI);
}

struct ELF_Info *load_object(char *path)
{
    struct ELF_Info *object_ELFI = malloc(sizeof(struct ELF_Info));

    struct stat stat_buffer;
    stat(path, &stat_buffer);
    object_ELFI->size = stat_buffer.st_size;

    int fd = open(path, O_RDONLY);
    object_ELFI->ELF = mmap(0, stat_buffer.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);

    return object_ELFI;
}

struct ELF_Info *get_executable(struct ELF_Info *object_ELFI)
{
    struct ELF_Info *executable_ELFI = malloc(sizeof(struct ELF_Info));

    executable_ELFI->ELF = malloc(object_ELFI->size + sizeof(ElfW(Phdr)));
    memcpy(executable_ELFI->ELF, object_ELFI->ELF, object_ELFI->size);

    executable_ELFI->size = object_ELFI->size + sizeof(ElfW(Phdr));

    update_header(executable_ELFI);
    update_section_header(executable_ELFI);
    insert_program_header(executable_ELFI);

    return executable_ELFI;
}

void update_header(struct ELF_Info *executable_ELFI)
{
    // SET TYPE TO EXECUTABLE (2)
    executable_ELFI->ELF->ehdr.e_type = ET_EXEC;

    // SET PROGRAM HEADER START TO THE END OF THE FILE
    executable_ELFI->ELF->ehdr.e_phoff = executable_ELFI->size;

    // SET PROGRAM HEADER SIZE OF SECTIONS
    executable_ELFI->ELF->ehdr.e_phentsize = 8;

    // SET PROGRAM HEADER NUMBER OF SECTIONS
    executable_ELFI->ELF->ehdr.e_phnum = 8;

    // SET THE ENTRY POINT OF THE FUNCTION _START
    executable_ELFI->ELF->ehdr.e_entry = get_entry_point(executable_ELFI);
}

size_t get_entry_point(struct ELF_Info *executable_ELFI)
{
    return 12;
}

void update_section_header(struct ELF_Info *executable_ELFI)
{

}

void insert_program_header(struct ELF_Info *executable_ELFI)
{

}

void write_executable(char *executable_name, struct ELF_Info *executable_ELFI)
{
    int fd = open(executable_name, O_WRONLY | O_APPEND | O_CREAT, 0755);
    write(fd, executable_ELFI->ELF, executable_ELFI->size);
}



void unload_ELF(struct ELF_Info *ELFI)
{
    munmap(ELFI->ELF, ELFI->size);
}

/*
struct ELF *map_object(char *object_path)
{
	struct ELF *my_elf = malloc(sizeof(struct ELF));

	if (pathname)
	{

		struct stat stat_buffer;
		stat(pathname, &stat_buffer);
		int fd = open(pathname, O_RDONLY);

		my_elf->pathname = malloc(sizeof(char) * strlen(pathname));
		memcpy(my_elf->pathname, pathname, strlen(pathname));

		my_elf->ehdr = mmap(0, stat_buffer.st_size,
	        PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE, fd, 0);
		close(fd);
	}
	else
	{
		my_elf->ehdr = addr;
	}

	char *my_elf_str = (void *) my_elf->ehdr;
	my_elf->shdr = (void *) my_elf_str + my_elf->ehdr->e_shoff;

	my_elf->phdr = (void *) my_elf_str + my_elf->ehdr->e_phoff;

    ElfW(Shdr) *section = my_elf->shdr;
	unsigned i = 0;


    while(i < my_elf->ehdr->e_shnum)
    {
        if (section->sh_type == SHT_DYNAMIC)
        {
            my_elf->dyn = (void *) my_elf_str + section->sh_offset;
            my_elf->shdr_dyn = section;
        }
		if (section->sh_type == SHT_DYNSYM)
        {
            my_elf->dynsym = (void *) my_elf_str + section->sh_offset;
            my_elf->shdr_dynsym = section;
        }

        char *section_str = (void *) section;
        section = (void *) section_str + my_elf->ehdr->e_shentsize;
        i++;
    }

	my_elf->dynstr = (void *) my_elf_str +
		get_section(my_elf, ".dynstr")->sh_offset;
	my_elf->shdr_dynstr = get_section(my_elf, ".dynstr");

	return my_elf;
}*/
