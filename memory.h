#pragma once
#include <cstdint>

const uint16_t MAX_MEMORY_SIZE = 32768;

class memory
{
public:
    uint16_t  memory[MAX_MEMORY_SIZE] ;
    memory();
    virtual  ~memory();

    getWordByAddr();
    getByteByAddr();
    setWordAddr();
    setByteAddr();
};

