#pragma once

#include <fstream>
#include <vector>
#include <elf/elf.hpp>

class Disassembler {
    std::ifstream& m_file;
    std::vector<uint8_t> m_bytes;

public:
    Disassembler(std::ifstream& file);
    ~Disassembler();

    void disassemble(Elf::program_header& ph);
};