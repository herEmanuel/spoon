#include "disassembler.hpp"
#include <fstream>
#include <iostream>
#include <elf/elf.hpp>

Disassembler::Disassembler(std::ifstream& file) : m_file(file) {
}

Disassembler::~Disassembler() {
}

void Disassembler::disassemble(Elf::program_header& ph) {
    // read the bytes contained in that segment from the file
    m_file.seekg(ph.offset, std::ios::beg);

    std::cout << "size: " << ph.filesz << "\n";
    
    m_bytes.reserve(ph.filesz); // check this later
    m_file.read(reinterpret_cast<char*>(m_bytes.data()), ph.filesz);

    for (size_t i = 0; i < 100; i++) {
        std::cout << std::hex << (int)m_bytes[i] << " ";
    }

}