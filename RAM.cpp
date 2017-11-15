#include <RAM.h>

RAM::RAM()
{

}


RAM::~RAM()
{

}


uint16_t RAM::GetWordByAddr(uint16_t address)
{
    std::cout << "word = " << mem_ram[address] << std::endl;
    return this->mem_ram[address];
}


void RAM::SetWordOnAddr(uint16_t address, uint16_t word)
{
    this->mem_ram[address] = word;
}

uint16_t RAM::GetByteByAddr(uint16_t address)
{
    uint16_t word = GetWordByAddr(address);
    uint16_t byte = word >> 8;
    std::cout << "byte = " << byte << std::endl;
    return byte;
}

void RAM::SetByteOnAddr(uint16_t address, uint8_t byte)
{
    uint16_t tmp = byte;
    tmp = tmp << 8;
    //std::cout << "tmp = " << tmp;
    SetWordOnAddr(address, tmp);
    /*GetWordByAddr(address);
    uint16_t tmp = GetWordByAddr(address);
    tmp = tmp << 8;
    SetWordOnAddr(address, static_cast<uint8_t>(tmp));*/
}


