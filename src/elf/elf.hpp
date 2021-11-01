#pragma once

#include <memory>

namespace Elf {

    constexpr size_t SIGNATURE = 0x464C457F; // stored backwards because of the endianess of my machine

    constexpr size_t ELF_64_BITS = 0x2;
    constexpr size_t ELF_LITTLE_ENDIAN = 0x1;

    constexpr size_t x86_64_ISA = 0x3E;

    struct elf_header {
        uint8_t ident[16];
        uint16_t type;
        uint16_t machine;
        uint32_t version;
        uint64_t entry;
        uint64_t phoff;
        uint64_t shoff;
        uint32_t flags;
        uint16_t elf_hdr_size;
        uint16_t ph_entry_size;
        uint16_t ph_count;
        uint16_t shdr_size;
        uint16_t sh_num;
        uint16_t shstrndx;
    };

    struct program_header {
        uint32_t type;
        uint32_t flags;
        uint64_t offset;
        uint64_t vaddr;
        uint64_t paddr;
        uint64_t filesz;
        uint64_t memsz;
        uint64_t align;
    };

    enum PType {
        P_NULL = 0x0,
        P_LOAD = 0x1,
        P_PHDR = 0x6
    };

    std::unique_ptr<elf_header> verify(std::ifstream& file);

}