#pragma once
#include <iostream>
#include <cstdint>



const uint16_t MAX_MEMORY_SIZE = 32768;

class RAM
{
private:
        uint16_t  mem_ram[MAX_MEMORY_SIZE] = {};
public:
    RAM();
    ~RAM();

    uint16_t GetWordByAddr(uint16_t address);
    uint16_t GetByteByAddr(uint16_t address);
    void SetWordOnAddr(uint16_t address, uint16_t word);
    void SetByteOnAddr(uint16_t address, uint8_t byte);
};

