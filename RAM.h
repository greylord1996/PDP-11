#pragma once
#include <cstdint>

const uint16_t MAX_MEMORY_SIZE = 32768;

class RAM
{
public:
    uint16_t  mem_ram[MAX_MEMORY_SIZE] ;
    RAM();
    virtual  ~RAM();

    void getWordByAddr();
    void getByteByAddr();
    void setWordAddr();
    void setByteAddr();
};

