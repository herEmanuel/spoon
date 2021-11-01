#include "elf.hpp"
#include <fstream>
#include <iostream>
#include <cstring>
#include <memory>

namespace Elf {
    
    std::unique_ptr<elf_header> verify(std::ifstream& file) {
        auto header = std::make_unique<elf_header>();
    
        if (!file.read(reinterpret_cast<char*>(header.get()), sizeof(elf_header))) {
            std::cerr << "Could not read the elf header" << "\n";
            exit(1);
        }

        if (std::memcmp(header->ident, &SIGNATURE, 4) != 0) {
            std::cerr << "Spoon can only read elf executables" << "\n";
            exit(1);
        }
        
        if (header->ident[4] != ELF_64_BITS) {
            std::cerr << "Spoon can only disassemble 64 bits executables" << "\n";
            exit(1);
        }

        if (header->ident[5] != ELF_LITTLE_ENDIAN) {
            std::cerr << "Spoon can only disassemble little endian executables" << "\n";
            exit(1);
        }

        if (header->machine != x86_64_ISA) {
            std::cerr << "Spoon can only disassemble x86_64 executables" << "\n";
            exit(1);
        }
        
        return header;
    }

}
