#include <iostream>
#include <fstream>
#include <vector>
#include <elf/elf.hpp>
#include "disassembler.hpp"

int main(int argc, char* argv[]) {    

    if (argc != 2) {
        std::cerr << "Invalid number of arguments: expected a single file name" << "\n";
        exit(1);
    }

    std::ifstream file(argv[1], std::ios::binary);

    auto elf_header = Elf::verify(file);
    
    Disassembler disassembler(file);

    std::vector<Elf::program_header> program_headers(elf_header->ph_count);

    file.seekg(elf_header->phoff, std::ios::beg);

    file.read(reinterpret_cast<char*>(program_headers.data()), 
                sizeof(Elf::program_header) * elf_header->ph_count);

    for (auto& ph : program_headers) {
        if (ph.type != Elf::PType::P_LOAD)
            continue;

        disassembler.disassemble(ph);
    }

    return 0;
}